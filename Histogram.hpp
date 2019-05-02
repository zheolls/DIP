#include "Config.hpp"
class Histogram {
private:
	double h[256];
	int inth[256];
	double h2[256];
	int t[256];
	
	int inverse_g(double s, Histogram histogram);
public:
	cv::Mat dimg;
	cv::Mat img;
	double c[256];
	void generate_histogram(cv::Mat img);
	void equalization_histogram(cv::Mat img);
	void specifications_histogram(cv::Mat img,Histogram histogram);
	void sethistogram(int s[]);
	void sethistogram(double s[]);
	void addpixel(uchar p);
	void subpixel(uchar p);
	Histogram(cv::Mat img);
	Histogram(int s[]);
	Histogram();
	cv::Mat drawhistogram();
};