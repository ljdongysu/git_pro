#include "cnn.h"
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <sys/time.h>
#include <unistd.h>
#include<readfromdir.h>
#undef DEBUG_SMART

CNN::CNN()
{
    runtime = nullptr;
    engine = nullptr;
    context = nullptr;
}

CNN::~CNN()
{
    if (nullptr != context)
    {
        context->destroy();
    }

    if (nullptr != engine)
    {
        engine->destroy();
    }

    if (nullptr != runtime)
    {
        runtime->destroy();
    }

}

bool CNN::Init(const std::string serializedModelFile)
{

    if ((access(serializedModelFile.c_str(), 0 )) != 0)
    {
        return false;
    }

    SerializeModel(serializedModelFile);

    return true;
}

void CNN::FeatureExtract(const cv::Mat &img, vector<long> &feature)
{
    if (img.empty())
    {
        fprintf(stderr, "image is empty");
        return;
    }


}

void CNN::MaxIndex(vector<int>& maxIndex, const cv::Mat& similarity)
{
    const double* pxVec=similarity.ptr<double>(0);

    for (int i = 0; i < similarity.rows; i++)
    {
        pxVec = similarity.ptr<double>(i);
        //三通道数据都在第一行依次排列，按照BGR顺序
        //依次赋值为1
        float maxVal = pxVec[0];
        maxIndex[i] = 0;
        for (int j = 0; j < similarity.cols*similarity.channels(); j++)
        {
            if (maxVal < pxVec[j])
            {
                maxVal = pxVec[j];
                maxIndex[i] = j;
            }
        }
    }
}

float CNN::CalculateAccuracy(vector<int> &maxIndex,const vector<string> &referFullFileNames, const vector<string> &trainFullFileNames)
{
    int trueClass = 0;
    int falseClass = 0;
    for (int i = 0; i < maxIndex.size();++i)
    {
        string referName = referFullFileNames[maxIndex[i]];
        string trainName = trainFullFileNames[i];

        referName = GetStringName(referName,4);
        trainName = GetStringName(trainName,4);

        referName = GetStringName(referName,0);
        trainName = GetStringName(trainName,0);

        if (strcmp(referName.c_str(),trainName.c_str()))
        {
            std::cout<<referName<<" "<<trainName<<std::endl;
            falseClass++;
        }
        else
        {
            trueClass++;
        }
    }

    float accuracy = float(trueClass)/float(trueClass + falseClass);
    cout<<"the number of refer: "<<referFullFileNames.size()<<", the number of train: "<<trainFullFileNames.size()<<endl;
    cout<<"True Num: "<<trueClass<<", False Num: "<<falseClass<<endl;
    cout<<"accuracy: "<<accuracy<<endl;

    return accuracy;
}

void CNN::SimilarityMatrix(const VIDEO &trainFeature, const VIDEO &referFeature, cv::Mat &similarity)
{
    cv::Mat p,q;

    Map(referFeature, p); // or use pca
    Map(trainFeature, q); // or use pca

    assert(p.cols == q.cols);

    p = Normal(p);
    q = Normal(q);

    assert(p.cols == q.cols);

    similarity = CosinSimilarityMatrix(p, q);
    similarity = similarity.t();
}

void CNN::ReadImages(const vector<string> &FullfileNames, vector<cv::Mat> &matVec)
{
    for (int i =0; i< FullfileNames.size();++i)
    {
        cv::Mat img = cv::imread(FullfileNames[i]);
        cv::resize(img,img,cv::Size(INPUT_W,INPUT_H));
        matVec.push_back(img);
    }
}



void CNN::GetInputSize(int &width, int &height)
{
    width = INPUT_W;
    height = INPUT_H;
}

void CNN::FeatureExtract(const std::vector<cv::Mat> &frames, VIDEO &feature)
{


    std::vector<int> batchSizeVec;

    if (frames.size() > MAX_BATCHSIZE)
    {
        int batchSizeNum = frames.size() / MAX_BATCHSIZE;

        batchSizeVec.resize(batchSizeNum, MAX_BATCHSIZE);

        int mod = frames.size() % MAX_BATCHSIZE;
        if (mod != 0)
        {
            batchSizeNum++;
            batchSizeVec.push_back(mod);
        }
    }
    else
    {
        batchSizeVec.push_back(frames.size());
    }

    FeatureExtractBatch(frames, batchSizeVec, feature);

}


void CNN::Inference(int device, IExecutionContext& context, float* input, float* batchOutput, int batchSize)
{
    const ICudaEngine& engine = context.getEngine();

    // Pointers to input and output device buffers to pass to engine.
    // Engine requires exactly IEngine::getNbBindings() number of buffers.
    assert(engine.getNbBindings() == 2);
    void* buffers[2];

    // In order to bind the buffers, we need to know the names of the input and output tensors.
    // Note that indices are guaranteed to be less than IEngine::getNbBindings()
    const int inputIndex = engine.getBindingIndex(INPUT_BLOB_NAME);
    const int outputIndex = engine.getBindingIndex(OUTPUT_BLOB_NAME);

    // Create GPU buffers on device
    CHECK(cudaMalloc(&buffers[inputIndex], batchSize * IMAGE_SIZE * sizeof(float)));
    CHECK(cudaMalloc(&buffers[outputIndex], batchSize * OUTPUT_SIZE * sizeof(float)));

    // Create stream
    cudaStream_t stream;
    CHECK(cudaStreamCreate(&stream));

    // DMA input batch data to device, infer on the batch asynchronously, and DMA output back to host
    CHECK(cudaMemcpyAsync(buffers[inputIndex], input, batchSize * IMAGE_SIZE * sizeof(float), cudaMemcpyHostToDevice, stream));
    float ms;
//    cudaEventRecord(start, stream);
    context.enqueue(batchSize, buffers, stream, nullptr);

    CHECK(cudaMemcpyAsync(batchOutput, buffers[outputIndex], batchSize * OUTPUT_SIZE * sizeof(float), cudaMemcpyDeviceToHost, stream));
    cudaStreamSynchronize(stream);

    // Release stream and buffers
    cudaStreamDestroy(stream);
    CHECK(cudaFree(buffers[inputIndex]));
    CHECK(cudaFree(buffers[outputIndex]));
}

void CNN::FeatureExtractBatch(const std::vector<cv::Mat> &frames, const std::vector<int> &batchSizeVec, VIDEO &feature)
{


    for (size_t batch = 0; batch < batchSizeVec.size(); ++batch)
    {
        batchSize = batchSizeVec[batch];
        float *data = (float *)malloc(batchSize * IMAGE_SIZE * sizeof(float));
        float *batchOutput = (float *)malloc(batchSize * OUTPUT_SIZE * sizeof(float));

        Images2Data(frames, batchSize, batch, data);


        Inference(device, *context, data, batchOutput, batchSize);

        int batchOutSize = batch * MAX_BATCHSIZE;
        for (long i = 0; i < batchSize * OUTPUT_SIZE; ++i)
        {
            feature[batchOutSize + i / OUTPUT_SIZE].feature[i % OUTPUT_SIZE] = batchOutput[i];

        }

        if(data != NULL)
        {
            free(data);
            data = NULL;
        }

        if(batchOutput != NULL)
        {
            free(batchOutput);
            batchOutput = NULL;
        }
    }
}

void CNN::Images2Data(const std::vector<cv::Mat> &frames, const int batchSize, const int batch, float *data)
{

    #pragma omp parallel for
    for (size_t i = 0; i < batchSize; ++i)
    {
        if (3 != frames[i].channels())
        {
            std::cerr << "only support image with 3 channels" << std::endl;
            exit(0);
        }

        cv::Mat image;
        cv::resize(frames[batch * MAX_BATCHSIZE + i], image, cv::Size(INPUT_H, INPUT_W));

        for (int c = 0; c < INPUT_C; ++c)
        {
            // the color image to input should be in BGR order
            for (size_t j = 0, volChl = INPUT_H * INPUT_W; j < volChl; ++j)
            {
                data[i * IMAGE_SIZE + c * volChl + j] =
//                        (float(image.data[j * INPUT_C + 2 - c]) - means[2 - c]) * 0.017f;//mobilenetv2-pytorch and MobileNetv2-caffe
                        (float(image.data[j * INPUT_C + 2 - c]));// - means[2 - c]) * 0.017f;
//                        (float(image.data[j * INPUT_C ]));
//                (float(image.data[j * INPUT_C + 2 - c]) - means[c]) * 0.017f;//0.913


            }
        }
    }
}

void CNN::SerializeModel(const std::string serializedModelFile)
{
    std::ifstream inputModel(serializedModelFile);
    std::string cachedEngine = "";

    if(!inputModel)
    {
        std::cout << "can't open serializedModelFile!" << std::endl;
    }

    inputModel.seekg(0, std::ios::beg);
    while (inputModel.peek() != EOF) {
        std::stringstream buffer;
        buffer << inputModel.rdbuf();
        cachedEngine.append(buffer.str());
    }

    inputModel.close();
    IRuntime* runtime = createInferRuntime(gLogger);
    assert(runtime != nullptr);

    engine = runtime->deserializeCudaEngine(cachedEngine.data(), cachedEngine.size(), nullptr);
    assert(engine != nullptr);

    if (runtime != nullptr)
    {
        runtime->destroy();
    }

    context = engine->createExecutionContext();
    assert(context != nullptr);
}


void CNN::Map(const VIDEO &data, cv::Mat &dst)
{
    if (data.empty())
    {
        return;
    }

    const size_t height = data.size(), width = data.at(0).feature.size();
    dst = cv::Mat(height, width, CV_64FC1);

    double *p;

    for (size_t i = 0; i < height; ++i)
    {
        p = dst.ptr<double>(i);

        for (size_t j = 0; j < width; ++j)
        {
            p[j] = static_cast<double>(data[i].feature[j]);
        }
    }

//    cv::reduce(dst, dst, 0, cv::REDUCE_AVG); //frame-wise pooling
}

cv::Mat CNN::Normal(cv::Mat &src)
{
//    cv::Mat aa(2, 3, CV_64F, src);
//    std::cout<<aa<<std::endl;
    cv::Mat temp1, temp2, temp3;
    pow(src, 2, temp1);
//    std::cout<<"temp1: "<<temp1<<endl;
    reduce(temp1, temp2, 1, cv::REDUCE_SUM); // calculate sum of each col
//    reduce(temp1, temp2, 1, CAP_OPENCV_MJPEG); // calculate sum of each col

//    std::cout<<"recude temp2: "<<temp2<<endl;
    sqrt(temp2, temp2);
//    std::cout<<"temp2-2: "<<temp2<<"\t"<<temp2.size()<<"aa.size"<<aa.size()<<aa.rows<<aa.cols<<endl;
    repeat(temp2, 1, src.cols, temp3);
//    std::cout<<"tempe3: "<<temp3<<"\t"<<temp3.size()<<endl;
    divide(src, temp3, src);
    return src;
//    std::cout<<aa<<std::endl;

}

cv::Mat CNN::CosinSimilarityMatrix(const cv::Mat A, const cv::Mat B)
{
    cv::Mat similarity;
    cv::Mat detA, detB;

    Determinant(A, detA, 1, B.rows);
    Determinant(B, detB, 1, A.rows);

    cv::multiply(detA, detB.t(), similarity);
    similarity = A * B.t() / similarity;

    return similarity;
}

void CNN::Determinant(const cv::Mat src, cv::Mat &dst, const int axis
                         , const int repeat, const bool square)
{
    cv::Mat sum;

    cv::multiply(src, src, sum);
    cv::reduce(sum, sum, axis, cv::REDUCE_SUM);

    if (not square)
    {
        cv::sqrt(sum, sum);
    }

    if (repeat > 1)
    {
        if (1 == axis)
        {
            cv::repeat(sum, 1, repeat, dst);
        }
        else if (0 == axis)
        {
            cv::repeat(sum, repeat, 1, dst);
        }
    }
    else
    {
        dst = sum;
    }
}


FRAME::FRAME()
{
    this->number = 0;
}

FRAME::FRAME(const size_t size, const FEATURE_TYPE value)
{
    this->feature = FEATURE(size, value);
}


FRAME::FRAME(const FRAME &f)
{
    this->number = f.number;
    this->feature = f.feature;
}

FRAME &FRAME::operator=(const FRAME &f)
{
    this->number = f.number;
    this->feature = f.feature;

    return *this;
}

void FRAME::clear()
{
    this->feature.clear();
    this->number = 0;
}

size_t FRAME::size() const
{
    return this->feature.size();
}

bool FRAME::empty() const
{
    return this->feature.empty();
}


