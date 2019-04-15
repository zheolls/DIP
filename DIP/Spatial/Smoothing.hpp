#ifndef _DIP_Spatial_Smoothing_hpp_
#define _DIP_Spatial_Smoothing_hpp_

#include <DIP/Config.hpp>
#include <DIP/Types.hpp>
#include <cassert>
#include <cmath>
#include <cstdlib>

#include <DIP/internal/macros_begin.hpp>

namespace DIP {
	namespace Spatial {
		using namespace std;

		F_SHORT ScalarArray
		Smoothing(ScalarArray &in, Index sz)
		{
			assert(sz % 2 == 1);
			ScalarArray k(sz, sz);
			Scalar v = (Scalar)1 / k.size();
			Scalar *p = k.data();
			for (Index i = 0; i < k.size(); i++)
				*(p++) = v;
			return BoxFilter(in, k);
		}
	};
};

#include <DIP/internal/macros_end.hpp>

#endif
