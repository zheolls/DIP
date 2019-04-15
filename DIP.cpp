#include <iostream>
#include <DIP/DIP.hpp>
#pragma comment(lib, "opencv_world410d.lib")
//该头文件模式下，兼容C和C++
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include "opencv2/opencv.hpp"


void RGBtoYUV(cv::Mat simg, cv::Mat &oimgy, cv::Mat &oimgu, cv::Mat &oimgv) {
	using namespace DIP::ColorSpace;

	for (int i = 0; i < simg.rows; i++) {
		for (int j = 0; j < simg.cols; j++) {
			cv::Vec3b temp = simg.at<cv::Vec3b>(j, i);
			cv::Vec3b temp2;
			YUV y = RGB(temp[0],temp[1],temp[2]);
			temp2 = cv::Vec3b(y.intY(), y.intU(), y.intV());
			oimgy.at<cv::Vec3b>(j, i) = cv::Vec3b(temp2[0], temp2[0], temp2[0]);
			oimgu.at<cv::Vec3b>(j, i) = cv::Vec3b(temp2[1], temp2[1], temp2[1]);
			oimgv.at<cv::Vec3b>(j, i) = cv::Vec3b(temp2[2], temp2[2], temp2[2]);

		}
	}
}
int main()
{
	cv::Mat src,drcy,drcu,drcv,drc;
	src = cv::imread("girl.bmp",CV_16FC3);
	if (!src.data) {
		std::cout << "dsadd" << std::endl;
	}
	drcy = cv::Mat(src.rows, src.cols, src.type());
	drcu = cv::Mat(src.rows, src.cols, src.type());
	drcv = cv::Mat(src.rows, src.cols, src.type());
	std::cout << src.channels() << std::endl;
	RGBtoYUV(src, drcy, drcu, drcv);
	cv::imwrite("image/Color/girly.bmp",drcy);
	cv::imwrite("image/Color/girlu.bmp", drcu);
	cv::imwrite("image/Color/girlv.bmp", drcv);

}

