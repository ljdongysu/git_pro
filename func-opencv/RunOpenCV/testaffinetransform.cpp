//
// Created by indemind on 11/27/21.
//
//用于验证仿射变换，旋转缩放图像，其中也包含了图像上的点通过两条线段进行映射的操作
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/opencv.hpp>

#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

/// 全局变量
char* source_window = "Source image";
char* warp_window = "Warp";
char* warp_rotate_window = "Warp + Rotate";

cv::Scalar colorBack(100, 100, 100);
cv::Scalar colorAxis(0, 0, 200);
cv::Scalar colorObject(50, 250, 50);
/** @function main */
int main( int argc, char** argv )
{
    Point2f srcTri[3];
    Point2f dstTri[3];

    Mat rot_mat( 2, 3, CV_32FC1 );
    Mat warp_mat( 2, 3, CV_32FC1 );
    Mat src, warp_dst, warp_rotate_dst;

    /// 加载源图像
    src = imread( argv[1], 1 );

    /// 设置目标图像的大小和类型与源图像一致
    warp_dst = Mat::zeros( src.rows, src.cols, src.type() );

    /// 设置源图像和目标图像上的三组点以计算仿射变换
    srcTri[0] = Point2f( 0,0 );
    srcTri[1] = Point2f( 100, 0);
    srcTri[2] = Point2f( 0, 100);

    dstTri[0] = Point2f( 500,500 );
    dstTri[1] = Point2f( 500, 600);
    dstTri[2] = Point2f( 400, 500 );

    /// 求得仿射变换
    warp_mat = getAffineTransform( srcTri, dstTri );
    const double x0 = 100;
    const double y0 = 100;

    cv::Mat point = cv::Mat(3,1,CV_64FC1);
    double *data = point.ptr<double>(0);
    data[0] = x0;
    data = point.ptr<double>(1);
    data[0] = y0;
    data = point.ptr<double>(2);
    data[0] = 1.0;

    std::cout<<point.type()<<std::endl;
    std::cout<<warp_mat.type()<<std::endl;
    std::cout<<point<<std::endl;
    std::cout<<warp_mat<<std::endl;
    point = warp_mat * point;
    std::cout<<point<<std::endl;

    std::cout<<warp_mat.size<<std::endl;
    /// 对源图像应用上面求得的仿射变换
    warpAffine( src, warp_dst, warp_mat, warp_dst.size() );

    /** 对图像扭曲后再旋转 */

    /// 计算绕图像中点顺时针旋转50度缩放因子为0.6的旋转矩阵
    Point center = Point( warp_dst.cols/2, warp_dst.rows/2 );
    double angle = -50.0;
    double scale = 0.6;

    /// 通过上面的旋转细节信息求得旋转矩阵
    rot_mat = getRotationMatrix2D( center, angle, scale );

    /// 旋转已扭曲图像
    warpAffine( warp_dst, warp_rotate_dst, rot_mat, warp_dst.size() );

    /// 显示结果
    cv::circle(src, cv::Point(int(100), int(100)), 1
            , colorObject, 4);
    namedWindow( source_window, CV_WINDOW_AUTOSIZE );
    imshow( source_window, src );

    data = point.ptr<double>(0);
    float x1 = data[0];
    data = point.ptr<double>(1);
    float y1 = data[0];
    cv::circle(warp_dst, cv::Point(int(x1), int(y1)), 1
            , colorObject, 4);
    namedWindow( warp_window, CV_WINDOW_AUTOSIZE );
    imshow( warp_window, warp_dst );

    namedWindow( warp_rotate_window, CV_WINDOW_AUTOSIZE );
    imshow( warp_rotate_window, warp_rotate_dst );

    /// 等待用户按任意按键退出程序
    waitKey(0);

    return 0;
}