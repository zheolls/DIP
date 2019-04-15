#ifndef _DIP_Util_GaussianFilter_hpp_
#define _DIP_Util_GaussianFilter_hpp_

#include <DIP/Config.hpp>
#include <DIP/Types.hpp>
#include <cassert>
#include <cmath>
#include <cstdlib>

#include <DIP/internal/macros_begin.hpp>

namespace DIP {
	namespace Util {
		using namespace std;

		F_SHORT ScalarArray
		SGaussianFilter(ScalarArray &in, Scalar sigma)
		{
			auto kern = Spatial::Gaussian(sigma);
			return Spatial::BoxFilter(in, kern);
		}

		F_SHORT ScalarArray
		FGaussianFilter(ScalarArray &in, Scalar sigma)
		{
			auto kern = Spatial::Gaussian(sigma);
			return Freq::SSFilter(in, kern);
		}

		F_PROXY ScalarArray
		GaussianFilter(ScalarArray &in, Scalar sigma)
		{
			// to do: better algo deciding
			if (sigma < 2) {
				return SGaussianFilter(in, sigma);
			} else {
				return FGaussianFilter(in, sigma);
			};
		}
	};
};

#include <DIP/internal/macros_end.hpp>

#endif
