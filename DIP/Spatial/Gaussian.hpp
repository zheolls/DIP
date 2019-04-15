#ifndef _DIP_Spatial_Gaussian_hpp_
#define _DIP_Spatial_Gaussian_hpp_

#include <DIP/Config.hpp>
#include <DIP/Math/Gaussian.hpp>
#include <DIP/Types.hpp>
#include <cassert>
#include <cmath>
#include <cstdlib>

#include <DIP/internal/macros_begin.hpp>

namespace DIP {
	namespace Spatial {
		using namespace std;

		F_PROXY ScalarArray
		Gaussian(Scalar sigma)
		{
			Index sz = sigma * 6;
			if (sz % 2 == 0)
				sz++;
			auto ret = Math::Gaussian2D(sigma, sz, sz);
			Scalar s = 0;
			for (Index y = 0; y < ret.rows(); y++)
				for (Index x = 0; x < ret.cols(); x++)
					s += ret(y, x);
			ret /= s;
			return ret;
		}
	};
};

#include <DIP/internal/macros_end.hpp>

#endif
