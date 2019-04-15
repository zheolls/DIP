#ifndef _DIP_Math_Gaussian_hpp_
#define _DIP_Math_Gaussian_hpp_

#include <DIP/Config.hpp>

#include <cstdlib>
#include <cmath>
#include <DIP/Types.hpp>

#include <DIP/internal/macros_begin.hpp>

namespace DIP {
	namespace Math {
		using namespace std;
		F_SHORT Scalar
		Gaussian(
				Scalar x,
				Scalar sigma = 1
			)
		{
			return exp(x * x / (sigma * sigma) / -2) /
				sigma / 2.5066282746310002;
			// sqrt(2 * M_PI) == 2.5066282746310002
		}

		F_MEDIUM ScalarArray
		Gaussian1D(
				Scalar sigma,
				Index size
			  )
		{
			Index sh = size / 2;
			ScalarArray ret(1, size);
			if (size % 2 == 1) {
				for (Index i = -sh; i <= sh; i++)
					ret(sh + i) = Gaussian(i, sigma);
			} else {
				for (Index i = -sh; i < sh; i++)
					ret(sh + i) = Gaussian((Scalar) i +
							0.5, sigma);
			};
			return ret;
		}

		F_MEDIUM ScalarArray
		RGaussian1D(
				Scalar sigma,
				Index size
			  )
		{
			Index sh = size / 2;
			ScalarArray ret(1, size);
			if (size % 2 == 1) {
				for (Index i = -sh; i <= sh; i++)
					ret(sh + i) = Gaussian(sh - i,
							sigma);
			} else {
				for (Index i = 0; i < sh; i++)
					ret(i) = Gaussian((Scalar) i, sigma);
				for (Index i = sh - 1; i >= 0; i--)
					ret(i) = ret(sh - i - 1, 0);
			};
			return ret;
		}

		F_MEDIUM ScalarArray
		Gaussian2D(
				Scalar sigma,
				Index r,
				Index c
			  )
		{
			ScalarArray ret(r, c);
			auto rv = Gaussian1D(sigma, r);
			auto cv = Gaussian1D(sigma, c);
			for (Index y = 0; y < r; y++)
				for (Index x = 0; x < c; x++)
					ret(y, x) = rv(y) * cv(x);
			return ret;
		}

		F_MEDIUM ScalarArray
		RGaussian2D(
				Scalar sigma,
				Index r,
				Index c
			  )
		{
			ScalarArray ret(r, c);
			auto rv = RGaussian1D(sigma, r);
			auto cv = RGaussian1D(sigma, c);
			for (Index y = 0; y < r; y++)
				for (Index x = 0; x < c; x++)
					ret(y, x) = rv(y) * cv(x);
			return ret;
		}
	};
};

#include <DIP/internal/macros_end.hpp>

#endif
