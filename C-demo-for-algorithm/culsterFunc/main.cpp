#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <io.h>
#include <string>
#include<vector>
#include <sys/time.h> //test

//#include <opencv2/core/core.hpp>
//#include <opencv2/core/mat.hpp>

#include <iostream>
#include <dirent.h>
using namespace std;
using namespace cv;

int aHashCodeFeature(vector<Mat> srcVec, Mat &pHashCode);

int fingerprint(Mat src, vector<int> &hash);

/*计算欧式距离*/
float calcuDistance(uchar* ptr, uchar* ptrCen, int cols)
{
    float d = 0.0;
    for (size_t j = 0; j < cols; j++)
    {
       d += (double)(ptr[j] - ptrCen[j])*(ptr[j] - ptrCen[j]);
    }
    d = sqrt(d);
    return d;
}

/** @brief   最大最小距离算法
 @param data  输入样本数据，每一行为一个样本，每个样本可以存在多个特征数据
 @param Theta 阈值，一般设置为0.5，阈值越小聚类中心越多
 @param centerIndex 聚类中心的下标
 @return 返回每个样本的类别，类别从1开始，0表示未分类或者分类失败
*/
cv::Mat  MaxMinDisFun(cv::Mat data, float Theta, vector<int> &centerIndex)
{
    double maxDistance = 0;
    int start = 0;    //初始选一个中心点
    int index = start; //相当于指针指示新中心点的位置
    int k = 0;        //中心点计数，也即是类别
    int dataNum = data.rows; //输入的样本数
    cout<<"dataNum: "<<dataNum<<endl;
                                                     //vector<int>	centerIndex;//保存中心点
    cv::Mat distance = cv::Mat::zeros(cv::Size(1, dataNum), CV_32FC1); //表示所有样本到当前聚类中心的距离
    cv::Mat minDistance = cv::Mat::zeros(cv::Size(1, dataNum), CV_32FC1); //取较小距离


    cv::Mat classes = cv::Mat::zeros(cv::Size(1, dataNum), CV_32SC1);     //表示类别
    centerIndex.push_back(index); //保存第一个聚类中心

    for (size_t i = 0; i < dataNum; i++)
    {
        uchar* ptr1 = data.ptr<uchar>(i);
        uchar* ptrCen = data.ptr<uchar>(centerIndex.at(0));
        float d= calcuDistance(ptr1, ptrCen, data.cols);
        distance.at<float>(i, 0) = d;
        classes.at<int>(i, 0) = k + 1;
        if (maxDistance < d)
        {
            maxDistance = d;
            index = i; //与第一个聚类中心距离最大的样本
        }
    }

    minDistance = distance.clone();
    double minVal; double maxVal; cv::Point minLoc; cv::Point maxLoc;
    maxVal = maxDistance;
    while (maxVal > (maxDistance*Theta))
    {
        k = k + 1;
        centerIndex.push_back(index); //新的聚类中心
        for (size_t i = 0; i < dataNum; i++)
        {
            uchar* ptr1 = data.ptr<uchar>(i);
            uchar* ptrCen = data.ptr<uchar>(centerIndex.at(k));
            float d = calcuDistance(ptr1, ptrCen, data.cols);
            distance.at<float>(i, 0) = d;
            //按照当前最近临方式分类，哪个近就分哪个类别
            if (minDistance.at<float>(i, 0) > distance.at<float>(i, 0))
            {
                minDistance.at<float>(i, 0) = distance.at<float>(i, 0);
                classes.at<int>(i, 0) = k + 1;
            }
        }
        //查找minDistance中最大值
        cv::minMaxLoc(minDistance, &minVal, &maxVal, &minLoc, &maxLoc);
        index = maxLoc.y;
    }
    return classes;
}



int main()
{
    struct timeval start, end;

    struct dirent *ptr;
     DIR *dir;
     string PATH = "/home/ljdong/code/qt/dna_data/VCDB/core_dataset/saving_private_ryan_omaha_beach";
     dir=opendir(PATH.c_str());
     vector<string> files;
     cout << "文件列表: "<< endl;
     while((ptr=readdir(dir))!=NULL)
     {

         //跳过'.'和'..'两个目录
         if(ptr->d_name[0] == '.')
             continue;
         //cout << ptr->d_name << endl;
         files.push_back(ptr->d_name);
     }

     for(int i = 0;i < files.size(); ++i)
     {
        VideoCapture capture;
        capture.open(PATH + '/' + files[i]);
        Mat frame;
        vector<Mat> imageVec;


        std::cout<<files[i]<<std::endl;
        while (capture.read(frame))
        {
            if (frame.empty())
            {
                cout<<"read image error!"<<endl;
                return -1;
            }
            cvtColor( frame, frame, CV_BGR2GRAY );
            resize(frame, frame, Size(32, 32));

            imageVec.push_back(frame);
        }

        Mat dsthash(Size(64, imageVec.size()),0);
        gettimeofday(&start, nullptr);
        aHashCodeFeature(imageVec,dsthash);
        gettimeofday(&end, nullptr);
        double timeuse = (1000000*(end.tv_sec-start.tv_sec) + end.tv_usec-start.tv_usec) * 1.0 / 1000;
        cout<<"imageVec.soze(): "<<imageVec.size()<<" time used for feature hashcode: "<<timeuse<<"  average: "<<timeuse/imageVec.size()<<endl;

        vector<int> centerIndex;
        float Theta = 0.5;
        gettimeofday(&start, nullptr);
        cv::Mat classes = MaxMinDisFun(dsthash, 0.5, centerIndex);
        gettimeofday(&end, nullptr);
        timeuse = (1000000*(end.tv_sec-start.tv_sec) + end.tv_usec-start.tv_usec) * 1.0 / 1000;
        cout<<"imageVec.soze(): "<<imageVec.size()<<" time used for cluster: "<<timeuse<<"  average: "<<timeuse/imageVec.size()
           <<"average key frame: "<<timeuse/centerIndex.size() <<endl;
        //        cout << "类别classes=\n" << classes << endl;
        for(size_t i= 0; i < centerIndex.size(); ++i)
        {
            cv::imwrite("image_center/" + to_string(centerIndex[i]) + ".jpg",imageVec[centerIndex[i]]);
//            cout << centerIndex[i] << " ";
        }
        cout << "\n\n" << centerIndex.size()<<endl;
        int num_i = 0;
        for (int i = 1; i < dsthash.rows; ++i)
        {
            if (classes.at<int>(i,0) == 0)
            {
                cout<<"0表示未分类或者分类失败"<<endl;
                exit(0);
            }
            if(classes.at<int>(i,0) !=classes.at<int>(i-1,0))
            {
                num_i++;
//                cout<<classes.at<int>(i,0) <<" ";
                cv::imwrite("image_class/" + to_string(i) + ".jpg",imageVec[i]);

            }
        }
        cout<<"\nnum_i: "<<num_i<<endl;
     }
    system("pause");
    waitKey();
    return 0;
}

int fingerprint(Mat src, vector<int> &pHashCode)
{
    Mat srcDCT;

    resize(src, src, Size(32, 32));
    src.convertTo(src, CV_32F);
    //DCT系数矩阵
    dct(src, srcDCT);
    srcDCT = abs(srcDCT);
    double sum = 0;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            sum += srcDCT.at<float>(i,j);
        }
    }

    double average = sum/64;

    pHashCode.resize(64);
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            pHashCode[i * 8 + j] = srcDCT.at<float>(i,j) > average ? 1:0;
        }
    }
    return 0;
}
int aHashCodeFeature(vector<Mat> srcVec, Mat &pHashCode)
{

    for (int n = 0; n < srcVec.size(); ++n)
    {
        Mat src = srcVec[n];
//        resize(src, src, Size(32, 32));
        //to  single channel
        src.convertTo(src, CV_32F);

        Mat srcDCT;
        //DCT系数矩阵
        dct(src, srcDCT);

        srcDCT = abs(srcDCT);
        double sum = 0;
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                sum += srcDCT.at<float>(i,j);
            }
        }

        double average = sum/64;
        for(int i = 0; i <64 ;++i)
        {
            pHashCode.at<char>(n,i) = srcDCT.at<float>(i / 8,i % 8) > average ? 1 : 0;
        }
    }
    return 0;
}

