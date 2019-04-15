#ifndef _DIP_IO_hpp_
#define _DIP_IO_hpp_

#include <DIP/Config.hpp>
//#include <Magick++.h>
// Fix garbages from ImageMagick
#undef Intensity

#include <cmath>
#include <cstdlib>
#include <string>
#include <DIP/ColorSpace.hpp>
#include <DIP/Exceptions.hpp>
#include <DIP/Types.hpp>

using namespace std;
using namespace Magick;

#include <DIP/internal/macros_begin.hpp>

namespace DIP {
	namespace IO {
		using namespace std;

		bool magickNeedInit = true;

		F_MEDIUM void
		magickInit()
		{
			if (!magickNeedInit)
				return;
			magickNeedInit = false;
			char defdllpath[] = ".";
			char *dllpath = getenv("MAGICK_DLLPATH");
			if (dllpath == nullptr)
				dllpath = defdllpath;
			InitializeMagick(dllpath);
		};

		inline void
		getRGB(Quantum *&px, Scalar &r, Scalar &g, Scalar &b, size_t ch)
		{
			switch (ch) {
				case 1: {
					r = (Scalar)*px++ / QuantumRange;
					g = r;
					b = r;
					break;
				};
				case 3: {
					r = (Scalar)*px++ / QuantumRange;
					g = (Scalar)*px++ / QuantumRange;
					b = (Scalar)*px++ / QuantumRange;
					break;
				};
				case 4: {
					r = (Scalar)*px++ / QuantumRange;
					g = (Scalar)*px++ / QuantumRange;
					b = (Scalar)*px++ / QuantumRange;
					px++;
					break;
				};
				default:
					throw Exception::
						UnknownColorFormatError();
			};
		}

		inline void
		setRGB(Quantum *&px, Scalar &r, Scalar &g, Scalar &b, size_t ch)
		{
			switch (ch) {
				case 1: {
					*px++ = (r + g + b) * QuantumRange / 3;
					break;
				};
				case 3: {
					*px++ = r * QuantumRange;
					*px++ = g * QuantumRange;
					*px++ = b * QuantumRange;
					break;
				};
				case 4: {
					*px++ = r * QuantumRange;
					*px++ = g * QuantumRange;
					*px++ = b * QuantumRange;
					*px++ = 0;
					break;
				};
				default:
					throw Exception::
						UnknownColorFormatError();
			};
		}

		inline void
		setRGB_s(
				Quantum *&px,
				Scalar &r, Scalar &g, Scalar &b,
				size_t ch,
				Scalar sr = 0,
				Scalar sg = 0,
				Scalar sb = 0
			)
		{
			if (r < 0 || g < 0 || b < 0 ||
					r > 1 || g > 1 || b > 1) {
				r = sr;
				g = sg;
				b = sb;
			};
			switch (ch) {
				case 1: {
					*px++ = (r + g + b) * QuantumRange / 3;
					break;
				};
				case 3: {
					*px++ = r * QuantumRange;
					*px++ = g * QuantumRange;
					*px++ = b * QuantumRange;
					break;
				};
				case 4: {
					*px++ = r * QuantumRange;
					*px++ = g * QuantumRange;
					*px++ = b * QuantumRange;
					*px++ = 0;
					break;
				};
				default:
					throw Exception::
						UnknownColorFormatError();
			};
		}

		template <class CS = ColorSpace::RGB>
		F_LONG void
		Load(
				std::string uri,
				ScalarArray &A,
				ScalarArray &B,
				ScalarArray &C
				)
		{
			magickInit();
			Image im(uri);
			im.type(TrueColorType);
			A.resize(im.rows(), im.columns());
			B.resize(im.rows(), im.columns());
			C.resize(im.rows(), im.columns());
			Scalar *pA = A.data(), *pB = B.data(), *pC = C.data();
			Quantum *pixels =
				im.getPixels(0, 0, im.columns(), im.rows());
			size_t channels = im.channels();
			for (Index c = 0; c < A.size(); c++) {
				Scalar r, g, b;
				getRGB(pixels, r, g, b, channels);

				CS rc = ColorSpace::RGB(r, g, b);;
				*(pA++) = rc.First();
				*(pB++) = rc.Second();
				*(pC++) = rc.Third();
			};
		}

		template <class CS = ColorSpace::Grayscale>
		F_LONG void
		Load(std::string uri, ScalarArray &A)
		{
			magickInit();
			Image img(uri);
			img.type(TrueColorType);
			A.resize(img.rows(), img.columns());
			Scalar *pA = A.data();
			Quantum *pixels =
				img.getPixels(0, 0, img.columns(), img.rows());
			size_t channels = img.channels();
			for (Index c = 0; c < A.size(); c++) {
				Scalar r, g, b;
				getRGB(pixels, r, g, b, channels);

				CS rc = ColorSpace::RGB(r, g, b);
				*(pA++) = rc.First();
			};
		}

		template <class CS = ColorSpace::RGB>
		F_LONG void
		Save(
				std::string uri,
				ScalarArray &A,
				ScalarArray &B,
				ScalarArray &C,
				bool safe = true // check out of range
				)
		{
			magickInit();
			Image im(Geometry(A.cols(), A.rows()), Color("white"));
			im.type(TrueColorType);
			Quantum *pixels =
				im.getPixels(0, 0, im.columns(), im.rows());
			size_t channels = im.channels();
			auto pA = A.data(), pB = B.data(), pC = C.data();
			if (safe) {
				for (Index i = 0; i < A.size(); i++) {
					Scalar a, b, c;
					a = *(pA++);
					b = *(pB++);
					c = *(pC++);

					ColorSpace::RGB oc = CS(a, b, c);
					setRGB(pixels,
							oc.Red,
							oc.Green,
							oc.Blue,
							channels);
				};
			} else {
				for (Index i = 0; i < A.size(); i++) {
					Scalar a, b, c;
					a = *(pA++);
					b = *(pB++);
					c = *(pC++);

					ColorSpace::RGB oc = CS(a, b, c);
					setRGB_s(pixels,
							oc.Red,
							oc.Green,
							oc.Blue,
							channels);
				};
			};
			im.syncPixels();
			im.write(uri);
		}

		template <class CS = ColorSpace::Grayscale>
		F_LONG void
		Save(std::string uri, ScalarArray &A)
		{
			magickInit();
			Image im(Geometry(A.cols(), A.rows()), Color("white"));
			im.type(TrueColorType);
			Quantum *pixels =
				im.getPixels(0, 0, im.columns(), im.rows());
			size_t channels = im.channels();
			auto pA = A.data();
			for (Index c = 0; c < A.size(); c++) {
				Scalar a = *(pA++);

				ColorSpace::RGB oc = CS(a);
				setRGB(pixels,
						oc.Red, oc.Green, oc.Blue,
						channels);
			};
			im.syncPixels();
			im.write(uri);
		}
	};
};

#include <DIP/internal/macros_end.hpp>

#endif
