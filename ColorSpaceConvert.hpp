#include "Config.hpp"
#include "ColorSpace.hpp"
class Convert {
private:
	cv::Mat img;
public:
	Convert(cv::Mat s);
	cv::Mat getRimg();
	cv::Mat getGimg();
	cv::Mat getBimg();
	cv::Mat getYimg();
	cv::Mat getUimg();
	cv::Mat getVimg();
	cv::Mat getGreyimg();
	cv::Mat getHimg();
	cv::Mat getSimg(); 
	cv::Mat getIimg();
};