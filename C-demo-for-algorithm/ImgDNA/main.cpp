#include"readfromdir.h"
#include <sys/stat.h>
#include <sys/types.h>
#include"cnn.h"
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

//#define CLASS_IMAGE

using namespace cv;
int main()
{
    string referDir = "/home/ljdong/data/dna_data/imageDataset/refer/Parasite/";
    string trainDir = "/home/ljdong/data/dna_data/imageDataset/train/Parasite/";
    string modelNet = "/home/ljdong/code/qt/build-VideoDNA-Desktop_Qt_5_10_0_GCC_64bit-Debug/test_video_DNA/model/MobileNet_model.bin";
//    string modelNet = "/home/ljdong/PycharmProjects/tensorrt/TensorRT-sampleResNet50/model/MobileNet_v2_pool6.bin";


//    string modelNet = "/home/ljdong/code/qt/build-VideoDNA-Desktop_Qt_5_10_0_GCC_64bit-Debug/test_video_DNA/model/inception_original.trt";
//        string modelNet = "/home/ljdong/PycharmProjects/tensorrt/model_trt/MobileNetV2_Softmax_IQiyi_53.trt";


    vector<string> referFileNames;
    vector<string> referFullFileNames;

    vector<string> trainFileNames;
    vector<string> trainFullFileNames;

#ifdef CLASS_IMAGE
    string dirName = "";
    vector<string> fullFileNames;
    ReadFromDir(dirName,fileNames,fullFileNames);
    ClassImg(fullFileNames);
#endif

    ReadFromDir(referDir,referFileNames,referFullFileNames);
    ReadFromDir(trainDir,trainFileNames,trainFullFileNames);

    CNN cnn;
    cnn.Init(modelNet);

    vector<cv::Mat> referMat;
    vector<cv::Mat> trainMat;

    cnn.ReadImages(referFullFileNames,referMat);
    cnn.ReadImages(trainFullFileNames,trainMat);

    VIDEO referFeature;
    referFeature.resize(referFullFileNames.size(), FRAME(cnn.OUTPUT_SIZE, 0));

    VIDEO trainFeature;
    trainFeature.resize(trainFullFileNames.size(), FRAME(cnn.OUTPUT_SIZE, 0));

    cnn.FeatureExtract(referMat,referFeature);
    cnn.FeatureExtract(trainMat,trainFeature);

    cv::Mat similarity;

    cnn.SimilarityMatrix(trainFeature, referFeature, similarity);

    vector<int> maxIndex(similarity.rows);

    cnn.MaxIndex(maxIndex,similarity);

    float accuracy = cnn.CalculateAccuracy(maxIndex,referFullFileNames,trainFullFileNames);

    return 0;


}
