#include "ColorSpaceConvert.hpp"

Convert::Convert(cv::Mat s)
{
	img = s;
}

cv::Mat Convert::getRimg()
{
	cv::Mat rimg=cv::Mat(img.rows, img.cols, CV_8U);;
	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {
			rimg.at<uchar>(i, j) = img.at<cv::Vec3b>(i, j)[0];
		}
	}
	return rimg;

}

cv::Mat Convert::getGimg()
{
	cv::Mat gimg = cv::Mat(img.rows, img.cols, CV_8U);;
	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {
			gimg.at<uchar>(i, j) = img.at<cv::Vec3b>(i, j)[1];
		}
	}
	return gimg;
}

cv::Mat Convert::getBimg()
{
	cv::Mat bimg = cv::Mat(img.rows, img.cols, CV_8U);;
	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {
			bimg.at<uchar>(i, j) = img.at<cv::Vec3b>(i, j)[2];
		}
	}
	return bimg;
}

cv::Mat Convert::getYimg()
{
	cv::Mat yimg = cv::Mat(img.rows, img.cols, CV_8U);;
	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {
			ColorSpace::YUV yuv = ColorSpace::YUV(ColorSpace::RGB(img.at<cv::Vec3b>(i, j)[0], img.at<cv::Vec3b>(i, j)[1], img.at<cv::Vec3b>(i, j)[2]));
			yimg.at<uchar>(i, j) = yuv.intY();
		}
	}
	return yimg;
}

cv::Mat Convert::getUimg()
{
	cv::Mat uimg = cv::Mat(img.rows, img.cols, CV_8U);;
	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {
			ColorSpace::YUV yuv = ColorSpace::YUV(ColorSpace::RGB(img.at<cv::Vec3b>(i, j)[0], img.at<cv::Vec3b>(i, j)[1], img.at<cv::Vec3b>(i, j)[2]));
			uimg.at<uchar>(i, j) = yuv.intU();
		}
	}
	return uimg;
}

cv::Mat Convert::getVimg()
{
	cv::Mat vimg = cv::Mat(img.rows, img.cols, CV_8U);;
	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {
			ColorSpace::YUV yuv = ColorSpace::YUV(ColorSpace::RGB(img.at<cv::Vec3b>(i, j)[0], img.at<cv::Vec3b>(i, j)[1], img.at<cv::Vec3b>(i, j)[2]));
			vimg.at<uchar>(i, j) = yuv.intV();
		}
	}
	return vimg;
}

cv::Mat Convert::getGreyimg()
{
	cv::Mat greyimg = cv::Mat(img.rows, img.cols, CV_8U);;
	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {
			ColorSpace::Grayscale grey = ColorSpace::Grayscale(ColorSpace::RGB(img.at<cv::Vec3b>(i, j)[0], img.at<cv::Vec3b>(i, j)[1], img.at<cv::Vec3b>(i, j)[2]));
			greyimg.at<uchar>(i, j) = grey.intGrey();
		}
	}
	return greyimg;
}

cv::Mat Convert::getHimg()
{
	cv::Mat himg = cv::Mat(img.rows, img.cols, CV_8U);;
	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {
			ColorSpace::HSI hsi = ColorSpace::HSI(ColorSpace::RGB(img.at<cv::Vec3b>(i, j)[0], img.at<cv::Vec3b>(i, j)[1], img.at<cv::Vec3b>(i, j)[2]));
			himg.at<uchar>(i, j) = hsi.intH();
		}
	}
	return himg;
}

cv::Mat Convert::getSimg()
{
	cv::Mat simg = cv::Mat(img.rows, img.cols, CV_8U);;
	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {
			ColorSpace::HSI hsi = ColorSpace::HSI(ColorSpace::RGB(img.at<cv::Vec3b>(i, j)[0], img.at<cv::Vec3b>(i, j)[1], img.at<cv::Vec3b>(i, j)[2]));
			simg.at<uchar>(i, j) = hsi.intS();
		}
	}
	return simg;
}

cv::Mat Convert::getIimg()
{
	cv::Mat iimg = cv::Mat(img.rows, img.cols, CV_8U);;
	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {
			ColorSpace::HSI hsi = ColorSpace::HSI(ColorSpace::RGB(img.at<cv::Vec3b>(i, j)[0], img.at<cv::Vec3b>(i, j)[1], img.at<cv::Vec3b>(i, j)[2]));
			iimg.at<uchar>(i, j) = hsi.intI();
		}
	}
	return iimg;
}
