#ifndef _DIP_Spatial_Bilateral_hpp_
#define _DIP_Spatial_Bilateral_hpp_

#include <DIP/Config.hpp>
#include <DIP/Types.hpp>
#include <cassert>
#include <cmath>
#include <cstdlib>

#include <DIP/internal/macros_begin.hpp>

namespace DIP {
	namespace Spatial {
		using namespace std;

		template<
			class RF, class SF,
			bool usan, bool dsan, bool lsan, bool rsan
			>
		F_MEDIUM Scalar
		Bilateral_kApply(
				ScalarArray &in,
				RF &RFilter, SF &SFilter,
				Index x, Index y
				)
		{
			Index hkr, hkc;
			hkr = SFilter.rows / 2;
			hkc = SFilter.cols / 2;
			Scalar v = 0, w = 0;
			for (Index i = -hkr; i <= hkr; i++)
				for (Index j = -hkc; j <= hkc; j++) {
					Index ir, ic;
					ir = y + i;
					ic = x + j;
					if (usan && ir < 0)
						ir = 0;
					if (dsan && ir >= in.rows())
						ir = in.rows() - 1;
					if (lsan && ic < 0)
						ic = 0;
					if (rsan && ic >= in.cols())
						ic = in.cols() - 1;
					Scalar rv = RFilter.apply(in(y, x),
							in(ir, ic));
					Scalar sv = SFilter.apply(x, y,
							j + hkc, i + hkr);
					w += rv * sv;
					v += in(ir, ic) * (rv * sv);
				};
			return v / w;
		}

		template<class RF, class SF>
		F_LONG ScalarArray
		BilateralFilter(ScalarArray &in, RF &RFilter, SF &SFilter)
		{
			assert(SFilter.rows % 2 == 1);
			assert(SFilter.cols % 2 == 1);
			Index ir, ic, krh, kch;
			ir = in.rows();
			ic = in.cols();
			krh = SFilter.rows / 2;
			kch = SFilter.cols / 2;
			ScalarArray ret(ir, ic);
			Index y = 0;
			for (; y < krh; y++) {
				Index x = 0;
				for (; x < kch; x++)
					ret(y, x) = Bilateral_kApply<
						RF, SF,
						true, false, true, false
						>(in, RFilter, SFilter, x, y);
				for (; x < ic - kch; x++)
					ret(y, x) = Bilateral_kApply<
						RF, SF,
						true, false, false, false
						>(in, RFilter, SFilter, x, y);
				for (; x < ic; x++)
					ret(y, x) = Bilateral_kApply<
						RF, SF,
						true, false, false, true
						>(in, RFilter, SFilter, x, y);
			};
			for (; y < ir - krh; y++) {
				Index x = 0;
				for (; x < kch; x++)
					ret(y, x) = Bilateral_kApply<
						RF, SF,
						false, false, true, false
						>(in, RFilter, SFilter, x, y);
				for (; x < ic - kch; x++)
					ret(y, x) = Bilateral_kApply<
						RF, SF,
						false, false, false, false
						>(in, RFilter, SFilter, x, y);
				for (; x < ic; x++)
					ret(y, x) = Bilateral_kApply<
						RF, SF,
						false, false, false, true
						>(in, RFilter, SFilter, x, y);
			};
			for (; y < ir; y++) {
				Index x = 0;
				for (; x < kch; x++)
					ret(y, x) = Bilateral_kApply<
						RF, SF,
						false, true, true, false
						>(in, RFilter, SFilter, x, y);
				for (; x < ic - kch; x++)
					ret(y, x) = Bilateral_kApply<
						RF, SF,
						false, true, false, false
						>(in, RFilter, SFilter, x, y);
				for (; x < ic; x++)
					ret(y, x) = Bilateral_kApply<
						RF, SF,
						false, true, false, true
						>(in, RFilter, SFilter, x, y);
			};
			return ret;
		}
	};
};

#include <DIP/internal/macros_end.hpp>

#endif
