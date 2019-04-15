#ifndef _DIP_ColorSpace_hpp_
#define _DIP_ColorSpace_hpp_
#define M_PI 3.14159
#include <DIP/Config.hpp>
#include <cstdlib>
#include <cmath>
#include <string>
//#include <DIP/Exceptions.hpp>
#include <DIP/Types.hpp>

#include <DIP/internal/macros_begin.hpp>

namespace DIP {
	namespace ColorSpace {
		using namespace std;

		struct Base {
			// string Name();
			// void FromStr(string colorString);
			// string Str();
		};

		struct Unitary : Base {
			// F_GETTER Scalar First();
		};

		struct Tenary : Base {
			// F_GETTER Scalar First();
			// F_GETTER Scalar Second();
			// F_GETTER Scalar Third();
		};

		struct Grayscale;

		struct RGB;
		struct HSI;
		struct CIEXYZ;
		struct CIELab;
		struct YUV;

		struct Grayscale : Unitary {
			Scalar Intensity;
			F_SHORT Grayscale(Scalar i);
			F_SHORT Grayscale(RGB c);
			F_SHORT Grayscale(HSI c);
			F_SHORT Grayscale(YUV c);
			F_GETTER string Name() {
				return "Grayscale";
			};
			F_GETTER Scalar First() {
				return Intensity;
			};
		};

		struct RGB : Tenary {
			Scalar Red;	// 0 .. 1
			Scalar Green;	// 0 .. 1
			Scalar Blue;	// 0 .. 1
			F_SHORT RGB(Scalar r, Scalar g, Scalar b);
			F_SHORT RGB(int r, int g, int b);
			F_SHORT RGB(Grayscale c);
			F_SHORT RGB(HSI c);
			F_SHORT RGB(CIEXYZ c);
			F_SHORT RGB(CIELab c);
			F_GETTER string Name() {
				return "RGB";
			};
			F_GETTER Scalar First() {
				return Red;
			};
			F_GETTER Scalar Second() {
				return Green;
			};
			F_GETTER Scalar Third() {
				return Blue;
			};
		};
		struct HSI : Tenary {
			Scalar Hue;	// 0 .. 2 * Pi
			Scalar Saturation;	// 0 .. 1
			Scalar Intensity;	// 0 .. 1
			F_SHORT HSI(Scalar h, Scalar s, Scalar i);
			F_SHORT HSI(Grayscale c);
			F_SHORT HSI(RGB c);
			F_GETTER string Name() {
				return "HSI";
			};
			F_GETTER Scalar First() {
				return Hue;
			};
			F_GETTER Scalar Second() {
				return Saturation;
			};
			F_GETTER Scalar Third() {
				return Intensity;
			};
		};

		struct YUV : Tenary {
			Scalar Y; //0...1
			Scalar U;  //-0.5~0.5
			Scalar V;  //-0.5~0.5
			F_SHORT YUV(Scalar y, Scalar u, Scalar v);
			F_SHORT YUV(RGB c);
			F_GETTER string Name() {
				return "YUV";
			};
			F_GETTER Scalar First() {
				return Y;
			};
			F_GETTER Scalar Second() {
				return U;
			};
			F_GETTER Scalar Third() {
				return V;
			};
			int intY() {
				return int(Y * (235 - 16) + 16);
			}
			 
			int intU() {
				return int((U + 0.5) * (240 - 16) + 16);
			}

			int intV() {
				return int((V + 0.5) * (240 - 16) + 16);
			}
		};

		struct CIEXYZ : Tenary {
			/* CIEXYZ, Observer 2°, Illuminant D65 */
			constexpr static Scalar Xref = 0.9505;
			constexpr static Scalar Yref = 1.0000;
			constexpr static Scalar Zref = 1.0890;
			Scalar X;	// 0 .. Xref
			Scalar Y;	// 0 .. Yref
			Scalar Z;	// 0 .. Zref
			F_SHORT CIEXYZ(Scalar X, Scalar Y, Scalar Z);
			F_SHORT CIEXYZ(RGB c);
			F_SHORT CIEXYZ(CIELab c);
			F_GETTER string Name() {
				return "CIEXYZ";
			};
			F_GETTER Scalar First() {
				return X;
			};
			F_GETTER Scalar Second() {
				return Y;
			};
			F_GETTER Scalar Third() {
				return Z;
			};
		};
		struct CIELab : Tenary {
			Scalar L;
			// 4 / 29 .. 116 * Yref ^ (1 / 3) - 16
			// 0.13793103448275862 .. 100
			Scalar a;
			// -500 * Yref ^ (1 / 3) .. 500 * Xref ^ (1 / 3)
			// -500 .. 491.61000336493856
			Scalar b;
			// -500 * Zref ^ (1 / 3) .. 500 * Yref ^ (1 / 3)
			// -514.4138239050887 .. 500
			F_SHORT CIELab(Scalar L, Scalar a, Scalar b);
			F_SHORT CIELab(RGB c);
			F_SHORT CIELab(CIEXYZ c);
			F_GETTER string Name() {
				return "CIELab";
			};
			F_GETTER Scalar First() {
				return L;
			};
			F_GETTER Scalar Second() {
				return a;
			};
			F_GETTER Scalar Third() {
				return b;
			};
		};

		F_SHORT Grayscale::Grayscale(Scalar i) :
			Intensity(i)
		{
		}

		F_SHORT Grayscale::Grayscale(RGB c)
		{
			Intensity = (c.Red + c.Green + c.Blue) / 3;
		}

		F_SHORT Grayscale::Grayscale(HSI c)
		{
			Intensity = c.Intensity;
		}

		F_SHORT Grayscale::Grayscale(YUV c) {
			Intensity = c.Y;
		}


		F_SHORT RGB::RGB(Scalar r, Scalar g, Scalar b) :
			Red(r), Green(g), Blue(b)
		{
		}

		inline RGB::RGB(int r, int g, int b) :

			Red(r / 255.0), Green(g / 255.0), Blue(b / 255.0) {
		}



		F_SHORT RGB::RGB(Grayscale c) :
			Red(c.Intensity), Green(c.Intensity), Blue(c.Intensity)
		{
		}

		F_SHORT RGB::RGB(HSI c)
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
			} else if(M_PI * 2 / 3 <= h && h < M_PI * 4 / 3) {
				Scalar H = h - M_PI * 2 / 3;
				r = i * (1 - s);
				g = i * (1 + s * cos(H) / cos(M_PI / 3 - H));
				b = 3 * i - (r + g);
			} else {
				Scalar H = h - M_PI * 4 / 3;
				g = i * (1 - s);
				b = i * (1 + s * cos(H) / cos(M_PI / 3 - H));
				r = 3 * i - (g + b);
			};

			Red = r;
			Green = g;
			Blue = b;
		}

		F_SHORT RGB::RGB(CIEXYZ c)
		{
			Red   = c.X *  3.24062548 + c.Y * -1.53720797 + c.Z * -0.49862860;
			Green = c.X * -0.96893071 + c.Y *  1.87575606 + c.Z *  0.04151752;
			Blue  = c.X *  0.05571012 + c.Y * -0.20402105 + c.Z *  1.05699594;
			if (Red < 0)
				Red = 0;
			if (Red > 1)
				Red = 1;
			if (Green < 0)
				Green = 0;
			if (Green > 1)
				Green = 1;
			if (Blue < 0)
				Blue = 0;
			if (Blue > 1)
				Blue = 1;
		}

		F_SHORT RGB::RGB(CIELab c)
		{
			*this = CIEXYZ(c);
		}
		
		F_SHORT YUV::YUV(Scalar y, Scalar u, Scalar v) :
			Y(y), U(u), V(v){
		}

		F_SHORT YUV::YUV(RGB c) {
			Scalar r, g, b;
			Scalar y,u,v;

			r = c.Red;
			g = c.Green;
			b = c.Blue;

			y = 0.299 * r + 0.587 * g + 0.114 * b;
			u = -0.169 * r - 0.331 * g + 0.5 * b;
			v = 0.5 * r - 0.419 * g - 0.081 * b;

			Y = y;
			U = u;
			V = v;
		}

		F_SHORT HSI::HSI(Scalar h, Scalar s, Scalar i) :
			Hue(h), Saturation(s), Intensity(i)
		{
		}

		F_SHORT HSI::HSI(Grayscale c) :
			Hue(0), Saturation(0), Intensity(c.Intensity)
		{
		}

		F_SHORT HSI::HSI(RGB c)
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
			} else {
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

		F_SHORT CIEXYZ::CIEXYZ(Scalar x, Scalar y, Scalar z) :
			X(x), Y(y), Z(z)
		{
		}

		F_SHORT CIEXYZ::CIEXYZ(RGB c)
		{
			X = c.Red * 0.4124 + c.Green * 0.3576 + c.Blue * 0.1805;
			Y = c.Red * 0.2126 + c.Green * 0.7152 + c.Blue * 0.0722;
			Z = c.Red * 0.0193 + c.Green * 0.1192 + c.Blue * 0.9505;
		}

		F_SHORT Scalar

		lab_xyz_f(Scalar x)
		{
			const Scalar ftnth = 0.13793103448275862;
			// 4 / 29
			const Scalar delta = 0.20689655172413793;
			// 6 / 29
			const Scalar delta2 = 0.04280618311533888;
			// delta ^ 2
			if (x > delta) {
				return pow(x, 3.);
			} else {
				return 3 * delta2 * (x - ftnth);
			};
		}

		F_SHORT CIEXYZ::CIEXYZ(CIELab c)
		{
			X = Xref * lab_xyz_f((c.L + 16) / 116 + c.a / 500);
			Y = Yref * lab_xyz_f((c.L + 16) / 116);
			Z = Zref * lab_xyz_f((c.L + 16) / 116 - c.b / 200);
		}

		F_SHORT CIELab::CIELab(Scalar cL, Scalar ca, Scalar cb) :
			L(cL), a(ca), b(cb)
		{
		}

		F_SHORT CIELab::CIELab(RGB c)
		{
			*this = CIEXYZ(c);
		}

		F_SHORT Scalar
		xyz_lab_f(Scalar x)
		{
			const Scalar ftnth = 0.13793103448275862;
			// 4 / 29
			//const Scalar delta = 0.20689655172413793;
			// 6 / 29
			const Scalar delta2 = 0.04280618311533888;
			// delta ^ 2
			const Scalar delta3 = 0.008856451679035631;
			// delta ^ 3
			if (x > delta3) {
				return pow(x, 1. / 3);
			} else {
				return x / (3 * delta2) + ftnth;
			};
		}

		F_SHORT CIELab::CIELab(CIEXYZ c)
		{
			Scalar fx = xyz_lab_f(c.X / CIEXYZ::Xref);
			Scalar fy = xyz_lab_f(c.Y / CIEXYZ::Yref);
			Scalar fz = xyz_lab_f(c.Z / CIEXYZ::Zref);
			L = 116 * fy - 16;
			a = 500 * (fx - fy);
			b = 200 * (fy - fz);
		}
	};
};

#include <DIP/internal/macros_end.hpp>

#endif
