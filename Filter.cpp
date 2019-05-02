#include "Filter.hpp"

Filter::Filter(cv::Mat s)
{
	img = s;
	check_noise_enable = false;
	sinp = 1 / (s.rows * s.cols);
	sharpenamount = 4;
	bitimg = cv::Mat(img.rows, img.cols, img.type());
	sharpimg = cv::Mat(img.rows, img.cols, img.type());
}

Filter::Filter()
{
}

cv::Mat Filter::median_filtering(int kernalsize)
{
	int his[256];
	cv::Mat dimg = cv::Mat(img.rows, img.cols, img.type());
	for (int i = 0; i < img.rows; i++) {
		kernal_his(img, i, 0, kernalsize,his);
		dimg.at<uchar>(i, 0) = median_his(his, kernalsize);
		for (int j = 1; j < img.cols; j++) {
			for (int k = -kernalsize; k <= kernalsize; k++)
			{
				his[img.at<uchar>(edge(i + k, img.rows), edge(j - kernalsize - 1, img.cols))]--;
				his[img.at<uchar>(edge(i + k, img.rows), edge(j + kernalsize, img.cols))]++;
			}

			if (check_noise(his, kernalsize)&&check_noise_enable) {
				kernal_his(img, i, j, kernalsize + noisesize, his);
				dimg.at<uchar>(i, j) = median_his(his, kernalsize + noisesize);
				kernal_his(img, i, j, kernalsize, his);
			}
			else
			{
				dimg.at<uchar>(i, j) = median_his(his, kernalsize);
			}
		}
	}
;	return dimg;
}

cv::Mat Filter::average_filtering(int kernalsize)
{
	cv::Mat dimg = cv::Mat(img.rows, img.cols, img.type());
	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {
			int sum = 0;
			for (int ii = i - kernalsize; ii <= i + kernalsize; ii++)
				for (int jj = j - kernalsize; jj <= j + kernalsize; jj++) {
					uchar a = img.at<uchar>(edge(ii, img.rows), edge(jj, img.cols));
					sum += a;
				}
			dimg.at<uchar>(i, j) = sum / ((kernalsize * 2 + 1) * (kernalsize * 2 + 1));
		}
	}
	return dimg;
}

cv::Mat Filter::sharpening_filtering(SHARPTYPE s, double amount)
{
	sharpenamount = amount;
	return sharpening_filtering(s);
}

cv::Mat Filter::sharpening_filtering(SHARPTYPE s)
{
	cv::Mat dimg = cv::Mat(img.rows, img.cols, img.type());
	switch (s)
	{
	case Filter::SOBEL: {
		for (int i = 0; i < img.rows; i++) {
			for (int j = 0; j < img.cols; j++) {
				int delta =
					abs(img.at<uchar>(edge(i + 1, img.rows), edge(j - 1, img.cols)) +
						img.at<uchar>(edge(i + 1, img.rows), edge(j, img.cols)) * 2 +
						img.at<uchar>(edge(i + 1, img.rows), edge(j + 1, img.cols)) -
						img.at<uchar>(edge(i - 1, img.rows), edge(j - 1, img.cols)) -
						img.at<uchar>(edge(i - 1, img.rows), edge(j, img.cols)) * 2 -
						img.at<uchar>(edge(i - 1, img.rows), edge(j + 1, img.cols)))
					+
					abs(img.at<uchar>(edge(i - 1, img.rows), edge(j + 1, img.cols)) +
						img.at<uchar>(edge(i, img.rows), edge(j + 1, img.cols)) * 2 +
						img.at<uchar>(edge(i + 1, img.rows), edge(j + 1, img.cols)) -
						img.at<uchar>(edge(i - 1, img.rows), edge(j - 1, img.cols)) -
						img.at<uchar>(edge(i, img.rows), edge(j - 1, img.cols)) * 2 -
						img.at<uchar>(edge(i + 1, img.rows), edge(j - 1, img.cols)));
				dimg.at<uchar>(i, j) = sharp(img.at<uchar>(i, j), int(delta));
				sharpimg.at<uchar>(i, j) = overflow((int)delta);
			}
		}
		break;
	}

	case Filter::PREWITT: {
		for (int i = 0; i < img.rows; i++) {
			for (int j = 0; j < img.cols; j++) {
				int delta =
					abs(img.at<uchar>(edge(i + 1, img.rows), edge(j - 1, img.cols)) +
						img.at<uchar>(edge(i + 1, img.rows), edge(j, img.cols)) +
						img.at<uchar>(edge(i + 1, img.rows), edge(j + 1, img.cols)) -
						img.at<uchar>(edge(i - 1, img.rows), edge(j - 1, img.cols)) -
						img.at<uchar>(edge(i - 1, img.rows), edge(j, img.cols)) -
						img.at<uchar>(edge(i - 1, img.rows), edge(j + 1, img.cols)))
					+
					abs(img.at<uchar>(edge(i - 1, img.rows), edge(j + 1, img.cols)) +
						img.at<uchar>(edge(i, img.rows), edge(j + 1, img.cols)) +
						img.at<uchar>(edge(i + 1, img.rows), edge(j + 1, img.cols)) -
						img.at<uchar>(edge(i - 1, img.rows), edge(j - 1, img.cols)) -
						img.at<uchar>(edge(i, img.rows), edge(j - 1, img.cols)) -
						img.at<uchar>(edge(i + 1, img.rows), edge(j - 1, img.cols)));
				dimg.at<uchar>(i, j) = sharp(img.at<uchar>(i, j), int(delta));
				sharpimg.at<uchar>(i, j) = overflow((int)delta);
			}
		}
		break;
	}

	case Filter::ROBERTS: {
		for (int i = 0; i < img.rows; i++) {
			for (int j = 0; j < img.cols; j++) {
				int delta = abs(img.at<uchar>(edge(i + 1, img.rows), edge(j + 1, img.cols)) - img.at<uchar>(edge(i, img.rows), edge(j, img.cols)))
					+
					abs(img.at<uchar>(edge(i + 1, img.rows), edge(j, img.cols)) - img.at<uchar>(edge(i, img.rows), edge(j + 1, img.cols)));
				dimg.at<uchar>(i, j) = sharp(img.at<uchar>(i, j), int(delta));
				sharpimg.at<uchar>(i, j) = overflow((int)delta);
			}
		}
		break;
	}

	case Filter::LAPLACE: {
		double b[9];
		for (int i = 0; i < 9; i++) {
			b[i] = sharpenamount / 8;
		}
		b[5] = -sharpenamount;
		for (int i = 0; i < img.rows; i++) {
			for (int j = 0; j < img.cols; j++) {
				double delta = 0;
				int flag = 0;
				for (int ii = i - 1; ii <= i + 1; ii++)
					for (int jj = j - 1; jj <= j + 1; jj++) {
						uchar a = img.at<uchar>(edge(ii, img.rows), edge(jj, img.cols));
						delta += b[flag] * a;
						flag++;
					}
				dimg.at<uchar>(i, j) = sharp(img.at<uchar>(i, j), int(delta));
				sharpimg.at<uchar>(i, j) = overflow((int)delta);
			}
		}
		break;
	}

	default:
		break;
	}

	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {
			if (sharpimg.at<uchar>(i, j)>=128)
				bitimg.at<uchar>(i, j) = 255;
			else
			{
				bitimg.at<uchar>(i, j) = 0;
			}
		}
	}

	return dimg;
}

cv::Mat Filter::getBitImage()
{
	return bitimg;
}

cv::Mat Filter::getSharpDeltaImage()
{
	return sharpimg;
}

int Filter::edge(int a, int b)
{
	if (a < 0) {
		return -a - 1;
	}
	else if (a >= b) {
		return b - (a - b + 1);
	}
	else
		return a;
}

void Filter::kernal_his(cv::Mat s, int i, int j, int r,int *h)
{
	for (int ii = 0; ii < 256; ii++)
		h[ii] = 0;
	for (int ii=i-r;ii<=i+r;ii++)
		for (int jj = j - r; jj <= j + r; jj++) {
			uchar a = s.at<uchar>(edge(ii, s.rows), edge(jj, s.cols));
			h[a]++;
		}

}

bool Filter::check_noise(int* h,int r)
{
	int sum = 0;
	for (int i = 0; i < 16; i++) {
		sum += h[i];
	}
	if (sum>0.3*(r*2+1)*(r*2+1))
		return true;
	else
	{
		return false;
	}
}

uchar Filter::median_his(int* his,int r)
{
	int median = ((r+1) * (r+1)) / 2+1;
	int sum = 0;
	for (uchar i = 0; i < 256; i++) {
		sum += his[i];
		if (sum > median) {
			return i;
		}
	}
}

uchar Filter::sharp(uchar pixel, int d)
{
	int delta=overflow(d);
	uchar pixel2;
	if (pixel - delta < 0)
		return 0;
	else if (pixel - delta > 255)
	{
		return 255;
	}
	else
	{
		return pixel - delta;
	}
}

uchar Filter::overflow(int d)
{
	if (d > 255)
		return 255;
	else if (d < 0)
		return 0;
	else
		return d;
}

void Filter::set_max_noise(int n)
{
	noisesize = n;
	check_noise_enable = true;
}
