#include <iostream>
#pragma comment(lib, "opencv_world410d.lib")
//该头文件模式下，兼容C和C++
#include "ColorSpace.hpp"
#include "Histogram.hpp"
void RGBtoYUV(cv::Mat simg, cv::Mat &oimgy, cv::Mat &oimgu, cv::Mat &oimgv) {
	using namespace ColorSpace;

	for (int i = 0; i < simg.rows; i++) {
		for (int j = 0; j < simg.cols; j++) {
			cv::Vec3b temp = simg.at<cv::Vec3b>(j, i);
			cv::Vec3b temp2;
			YUV y = YUV(RGB(temp[0],temp[1],temp[2]));
			temp2 = cv::Vec3b(y.intY(), y.intU(), y.intV());
			oimgy.at<cv::Vec3b>(j, i) = cv::Vec3b(temp2[0], temp2[0], temp2[0]);
			oimgu.at<cv::Vec3b>(j, i) = cv::Vec3b(temp2[1], temp2[1], temp2[1]);
			oimgv.at<cv::Vec3b>(j, i) = cv::Vec3b(temp2[2], temp2[2], temp2[2]);

		}
	}
}
void RGBtoHSI(cv::Mat simg, cv::Mat& oimgh, cv::Mat& oimgs, cv::Mat& oimgi) {
	using namespace ColorSpace;

	for (int i = 0; i < simg.rows; i++) {
		for (int j = 0; j < simg.cols; j++) {
			cv::Vec3b temp = simg.at<cv::Vec3b>(j, i);
			cv::Vec3b temp2;
			HSI y = HSI(RGB(temp[0], temp[1], temp[2]));
			temp2 = cv::Vec3b(y.First()*255, y.Second()*255, y.Third()*255);
			oimgh.at<cv::Vec3b>(j, i) = cv::Vec3b(temp2[0], temp2[0], temp2[0]);
			oimgs.at<cv::Vec3b>(j, i) = cv::Vec3b(temp2[1], temp2[1], temp2[1]);
			oimgi.at<cv::Vec3b>(j, i) = cv::Vec3b(temp2[2], temp2[2], temp2[2]);

		}
	}
}



int main()
{
	cv::Mat src,drcy,drcu,drcv,drc,dimg;
	src = cv::imread("dark.bmp",0 );
	if (!src.dims) {

	}
	int b[256];
	for (int i = 0; i < 256; i++) {
		b[i] = int(pow(i, 0.5)*255);
	}
	Histogram histogram = Histogram(src);
	Histogram his(b);
	histogram.equalization_histogram(src);
	cv::imwrite("image/Color/dark.bmp", histogram.dimg);
	cv::imwrite("image/Color/his.bmp", histogram.drawhistogram());
	histogram.specifications_histogram(src,his);
	cv::imwrite("image/Color/darkspec.bmp", histogram.dimg);

	cv::imwrite("image/Color/spec.bmp", histogram.drawhistogram());
	//drcy = cv::Mat(src.rows, src.cols, src.type());
	//drcu = cv::Mat(src.rows, src.cols, src.type());
	//drcv = cv::Mat(src.rows, src.cols, src.type());
	//std::cout << src.channels() << std::endl;
	//RGBtoYUV(src, drcy, drcu, drcv);
	//cv::imwrite("image/Color/girly.bmp",drcy);
	//cv::imwrite("image/Color/girlu.bmp", drcu);
	//cv::imwrite("image/Color/girlv.bmp", drcv);

}

