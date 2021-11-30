#include <iostream>
#include "opencv2/opencv.hpp"
//


#include <stdio.h>
#include <cv.h>

void test()
{
    int i;
    double r_vec[3]={-2.100418,-2.167796,0.273330};
    double R_matrix[9];
    CvMat pr_vec;
    CvMat pR_matrix;

    cvInitMatHeader(&pr_vec,1,3,CV_64FC1,r_vec,CV_AUTOSTEP);
    cvInitMatHeader(&pR_matrix,3,3,CV_64FC1,R_matrix,CV_AUTOSTEP);
    cvRodrigues2(&pr_vec, &pR_matrix,0);

    for(i=0; i<9; i++)
    {
        printf("%f\n",R_matrix[i]);
    }
}




int main() {

    double FONTscale = 1.0;
    std::string str;
    cv::Mat src = cv::Mat::zeros(480, 640, CV_8UC1);

    // b = a.clone();    深拷贝
    cv::Mat check_clone;
    check_clone = src.clone();

    str = "clone";
    cv::putText(check_clone, str, cv::Point(200, 100), cv::FONT_ITALIC, FONTscale, cv::Scalar(255, 0, 0), 2);
    cv::imshow("check_clone", check_clone);

    // a.copyTo(b);    深拷贝
    cv::Mat check_copyTo;
    src.copyTo(check_copyTo);

    str = "copyTo";
    cv::putText(check_copyTo, str, cv::Point(200, 150), cv::FONT_ITALIC, FONTscale, cv::Scalar(255, 0, 0), 2);
    cv::imshow("check_copyTo", check_copyTo);

    // b = a;    浅拷贝
    cv::Mat check_equal;
    check_equal = src;

    str = "equal";
    cv::putText(check_equal, str, cv::Point(200, 200), cv::FONT_ITALIC, FONTscale, cv::Scalar(255, 0, 0), 2);
    cv::imshow("check_equal", check_equal);

    // b(a);    浅拷贝
    cv::Mat check_brackets(src);

    str = "brackets";
    cv::putText(check_brackets, str, cv::Point(200, 250), cv::FONT_ITALIC, FONTscale, cv::Scalar(255, 0, 0), 2);
    cv::imshow("check_brackets", check_brackets);

    // b(a); c = b;    2次浅拷贝 一样是浅拷贝
    cv::Mat check_b(src);
    cv::Mat check_q;
    check_q = check_b;

    str = "2222";
    cv::putText(check_q, str, cv::Point(200, 300), cv::FONT_ITALIC, FONTscale, cv::Scalar(255, 0, 0), 2);
    cv::imshow("check_q", check_q);

    cv::imshow("src", src);

    std::vector<cv::Mat> imageLists;
    imageLists.push_back(src);
    printf("src add: %p\n",src.data);
    src.release();
    printf("src add after release(): %p\n",src.data);

    cv::Mat newMap = imageLists[0];
    printf("imageLists[0] add : %p\n",imageLists[0].data);

    imageLists[0] = cv::Mat();
    printf("imageLists[0] add after equal(): %p\n",imageLists[0].data);

    cv::imshow("newMap", newMap);
    std::cout<<src<<"  "<<imageLists[0]<<std::endl;
    printf("newMap add : %p\n",newMap.data);
    cv::Mat newMap1 = newMap;
    newMap = newMap.clone();
    printf("newMap add after clone() : %p\n",newMap.data);
    printf("newMap1 add after clone() : %p\n",newMap1.data);

    cv::waitKey();

//    // check ROI    浅拷贝
//    cv::Mat img = cv::imread("timg.jpg");
//
//    cv::Mat img_roi;
//    img_roi = img(cv::Rect(400, 200, 100, 100));
//
//    str = "girl";
//    cv::putText(img_roi, str, cv::Point(50, 50), cv::FONT_ITALIC, FONTscale, cv::Scalar(255, 0, 0), 2);
//    cv::imshow("img", img);
//    cv::imshow("img_roi", img_roi);
//    cv::waitKey();
//

    return 0;
}




//int main()
//{
//    int abc = 10;
//    cv::Mat image1 = cv::imread("/home/indemind/Code/PycharmProjects/darknet/darknet_ab/chart1030.png");
//    if (image1.empty())
//    {
//        std::cout<<"image.empty()";
//    }
//    else
//    {
//        std::cout<<"image.empty() is false";
//    }
//
//    cv::Mat image2 = image1.clone();
//    std::vector<cv::Mat> va;
//    va.push_back(image1.clone());
//
//    cv::Mat image_equal = image1;
//    cv::merge(va,image1);
//
//
//
//    cv::imshow("1",image1);
////    cv::imshow("2",image2);
////    cv::imshow("equal",image_equal);
////
////
////
////
//    cv::waitKey(0);
//
//    return  0;
//}

//
//int main(int argc, char *argv[])
//{
//
//    cv::VideoCapture capture1,capture;
//    capture.open(0);  //打开摄像头，只要一个摄像头，默认是0; 笔记本上有自带的摄像头,再插入usb摄像头应该是1
//    capture1.open(1);  //打开摄像头，只要一个摄像头，默认是0; 笔记本上有自带的摄像头,再插入usb摄像头应该是1
//
//    if(capture.isOpened())  //打开摄像头
//    {
//        std::cout<<"video is open";
//
//    }
//
//
//
//    cv::Mat frame,frame1; //定义一个矩阵接受帧
////    cv::namedWindow("camera",1);  //定义显示帧
//    int i=0;
//    for(;;)
//    {
//        std::cout<<"show image"<<std::endl;
//
//        capture>>frame; //取出一帧
//        capture>>frame1;
//        if (!frame.empty())
//        {
//            cv::imshow("camera", frame);   //在窗口显示
//            i++;
//            std::cout<<i<<"\n";
//        }
//        else
//        {
//
//        }
//        if (!frame1.empty())
//        {
//            cv::imshow("camera1", frame1);   //在窗口显示
//            i++;
//            std::cout<<i<<"\n";
//        }
//        else
//        {
//
//        }
//        cv::waitKey(1);
//
//    }
//
//    return 0;
//}