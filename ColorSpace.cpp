#include "ColorSpace.hpp"

ColorSpace::Grayscale::Grayscale(Scalar i)
{
	Intensity=i;
}

ColorSpace::Grayscale::Grayscale(RGB c)
{
	Intensity = (c.Red + c.Green + c.Blue) / 3;
}

ColorSpace::Grayscale::Grayscale(HSI c)
{
	Intensity = c.Intensity;
}

ColorSpace::Grayscale::Grayscale(YUV c)
{
	Intensity = c.Y;
}

ColorSpace::HSI::HSI(Scalar h, Scalar s, Scalar i)
{
	Hue = h;
	Saturation = s;
	Intensity = i;
}

ColorSpace::HSI::HSI(Grayscale c)
{
	Hue = 0;
	Saturation = 0;
	Intensity = c.Intensity;

}

ColorSpace::HSI::HSI(RGB c)
{
	Scalar h, s, i;
	Scalar r, g, b;

	r = c.Red;
	g = c.Green;
	b = c.Blue;

	Scalar theta = acos(
		((r - g) + (r - b)) /
		sqrt((r - g) * (r - g) +
		(r - b) * (g - b)) / 2);
	if (isnan(theta)) theta = 0.0;
	if (b <= g) {
		h = theta;
	}
	else {
		h = M_PI * 2 - theta;
	};

	Scalar min = r < g ? r : g;
	if (min > b) min = b;
	s = 1 - 3 * min / (r + g + b);
	if (isnan(s)) s = 0;

	i = (r + g + b) / 3;

	Hue = h;
	Saturation = s;
	Intensity = i;
}

ColorSpace::RGB::RGB(Scalar r, Scalar g, Scalar b)
{
	Red = r; Green = g; Blue = b;
}

ColorSpace::RGB::RGB(int r, int g, int b) {
	Red = r / 255.0; 
	Green = g / 255.0;
	Blue = b / 255.0;
}

ColorSpace::RGB::RGB(Grayscale c)
{
	Red = c.Intensity;
	Blue = c.Intensity;
	Green = c.Intensity;
}

ColorSpace::RGB::RGB(HSI c)
{
	Scalar r, g, b;
	Scalar h, s, i;

	h = c.Hue;
	s = c.Saturation;
	i = c.Intensity;

	if (0.0 <= h && h < M_PI * 2 / 3) {
		b = i * (1 - s);
		r = i * (1 + s * cos(h) / cos(M_PI / 3 - h));
		g = 3 * i - (r + b);
	}
	else if (M_PI * 2 / 3 <= h && h < M_PI * 4 / 3) {
		Scalar H = h - M_PI * 2 / 3;
		r = i * (1 - s);
		g = i * (1 + s * cos(H) / cos(M_PI / 3 - H));
		b = 3 * i - (r + g);
	}
	else {
		Scalar H = h - M_PI * 4 / 3;
		g = i * (1 - s);
		b = i * (1 + s * cos(H) / cos(M_PI / 3 - H));
		r = 3 * i - (g + b);
	};

	Red = r;
	Green = g;
	Blue = b;
}

ColorSpace::YUV::YUV(Scalar y, Scalar u, Scalar v)
{
	Y = y;
	U = u;
	V = v;
}

ColorSpace::YUV::YUV(RGB c)
{

}

int ColorSpace::YUV::intY()
{
	return int(Y * (235 - 16) + 16);
}

int ColorSpace::YUV::intU() {
	return int((U + 0.5) * (240 - 16) + 16);
}

int ColorSpace::YUV::intV() {
	return int((V + 0.5) * (240 - 16) + 16);
}
