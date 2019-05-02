#include<string>
#define M_PI 3.14159
namespace ColorSpace
{
	typedef double Scalar;
	struct Grayscale;
	struct RGB;
	struct HSI;
	struct YUV;
	struct Grayscale  {
		Scalar Intensity;
		Grayscale(Scalar i);
		Grayscale(RGB c);
		Grayscale(HSI c);
		Grayscale(YUV c);
		std::string Name() {
			return "Grayscale";
		};
		Scalar First() {
			return Intensity;
		};
		int intGrey();
	};
	struct RGB  {
		Scalar Red;	// 0 .. 1
		Scalar Green;	// 0 .. 1
		Scalar Blue;	// 0 .. 1
		RGB(Scalar r, Scalar g, Scalar b);
		RGB(int r, int g, int b);
		RGB(Grayscale c);
		RGB(HSI c);
		std::string Name() {
			return "RGB";
		};
		Scalar First() {
			return Red;
		};
		Scalar Second() {
			return Green;
		};
		Scalar Third() {
			return Blue;
		};
	};
	struct HSI  {
		Scalar Hue;	// 0 .. 2 * Pi
		Scalar Saturation;	// 0 .. 1
		Scalar Intensity;	// 0 .. 1
		HSI(Scalar h, Scalar s, Scalar i);
		HSI(Grayscale c);
		HSI(RGB c);
		std::string Name() {
			return "HSI";
		};
		Scalar First() {
			return Hue;
		};
		Scalar Second() {
			return Saturation;
		};
		Scalar Third() {
			return Intensity;
		};
		int intH();
		int intS();
		int intI();
	};
	struct YUV  {
		Scalar Y; //0...1
		Scalar U;  //-0.5~0.5
		Scalar V;  //-0.5~0.5
		YUV(Scalar y, Scalar u, Scalar v);
		YUV(RGB c);
		std::string Name() {
			return "YUV";
		};
		Scalar First() {
			return Y;
		};
		Scalar Second() {
			return U;
		};
		Scalar Third() {
			return V;
		};
		int intY();

		int intU();

		int intV();
	};
};


