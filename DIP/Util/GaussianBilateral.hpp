#ifndef _DIP_Util_GaussianBilateral_hpp_
#define _DIP_Util_GaussianBilateral_hpp_

#include <DIP/Config.hpp>
#include <DIP/Math/Gaussian.hpp>
#include <DIP/Spatial/Bilateral.hpp>
#include <DIP/Types.hpp>
#include <cassert>
#include <cmath>
#include <cstdlib>

#include <DIP/internal/macros_begin.hpp>

namespace DIP {
	namespace Util {
		using namespace std;

		struct FastBilateralGaussianRangeFilter {
			Scalar sigma;
			// Gaussian(0 .. 3.0) + 0, \sigma = 1
#ifdef __GNUC__
			__attribute__ ((aligned(64)))
#endif
			constexpr static Scalar p[] = {
				0.39894228,  0.39695255,  0.39104269,  0.38138782,  0.36827014,
				0.35206533,  0.3332246 ,  0.31225393,  0.28969155,  0.26608525,
				0.24197072,  0.21785218,  0.19418605,  0.17136859,  0.14972747,
				0.1295176 ,  0.11092083,  0.09404908,  0.07895016,  0.06561581,
				0.05399097,  0.0439836 ,  0.03547459,  0.02832704,  0.02239453,
				0.0175283 ,  0.01358297,  0.01042093,  0.00791545,  0.00595253,
				0.00443185,  0.
			};
			inline static Scalar s1gau(Scalar x) {
				if (x < 0)
					x = -x;
				int l = (int)(x * 10);
				if (l >= 31)
					return 0;
				return p[l] + (p[l] - p[l + 1]) * (x * 10 - l);
			};
			inline Scalar apply(Scalar ref, Scalar v) {
				return s1gau((v - ref) / sigma);
			};
		};
		constexpr Scalar FastBilateralGaussianRangeFilter::p[];

		struct BilateralGaussianRangeFilter {
			Scalar sigma;
			inline Scalar apply(Scalar ref, Scalar v) {
				return Math::Gaussian(ref - v, sigma);
			};
		};

		struct BilateralGaussianSpatialFilter {
			Index rows;
			Index cols;
			ScalarArray skern;
			inline Scalar apply(
					Index x, Index y,
					Index kx, Index ky
					) {
				return skern(ky, kx);
			};
		};

		F_MEDIUM ScalarArray
		GaussianBilateralFilter(ScalarArray &in, Scalar sr, Scalar ss)
		{
			Index sz = ss * 6;
			if (sz % 2 == 0)
				sz += 1;
			FastBilateralGaussianRangeFilter rf;
			rf.sigma = sr;
			BilateralGaussianSpatialFilter sf;
			sf.rows = sz; sf.cols = sz;
			sf.skern = Math::Gaussian2D(ss, sf.rows, sf.cols);
			return Spatial::BilateralFilter<
					FastBilateralGaussianRangeFilter,
					BilateralGaussianSpatialFilter
					>(in, rf, sf);
		}
	};
};

#include <DIP/internal/macros_end.hpp>

#endif
