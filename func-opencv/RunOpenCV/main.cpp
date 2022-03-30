#include <iostream>
#include "opencv2/opencv.hpp"
//
#include<unistd.h>

#include <stdio.h>
#include <cv.h>
struct Box
{
    float x, y, w, h, prob;
};
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
#define RAND_INT(a, b) (rand() % (b-a+1))+ a
void TestColor(cv::Mat image)
{
    const cv::Scalar COLOR_BACK(80, 80, 80);
    const cv::Scalar COLOR_TEXT(150, 150, 150);
    const cv::Scalar COLOR_AXIS(0, 0, 200);
    const cv::Scalar COLOR_VIEW(255, 50, 50);
    const cv::Scalar COLOR_OBJECT(50, 150, 50);
    const cv::Scalar COLOR_LAST_OBJECT(0, 250, 250);
    const cv::Scalar COLOR_FORGROUND(0, 140, 255);
    const cv::Scalar RED(0, 0, 255);
    const cv::Scalar GREEN(0, 255, 0);
    const cv::Scalar BLUE(255, 0, 0);

    cv::Scalar(RAND_INT(180, 250), RAND_INT(180, 250), RAND_INT(180, 250));

    for (int i = 0; i < 10; ++i)
    {
        std::string str = std::to_string(i);
        cv::line(image, cv::Point(10, 10), cv::Point(110, 110),
                 cv::Scalar(RAND_INT(180, 250), RAND_INT(180, 250), RAND_INT(180, 250)), 2);
//    }
        cv::imshow(str, image);
        cv::waitKey(0);
    }


}

void ResizeByPadding(const cv::Mat src, cv::Mat &dst, cv::Size size)
{
    if (src.empty() or src.cols == 0 or src.rows == 0)
    {
        return;
    }
    if (size.height == 0 or size.width == 0)
    {
        return;
    }

    cv::Scalar value(128);

    if (src.channels() == 3)
    {
        value = cv::Scalar(128,128,128);
    }

    float ratioWidth = src.cols / float(size.width);
    float ratioHeight = src.rows / float(size.height);
    int widthAdd = 0;
    int heightAdd = 0;
    bool heightBigger = ratioHeight > ratioWidth;
    float ratio = 1.0;
    if (heightBigger)
    {
        ratio = 1 / ratioHeight;
        widthAdd = size.width - src.cols * ratio;
    }
    else
    {
        ratio = 1 / ratioWidth;
        heightAdd = size.height - src.rows * ratio;

    }

    cv::resize(src, dst,cv::Size(0,0),  ratio ,ratio);

    copyMakeBorder(dst,dst,0,heightAdd,0,widthAdd, cv::BORDER_CONSTANT, value);
}

typedef struct box_label
{
    float x, y, w, h;
} box_label;

void labelResizeByPadding(box_label &truth, const int w, const int h, cv::Size dstSize)
{
    float ratioWidth = w / float(dstSize.width);
    float ratioHeight = h / float(dstSize.height);
    float ratio = 1.0;
    bool heightBigger = ratioHeight > ratioWidth;

    if (heightBigger)
    {
        ratio = (1 / ratioHeight) * ratioWidth;
        truth.x *= ratio;
        truth.w *= ratio;
    }
    else
    {
        ratio = (1 / ratioWidth) * ratioHeight;
        truth.y *= ratio;
        truth.h *= ratio;
    }
}

void labelResizeByPadding1(box_label &truth, const int w, const int h, cv::Size dstSize)
{
    float ratioWidth = w / float(dstSize.width);
    float ratioHeight = h / float(dstSize.height);
    float ratio = 1.0;
    bool heightBigger = ratioHeight > ratioWidth;

    if (heightBigger)
    {
        ratio = (1 / ratioWidth) * ratioHeight;
        truth.x *= ratio;
        truth.w *= ratio;
    }
    else
    {
        ratio = (1 / ratioHeight) * ratioWidth;
        truth.y *= ratio;
        truth.h *= ratio;
    }
}

void labelConvertPadding()
{

}

struct Image
{
    cv::Mat data;

    Image()
    {
        this->data = cv::Mat();
    }

    Image(cv::Mat image)
    {
        this->data = image;
    }

//    Image &operator=(const Image &image)
//    {
//        this->data = image.data; //.clone();
//
//        return *this;
//    }
};

std::list<Image> images;

//void SetImage( const cv::Mat &image)
//{
//
//    images.push_back(Image(image.clone()));
//
//}


void GetImageByTime(Image &lastImage)
{
    if (not images.empty())
    {
        lastImage = images.front();
        images.pop_front();
    }
}



class TestImage{

    void SetImage(const cv::Mat &image)
    {
        cv::imwrite("./imageInSetImage.jpg",image);

        sleep(10);
        cv::Mat imageTemp = image.clone();
        cv::imwrite("./imageInSetImage.jpg",imageTemp);
    }
};

struct AAA{
    int a;
    cv::Mat image;
};

int main()
{

    cv::Mat imageTest;
    imageTest.create(2,2,CV_8UC1);

    cv::Mat image = cv::imread("/home/indemind/Data/batch7_06_21_valid_extract_dataset_lit/cam02021_05_29_09_44_37_1622281477351.jpg");

    cv::imwrite("./image_before_write.jpg", image);
    std::cout<<image.u->refcount<<std::endl;
    for (int i = 0; i < image.rows; ++i)
    {
        cv::Vec<uint ,3> *dataPtr = image.ptr<cv::Vec<uint ,3>>(i);
        for (int j = 0; j < image.cols; ++j)
        {
            dataPtr[j][0] = 0;
            dataPtr[j][1] = 0;
            dataPtr[j][2] = 0;

        }
    }

    cv::imwrite("./image_after_write.jpg", image);
 }

//    int imageNumber = 0;
//
//
////    cv::Mat image = cv::imread("./2021_06_05_07_55_36_1622879736102.jpg");
////    cv::Mat image = cv::imread("/home/indemind/Code/CLionprojects/RunOpenCV/2021_06_05_07_55_36_1622879736102.jpg");
//
//    Image lastImage;
//
//    for (int i = 0; i < 2; ++i)
//    {
//        cv::Mat image = cv::imread("/home/indemind/Code/CLionprojects/RunOpenCV/2021_06_05_07_55_36_1622879736102.jpg");
//        std::cout<<&image<<std::endl;
//        std::cout<< static_cast<const void *>(image.data)<<std::endl;
//
//        cv::Mat image111 = image;
//        std::cout<< static_cast<const void *>(image111.data)<<std::endl;
//
//
//        cv::Mat imageClone = image.clone();
//        std::cout<< static_cast<const void *>(imageClone.data)<<std::endl;
//
//        std::cout<<&(image.data)<<std::endl;
//
//        SetImage(image);
//    }
//
//    while (not images.empty())
//    {
//        imageNumber += 1;
//        GetImageByTime(lastImage);
//        cv::imwrite(std::to_string(imageNumber) + ".jpg", lastImage.data);
//    }
//
//}


//
//
//    cv::Mat imageTest = image.clone();
//    cv::Mat image3 = image.clone();
//    ResizeByPadding(imageTest,imageTest,cv::Size(416,800));
////    cv::Mat image2 = cv::imread("./2021_06_05_07_55_36_1622879736102.jpg");
//    cv::Mat image2 = cv::imread("/home/indemind/Code/CLionprojects/RunOpenCV/2021_06_05_07_55_36_1622879736102.jpg");
//
//    cv::resize(image2,image2,cv::Size(416,416));
//
//    cv::Mat imaget(3,6,CV_8UC1,cv::Scalar(128));
////    imaget.create(3,6,CV_8UC1,cv::Scalar(128));
//    std::cout<<imaget<<std::endl;
//
//    cv::Rect boxRect, boxRect2;
//    boxRect.x = 261;
//    boxRect.y = 165;
//    boxRect.width = 378;
//    boxRect.height = 148;
//    boxRect2.x = 287;
//    boxRect2.y = 186;
//    boxRect2.width = 55;
//    boxRect2.height = 114;
//
//    box_label truth;
//    truth.x =   (boxRect.x + boxRect.width/2)/float(image.cols);
//    truth.y =   (boxRect.y + boxRect.height/2)/float(image.rows);
//    truth.w = boxRect.width/float(image.cols);
//    truth.h = boxRect.height/float(image.rows);
//
//    labelResizeByPadding(truth, image.cols, image.rows, cv::Size(416,800));
//
//    cv::Rect boxRect3;
//    boxRect3.x = (truth.x - truth.w / 2)*imageTest.cols;
//    boxRect3.width = truth.w*imageTest.cols;
//    boxRect3.y = (truth.y - truth.h / 2)*imageTest.rows;
//    boxRect3.height = truth.h*imageTest.rows;
//    cv::rectangle(imageTest, boxRect3,  cv::Scalar(0,255,255), 2);
//
//    cv::imshow("imageTest", imageTest);
//
//    cv::Rect boxRectRatio;
//    box_label truth1 = truth;
//    labelResizeByPadding1(truth1, image.cols, image.rows, cv::Size(416,800));
//
//
//    cv::Rect boxRect4;
//    boxRect4.x = (truth1.x - truth1.w / 2)*image3.cols;
//    boxRect4.width = truth1.w*image3.cols;
//    boxRect4.y = (truth1.y - truth1.h / 2)*image3.rows;
//    boxRect4.height = truth1.h*image3.rows;
//
//    cv::rectangle(image3, boxRect4,  cv::Scalar(0,255,255), 2);
//
//    cv::imshow("image3", image3);
//
//    std::cout<<image.size()<<std::endl;
//    std::cout<<image2.size()<<std::endl;
//    std::cout<<imageTest.size()<<std::endl;
//
//    cv::rectangle(image, boxRect,  cv::Scalar(0,255,255), 2);
//    cv::rectangle(image2, boxRect,  cv::Scalar(0,255,255), 2);
//
//    cv::rectangle(image, boxRect2,  cv::Scalar(0,255,255), 2);
//    cv::rectangle(image2, boxRect2,  cv::Scalar(0,255,255), 2);
//
//    cv::imshow("image", image);
//    cv::imshow("image2", image2);
//
//    cv::waitKey(0);
////    std::string file = "/data/log/image/evt3_2_20211130/20211130_3_2_1_7_75_0/config.yaml";
////    cv::FileStorage fileStream = cv::FileStorage(file, cv::FileStorage::READ);
////
////    if (not fileStream.isOpened())
////    {
////        return false;
////    }
////    try{
////        cv::Mat_<double> K_l, P_l, R_l, D_l, K_r, P_r, R_r, D_r;
////        fileStream["Kl"] >> K_l;
////        fileStream["Dl"] >> D_l;
////        fileStream["Pl"] >> P_l;
////        fileStream["Rl"] >> R_l;
////        fileStream["Kr"] >> K_r;
////        fileStream["Dr"] >> D_r;
////        fileStream["Pr"] >> P_r;
////        fileStream["Rrl"] >> P_r;
////        std::cout<<K_l<<std::endl;
////        std::cout<<P_r<<std::endl;
////
////        std::cout<<cv::countNonZero(K_l)<<std::endl;
////    }
////    catch (...)
////    {
////        std::cout<<"try ...."<<std::endl;
////    }
//
//
//
//
//
////    double FONTscale = 1.0;
////    std::string str;
////    cv::Mat src = cv::Mat::zeros(480, 640, CV_8UC3);
////
////    TestColor(src);
////    return 0;
////    // b = a.clone();    深拷贝
////    cv::Mat check_clone;
////    check_clone = src.clone();
////
////    str = "clone";
////    cv::putText(check_clone, str, cv::Point(200, 100), cv::FONT_ITALIC, FONTscale, cv::Scalar(255, 0, 0), 2);
////    cv::imshow("check_clone", check_clone);
////
////    // a.copyTo(b);    深拷贝
////    cv::Mat check_copyTo;
////    src.copyTo(check_copyTo);
////
////    str = "copyTo";
////    cv::putText(check_copyTo, str, cv::Point(200, 150), cv::FONT_ITALIC, FONTscale, cv::Scalar(255, 0, 0), 2);
////    cv::imshow("check_copyTo", check_copyTo);
////
////    // b = a;    浅拷贝
////    cv::Mat check_equal;
////    check_equal = src;
////
////    str = "equal";
////    cv::putText(check_equal, str, cv::Point(200, 200), cv::FONT_ITALIC, FONTscale, cv::Scalar(255, 0, 0), 2);
////    cv::imshow("check_equal", check_equal);
////
////    // b(a);    浅拷贝
////    cv::Mat check_brackets(src);
////
////    str = "brackets";
////    cv::putText(check_brackets, str, cv::Point(200, 250), cv::FONT_ITALIC, FONTscale, cv::Scalar(255, 0, 0), 2);
////    cv::imshow("check_brackets", check_brackets);
////
////    // b(a); c = b;    2次浅拷贝 一样是浅拷贝
////    cv::Mat check_b(src);
////    cv::Mat check_q;
////    check_q = check_b;
////
////    str = "2222";
////    cv::putText(check_q, str, cv::Point(200, 300), cv::FONT_ITALIC, FONTscale, cv::Scalar(255, 0, 0), 2);
////    cv::imshow("check_q", check_q);
////
////    cv::imshow("src", src);
////
////    std::vector<cv::Mat> imageLists;
////    imageLists.push_back(src);
////    printf("src add: %p\n",src.data);
////    src.release();
////    printf("src add after release(): %p\n",src.data);
////
////    cv::Mat newMap = imageLists[0];
////    printf("imageLists[0] add : %p\n",imageLists[0].data);
////
////    imageLists[0] = cv::Mat();
////    printf("imageLists[0] add after equal(): %p\n",imageLists[0].data);
////
////
////    cv::imshow("newMap", newMap);
////    std::cout<<src<<"  "<<imageLists[0]<<std::endl;
////    printf("newMap add : %p\n",newMap.data);
////    cv::Mat newMap1 = newMap;
////    newMap = newMap.clone();
////    printf("newMap add after clone() : %p\n",newMap.data);
////    printf("newMap1 add after clone() : %p\n",newMap1.data);
////
////    cv::waitKey();
//
//
//
//
//
//
//
//
//
//
//
//
//
//
////    // check ROI    浅拷贝
////    cv::Mat img = cv::imread("timg.jpg");
////
////    cv::Mat img_roi;
////    img_roi = img(cv::Rect(400, 200, 100, 100));
////
////    str = "girl";
////    cv::putText(img_roi, str, cv::Point(50, 50), cv::FONT_ITALIC, FONTscale, cv::Scalar(255, 0, 0), 2);
////    cv::imshow("img", img);
////    cv::imshow("img_roi", img_roi);
////    cv::waitKey();
////
//
//    return 0;
//}
//
//
//
//
////int main()
////{
////    int abc = 10;
////    cv::Mat image1 = cv::imread("/home/indemind/Code/PycharmProjects/darknet/darknet_ab/chart1030.png");
////    if (image1.empty())
////    {
////        std::cout<<"image.empty()";
////    }
////    else
////    {
////        std::cout<<"image.empty() is false";
////    }
////
////    cv::Mat image2 = image1.clone();
////    std::vector<cv::Mat> va;
////    va.push_back(image1.clone());
////
////    cv::Mat image_equal = image1;
////    cv::merge(va,image1);
////
////
////
////    cv::imshow("1",image1);
//////    cv::imshow("2",image2);
//////    cv::imshow("equal",image_equal);
//////
//////
//////
//////
////    cv::waitKey(0);
////
////    return  0;
////}
//
////
////int main(int argc, char *argv[])
////{
////
////    cv::VideoCapture capture1,capture;
////    capture.open(0);  //打开摄像头，只要一个摄像头，默认是0; 笔记本上有自带的摄像头,再插入usb摄像头应该是1
////    capture1.open(1);  //打开摄像头，只要一个摄像头，默认是0; 笔记本上有自带的摄像头,再插入usb摄像头应该是1
////
////    if(capture.isOpened())  //打开摄像头
////    {
////        std::cout<<"video is open";
////
////    }
////
////
////
////    cv::Mat frame,frame1; //定义一个矩阵接受帧
//////    cv::namedWindow("camera",1);  //定义显示帧
////    int i=0;
////    for(;;)
////    {
////        std::cout<<"show image"<<std::endl;
////
////        capture>>frame; //取出一帧
////        capture>>frame1;
////        if (!frame.empty())
////        {
////            cv::imshow("camera", frame);   //在窗口显示
////            i++;
////            std::cout<<i<<"\n";
////        }
////        else
////        {
////
////        }
////        if (!frame1.empty())
////        {
////            cv::imshow("camera1", frame1);   //在窗口显示
////            i++;
////            std::cout<<i<<"\n";
////        }
////        else
////        {
////
////        }
////        cv::waitKey(1);
////
////    }
////
////    return 0;
////}