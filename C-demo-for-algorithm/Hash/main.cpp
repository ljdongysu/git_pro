#include <iostream>
#include <stdio.h>
#include <fstream>
#include <io.h>
#include <string>
#include<vector>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/core/mat.hpp>
using namespace std;
using namespace cv;
//int fingerprint(Mat src, Mat* hash);
int afingerprint(Mat src, vector<int> &hash);
int fingerprint(Mat src, Mat* hash);
int HashCodeFeature(vector<Mat> srcVec, Mat &pHashCode);


void newdel(Mat dst,Mat *srchash,int i)
{
    Mat dsthash;
    fingerprint(dst, &dsthash);
    int d = 0;
     for (int n = 0; n < srchash->size[1]; n++)
         if (srchash->at<uchar>(0,n) != dsthash.at<uchar>(0,n)) d++;

     cout <<"infunction " << i <<"  distance=  " <<d<<"\n";

}


int main()
{
    Mat src = imread("../build-culsterFunc-Desktop_Qt_5_10_0_GCC_64bit-Debug/images/0.jpg", 0);
    if(src.empty())
    {
        cout << "the image is not exist" << endl;
        return -1;
    }

//    outPutMat(src);

    vector<int >srchashvec;
    vector<int >dsthashvec;
    afingerprint(src, srchashvec);
    Mat srchash;

    //
    fingerprint(src,&srchash);


    vector<Mat> imageVec;
    for(int i = 1; i <= 2011; i += 30)
    {
        string number;
        stringstream ss;
        ss << i;
        ss >> number;
        string path = "../build-culsterFunc-Desktop_Qt_5_10_0_GCC_64bit-Debug/images/" + number +".jpg";
        Mat dst = imread(path, 0);
        imageVec.push_back(dst);
        if(dst.empty())
        {
            cout << "the image is not exist" << endl;
            return -1;
        }
        afingerprint(dst, dsthashvec);
        int d = 0;
        for (int i = 0; i < dsthashvec.size(); ++i)
        {
            if(srchashvec[i] != dsthashvec[i])
                d++;
        }

//        cout<<"size[1]: "<< srchash.size[1]<<endl;
        cout <<"person" << i <<"  distance=  " <<d<<"\n";
    newdel(dst, &srchash, i);

    }

    Mat dsthash(Size(64, imageVec.size()),0);



    HashCodeFeature(imageVec,dsthash);
    for (int i = 0; i < imageVec.size(); ++i)
    {
          int dd = 0;
        for (int j = 0; j < dsthash.cols; ++j)
        {
            if(srchashvec[j] != dsthash.at<char>(i,j))
            {
                dd++;
            }

        }
        cout <<"person" << i <<"  distance=  " <<dd<<"\n";

    }

    system("pause");
    return 0;
}


int afingerprint(Mat src, vector<int> &pHashCode)
{

    resize(src, src, Size(32, 32));
    //to  single channel
    src.convertTo(src, CV_32F);
    Mat srcDCT;
    //DCT系数矩阵
    dct(src, srcDCT);

    srcDCT = abs(srcDCT);
    double sum = 0;
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            sum += srcDCT.at<float>(i,j);

    double average = sum/64;
    Mat phashcode= Mat::zeros(Size(8, 8), CV_8U);

//    vector<int > pHashCode(64);
    pHashCode.resize(64);
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
//            phashcode.at<char>(i,j) = srcDCT.at<float>(i,j) > average ? 1:0;
            pHashCode[i * 8 + j] = srcDCT.at<float>(i,j) > average ? 1:0;

//    *hash = phashcode.reshape(0,1).clone();
    return 0;
}

int HashCodeFeature(vector<Mat> srcVec, Mat &pHashCode)
{
    vector<double> averageVec;
//    vector<int>


    for (int n = 0; n < srcVec.size(); ++n)
    {
        Mat src = srcVec[n];
        resize(src, src, Size(32, 32));
        //to  single channel
        src.convertTo(src, CV_32F);
        Mat srcDCT;
        //DCT系数矩阵
        dct(src, srcDCT);

        srcDCT = abs(srcDCT);
        double sum = 0;
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
                sum += srcDCT.at<float>(i,j);

        double average = sum/64;
        averageVec.push_back(average);
        for(int i = 0; i <64 ;++i)
        {
            pHashCode.at<char>(n,i) = srcDCT.at<float>(i / 8,i % 8) > average ? 1 : 0;
        }
//        Mat phashcode= Mat::zeros(Size(8, 8), CV_8U);
    }
////    vector<int > pHashCode(64);
//    pHashCode.resize(64);
//    for (int i = 0; i < 8; i++)
//        for (int j = 0; j < 8; j++)
////            phashcode.at<char>(i,j) = srcDCT.at<float>(i,j) > average ? 1:0;
//            pHashCode[i * 8 + j] = srcDCT.at<float>(i,j) > average ? 1:0;

////    *hash = phashcode.reshape(0,1).clone();
    return 0;
}




int fingerprint(Mat src, Mat* hash)
{
    resize(src, src, Size(32, 32));
    src.convertTo(src, CV_32F);
    Mat srcDCT;
    dct(src, srcDCT);
    srcDCT = abs(srcDCT);
    double sum = 0;
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            sum += srcDCT.at<float>(i,j);

    double average = sum/64;
    Mat phashcode= Mat::zeros(Size(8, 8), CV_8U);
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            phashcode.at<char>(i,j) = srcDCT.at<float>(i,j) > average ? 1:0;

    *hash = phashcode.reshape(0,1).clone();
    return 0;
}
