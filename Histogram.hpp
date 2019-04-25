#pragma once
#include<string>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include "opencv2/opencv.hpp"
class Histogram {
private:
	double h[256];
	double h2[256];
	int t[256];
	double c[256];
	int inverse_g(double s, Histogram histogram);
public:
	cv::Mat dimg;
	cv::Mat img;
	void generate_histogram(cv::Mat img);
	void equalization_histogram(cv::Mat img);
	void specifications_histogram(cv::Mat img,Histogram histogram);
	void sethistogram(int s[]);
	void sethistogram(double s[]);
	Histogram(cv::Mat img);
	Histogram(int s[]);
	cv::Mat drawhistogram();
};