#ifndef MOBILENET_H
#define MOBILENET_H

#include "logger.h"
#include <NvCaffeParser.h>
#include <sstream>
#include <cuda_runtime_api.h>

#include <opencv2/videoio.hpp>

using namespace std;
using namespace nvinfer1;
using namespace nvcaffeparser1;

const std::string SPLIT_INNER{","};


typedef  std::vector< std::pair<double, size_t> > CLASSIFY_RESULT;
typedef double FEATURE_TYPE;
typedef unsigned long long FRAME_NUM_TYPE;
using FEATURE = std::vector<FEATURE_TYPE>;
struct FRAME
{
    FEATURE feature;
    FRAME_NUM_TYPE number;

    FRAME();
    FRAME(const size_t size, const FEATURE_TYPE value);
    FRAME(const FRAME& f);

    FRAME& operator= (const FRAME& f);
    void clear();
    size_t size() const;
    bool empty() const;
    std::string Serialize() const;
    void Parse(const std::string &sequence);
};




using VIDEO = std::vector<FRAME>;

class CNN
{
public:
    CNN();
    ~CNN();

public:
    bool Init(const std::string serializedModelFile);
    void FeatureExtract(const cv::Mat& img, vector<long>& feature);
    void FeatureExtract(const std::vector<cv::Mat> &frames, VIDEO& feature);
    void Map(const VIDEO &data, cv::Mat &dst);
    cv::Mat CosinSimilarityMatrix(const cv::Mat A, const cv::Mat B);
    void GetInputSize(int &width, int &height);
    void ReadImages(const vector<string> &FullfileNames, vector<cv::Mat> &matVec);
    void SimilarityMatrix(const VIDEO &trainFeature, const VIDEO &referFeature, cv::Mat &similarity);

    void MaxIndex(vector<int> &maxIndex, const cv::Mat &similarity);
    float CalculateAccuracy(vector<int> &maxIndex, const vector<string> &referFullFileNames, const vector<string> &trainFullFileNames);
private:
    void SerializeModel(const std::string serializedModelFile);
    void Inference(int device, IExecutionContext &context, float *input, float *batchOutput, int batchSize);
    void FeatureExtractBatch(const std::vector<cv::Mat> &frames, const std::vector<int> &batchSizeVec, VIDEO &feature);
    void Images2Data(const std::vector<cv::Mat> &frames, const int batchSize, const int batch, float *data);

    static void Determinant(const cv::Mat src, cv::Mat& dst, const int axis=0, const int repeat=0
            , const bool square=false);
private:
    Logger gLogger;
    const int INPUT_C = 3;
    const int INPUT_W = 224;
    const int INPUT_H = 224;
    const int IMAGE_SIZE = 150528; //INPUT_C * INPUT_W * INPUT_H
    const float means[3] = {103.94f, 116.78f, 123.68f};
    IRuntime* runtime;
    ICudaEngine* engine;
    IExecutionContext* context;
    const float* meanData;
    const char* INPUT_BLOB_NAME = "data";
    const char* OUTPUT_BLOB_NAME = "pool6";
    const int MAX_BATCHSIZE = 64; //should less than serialized model's MAX_BATCHSIZE
//    const char* INPUT_BLOB_NAME = "input";
//    const char* OUTPUT_BLOB_NAME = "output";
//    const int MAX_BATCHSIZE = 32; //should less than serialized model's MAX_BATCHSIZE
    int device = 0;
    int batchSize = 0;
public:
    const int OUTPUT_SIZE = 1024; // should less than  DNAC::FEATURE_LENGTH

    cv::Mat Normal(cv::Mat &src);
};

#endif // MOBILENET_H
