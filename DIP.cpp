#include "Histogram.hpp"
#include "Filter.hpp"
#include "ColorSpaceConvert.hpp"


int main()
{
	cv::Mat src = cv::imread("image/girl.bmp");

	Convert convert(src);
	cv::imwrite("image/girlgrey.bmp", convert.getGreyimg());
	cv::imwrite("image/girly.bmp", convert.getYimg());
	cv::imwrite("image/girlu.bmp", convert.getUimg());
	cv::imwrite("image/girlv.bmp", convert.getVimg());
	cv::imwrite("image/girlh.bmp", convert.getHimg());
	cv::imwrite("image/girls.bmp", convert.getSimg());
	cv::imwrite("image/girli.bmp", convert.getIimg());

	src = cv::imread("image/dark.bmp", 0);
	Histogram his=Histogram(src);
	his.equalization_histogram(src);
	cv::imwrite("image/dark_equalization.bmp",his.dimg);
	cv::imwrite("image/dark_equalization_his.bmp", his.drawhistogram());
	int b[256];
	for (int i = 0; i < 256; i++) {
		b[i] = 255-i;
	}

	his.specifications_histogram(src,Histogram(b));
	cv::imwrite("image/dark_specifications.bmp", his.dimg);
	cv::imwrite("image/dark_specifications_his.bmp", his.drawhistogram());


	src = cv::imread("image/lenna512noise.bmp",0);
	Filter filter(src);
	
	cv::imwrite("image/lenna512_median_filtering.bmp", filter.median_filtering(1));
	filter.set_max_noise(2);
	cv::imwrite("image/lenna512_median_filtering_2.bmp", filter.median_filtering(1));

	src = cv::imread("image/lenna512.bmp", 0);
	filter=Filter(src);

	cv::imwrite("image/lenna512_average_filtering.bmp", filter.average_filtering(1));
	cv::imwrite("image/lenna512_sharpening_filtering_laplace.bmp", filter.sharpening_filtering(Filter::LAPLACE,4));
	cv::imwrite("image/lenna512_sharpening_filtering_laplac_SharpDeltaImage.bmp", filter.getSharpDeltaImage());
	cv::imwrite("image/lenna512_sharpening_filtering_laplac_BitImage.bmp", filter.getBitImage());


}

