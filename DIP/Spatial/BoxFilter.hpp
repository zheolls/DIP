#ifndef _DIP_Spatial_BoxFilter_hpp_
#define _DIP_Spatial_BoxFilter_hpp_

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
				bool usan = false,
				bool dsan = false,
				bool lsan = false,
				bool rsan = false
			>
		F_SHORT Scalar
		boxInMajor_kApply(
				ScalarArray &in,
				ScalarArray &kernel,
				Index x,
				Index y
				)
		{
			Index krh, kch;
			krh = kernel.rows() / 2;
			kch = kernel.cols() / 2;
			Scalar ret = 0;
			for (Index i = 0; i < kernel.rows(); i++)
				for (Index j = 0; j < kernel.cols(); j++) {
					Index inr, inc;
					inr = y - krh + i;
					inc = x - kch + j;
					if (usan && inr < 0)
						inr = 0;
					if (dsan && inr >= in.rows())
						inr = in.rows() - 1;
					if (lsan && inc < 0)
						inc = 0;
					if (rsan && inc >= in.cols())
						inc = in.cols() - 1;
					ret += kernel(i, j) * in(inr, inc);
				};
			return ret;
		}

		F_LONG ScalarArray
		boxInMajor(ScalarArray &in, ScalarArray &kernel)
		{
			Index ir, ic, krh, kch;
			ir = in.rows();
			ic = in.cols();
			krh = kernel.rows() / 2;
			kch = kernel.cols() / 2;
			ScalarArray ret(ir, ic);
			Index y = 0;
			for (; y < krh; y++) {
				Index x = 0;
				for (; x < kch; x++)
					ret(y, x) = boxInMajor_kApply<
						true, false, true, false
						>(in, kernel, x, y);
				for (; x < ic - kch; x++)
					ret(y, x) = boxInMajor_kApply<
						true, false, false, false
						>(in, kernel, x, y);
				for (; x < ic; x++)
					ret(y, x) = boxInMajor_kApply<
						true, false, false, true
						>(in, kernel, x, y);
			};
			for (; y < ir - krh; y++) {
				Index x = 0;
				for (; x < kch; x++)
					ret(y, x) = boxInMajor_kApply<
						false, false, true, false
						>(in, kernel, x, y);
				for (; x < ic - kch; x++)
					ret(y, x) = boxInMajor_kApply<
						false, false, false, false
						>(in, kernel, x, y);
				for (; x < ic; x++)
					ret(y, x) = boxInMajor_kApply<
						false, false, false, true
						>(in, kernel, x, y);
			};
			for (; y < ir; y++) {
				Index x = 0;
				for (; x < kch; x++)
					ret(y, x) = boxInMajor_kApply<
						false, true, true, false
						>(in, kernel, x, y);
				for (; x < ic - kch; x++)
					ret(y, x) = boxInMajor_kApply<
						false, true, false, false
						>(in, kernel, x, y);
				for (; x < ic; x++)
					ret(y, x) = boxInMajor_kApply<
						false, true, false, true
						>(in, kernel, x, y);
			};
			return ret;
		}

		F_PROXY ScalarArray
		BoxFilter(ScalarArray &in, ScalarArray &kernel)
		{
			assert(kernel.rows() % 2 == 1);
			assert(kernel.cols() % 2 == 1);
			return boxInMajor(in, kernel);
		}
	};
};

#include <DIP/internal/macros_end.hpp>

#endif
