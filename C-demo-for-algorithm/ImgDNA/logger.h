#ifndef LOGGER_NVINFER1_H
#define LOGGER_NVINFER1_H
#include <NvInfer.h>
#include <string>
#include <vector>
#include <fstream>
#include <cassert>
#include <iostream>



#define CHECK(status)									\
{														\
    if (status != 0)									\
    {													\
        std::cout << "Cuda failure: " << status;		\
        abort();										\
    }													\
}

class Logger : public nvinfer1::ILogger
{
public:
    void log(nvinfer1::ILogger::Severity severity, const char* msg) override
    {
        // suppress info-level messages
        if (severity == Severity::kINFO) return;

        switch (severity)
        {
            case Severity::kINTERNAL_ERROR: std::cerr << "INTERNAL_ERROR: "; break;
            case Severity::kERROR: std::cerr << "ERROR: "; break;
            case Severity::kWARNING: std::cerr << "WARNING: "; break;
            case Severity::kINFO: std::cerr << "INFO: "; break;
            default: std::cerr << "UNKNOWN: "; break;
        }
        std::cerr << msg << std::endl;
    }
};
#endif // LOGGER_NVINFER1_H
