#include "Config.hpp"
class Filter {
private:
	cv::Mat img,bitimg,sharpimg;
	int edge(int a, int b);
	bool check_noise_enable;
	int noisesize;
	double sharpenamount;
	void kernal_his(cv::Mat s, int i, int j, int r, int* h);
	bool check_noise(int* h, int  r);
	uchar median_his(int* his, int r);
	uchar sharp(uchar pixel,int d);
	uchar overflow(int d);
	double sinp;
public:
	Filter(cv::Mat s);
	enum SHARPTYPE
	{
		SOBEL,
		PREWITT,
		ROBERTS,
		LAPLACE
	};
	Filter();
	cv::Mat median_filtering(int kernalsize);
	cv::Mat average_filtering(int kernalsize);
	cv::Mat sharpening_filtering(SHARPTYPE s,double amount);
	cv::Mat sharpening_filtering(SHARPTYPE s);
	cv::Mat getBitImage();
	cv::Mat getSharpDeltaImage();
	void set_max_noise(int n);
};