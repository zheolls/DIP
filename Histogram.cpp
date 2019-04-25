#include "Histogram.hpp"

void Histogram::generate_histogram(cv::Mat img)
{
	for (int i = 0; i < img.cols; i++)
		for (int j = 0; j < img.rows; j++) {
			h[int(img.at<uchar>(j, i))]++;
		}

	for (int i = 0; i < 256; i++) {
		h[i] = double(h[i]) / (img.rows * img.cols);
		if (i == 0)
			c[i] = h[i];
		else
			c[i] = c[i - 1] + h[i];
	}
	int a = img.rows;
	int b = img.cols;
}

void Histogram::equalization_histogram(cv::Mat img)
{
	generate_histogram(img);
	dimg = cv::Mat(img.rows, img.cols, img.type());
	for (int i = 0; i < 256; i++) {
		h2[i] = 0;
	}
	for (int i = 0; i < 256; i++) {
		t[i] = int(255.0*c[i]+0.5);
		h2[t[i]] += h[i];
	}
	for (int i = 0; i < img.cols; i++)
		for (int j = 0; j < img.rows; j++) {
			dimg.at<uchar>(j, i) = uchar(t[int(img.at<uchar>(j, i))]);
		}
}

void Histogram::specifications_histogram(cv::Mat img, Histogram histogram)
{
	generate_histogram(img);
	dimg = cv::Mat(img.rows, img.cols, img.type());
	for (int i = 0; i < 256; i++) {
		h2[i] = 0;
	}
	for (int i = 0; i < 256; i++) {
		t[i] = inverse_g(c[i],histogram);
		h2[t[i]] += h[i];
	}
	for (int i = 0; i < img.cols; i++)
		for (int j = 0; j < img.rows; j++) {
			dimg.at<uchar>(j, i) = uchar(t[img.at<uchar>(j, i)]);
		}
}

void Histogram::sethistogram(int s[])
{
	int sum = 0;
	for (int i = 0; i < 256; i++) {
		sum += s[i];
	}
	for (int i = 0; i < 256; i++) {
		h[i] = double(s[i]) / sum;
	}
	c[0] = h[0];
	for (int i = 0; i < 256; i++) {
		c[i] = c[i - 1] + h[i];
	}
	
}

void Histogram::sethistogram(double s[])
{
	for (int i = 0; i < 256; i++) {
		h[i] = s[i];
	}
	c[0] = h[0];
	for (int i = 0; i < 256; i++) {
		c[i] = c[i - 1] + h[i];
	}
}

Histogram::Histogram(cv::Mat img)
{
	generate_histogram(img);
}

Histogram::Histogram(int s[])
{
	sethistogram(s);
}

cv::Mat Histogram::drawhistogram()
{
	using namespace cv;
	int hist_w = 500; 
	int hist_h = 500;
	int histSize = 255;
	int bin_w = cvRound((double)hist_w / histSize);
	Mat histImage(hist_w, hist_h, CV_8UC3, Scalar(255,255,255));
	int his[255];
	double max = 0;
	for (int i = 0; i < 255; i++) {
		if (max < h2[i]) max = h2[i];
	}
	for (int i = 0; i < 255; i++) {
		his[i] = hist_h * h2[i]/max;
	}
	for (int i = 0; i < histSize; i++)
	{
		line(histImage, Point(bin_w * (i), hist_h),	Point(bin_w * (i), hist_h - his[i - 1]),
			Scalar(0, 0, 255), 2, 8, 0);
		line(histImage, Point(0, 0), Point(0, hist_h ),
			Scalar(0, 0, 0), 1, 8, 0);
		line(histImage, Point(0, hist_h), Point(hist_w, hist_h),
			Scalar(0, 0, 0), 2, 8, 0);
	}
	return histImage;
}

int Histogram::inverse_g(double s, Histogram histogram)
{
	for (int i = 0; i < 256; i++) {
		if (histogram.c[i] <= s && histogram.c[i + 1] >= s) {
			if (s - histogram.c[i] > histogram.h[i + 1] / 2)
				return i + 1;
			else
				return i;
		}
	}
	return -1;
}
