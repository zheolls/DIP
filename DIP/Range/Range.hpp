#ifndef _DIP_Range_Range_hpp_
#define _DIP_Range_Range_hpp_

#include <DIP/Config.hpp>
#include <DIP/Math/ArrayOperations.hpp>
#include <DIP/Math/FFT.hpp>
#include <DIP/Types.hpp>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <cstring>

#include <DIP/internal/macros_begin.hpp>

namespace DIP {
	namespace Range {
		using namespace std;

		template <
				bool usan = false,
				bool dsan = false,
				bool lsan = false,
				bool rsan = false
			 >
		F_MEDIUM Scalar
		Range_kApply(
				ScalarArray &in,
				ScalarArray &nhood,
				Index x,
				Index y
			     )
		{
			Index hkr, hkc;
			hkr = nhood.rows() / 2;
			hkc = nhood.cols() / 2;
			Scalar min, max;
			min = INFINITY;
			max = -INFINITY;
			for (Index i = 0; i < nhood.rows(); i++)
				for (Index j = 0; j < nhood.cols(); j++) {
					if (isZero(nhood(i, j)))
						continue;
					Index iy, ix;
					iy = y - (hkr - i);
					ix = x - (hkc - j);
					if (usan && iy < 0)
						iy = 0;
					if (dsan && iy >= nhood.rows())
						iy = nhood.rows() - 1;
					if (lsan && ix < 0)
						ix = 0;
					if (rsan && ix >= nhood.cols())
						ix = nhood.cols() - 1;
					Scalar v = in(iy, ix);
					if (v < min)
						min = v;
					if (v > max)
						max = v;
				};
			return max - min;
		}

		F_LONG ScalarArray
		Range(ScalarArray &in, ScalarArray &nhood)
		{
			assert(nhood.rows() % 2 == 1);
			assert(nhood.cols() % 2 == 1);
			Index ir, ic, hkr, hkc;
			ir = in.rows();
			ic = in.cols();
			hkr = nhood.rows() / 2;
			hkc = nhood.cols() / 2;
			ScalarArray ret(ir, ic);
			Index y = 0, x;
			for (; y < hkr; y++) {
				for (x = 0; x < hkc; x++)
					ret(y, x) = Range_kApply<true, false,
							true, false>
							(in, nhood, x, y);
				for (; x < ic - hkc; x++)
					ret(y, x) = Range_kApply<true, false,
							false, false>
							(in, nhood, x, y);
				for (; x < ic; x++)
					ret(y, x) = Range_kApply<true, false,
							false, true>
							(in, nhood, x, y);
			};
			for (; y < ir - hkr; y++) {
				for (x = 0; x < hkc; x++)
					ret(y, x) = Range_kApply<false, false,
							true, false>
							(in, nhood, x, y);
				for (; x < ic - hkc; x++)
					ret(y, x) = Range_kApply<false, false,
							false, false>
							(in, nhood, x, y);
				for (; x < ic; x++)
					ret(y, x) = Range_kApply<false, false,
							false, true>
							(in, nhood, x, y);
			};
			for (; y < ir; y++) {
				for (x = 0; x < hkc; x++)
					ret(y, x) = Range_kApply<false, true,
							true, false>
							(in, nhood, x, y);
				for (; x < ic - hkc; x++)
					ret(y, x) = Range_kApply<false, true,
							false, false>
							(in, nhood, x, y);
				for (; x < ic; x++)
					ret(y, x) = Range_kApply<false, true,
							false, true>
							(in, nhood, x, y);
			};
			return ret;
		}

		F_SHORT ScalarArray
		Range(ScalarArray &in, Scalar nhood)
		{
			Index r = (Index)nhood, d = 2 * r + 1;
			ScalarArray k(d, d);
			for (Index y = -r; y <= r; y++)
				for (Index x = -r; x <= r; x++)
					if ((Scalar)(x * x + y * y) <= nhood) {
						k(y + r, x + r) = 1;
					} else {
						k(y + r, x + r) = 0;
					};
			return Range(in, k);
		}
	};
};

#include <DIP/internal/macros_end.hpp>

#endif
