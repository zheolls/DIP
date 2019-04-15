#ifndef _DIP_Freq_Filter_hpp_
#define _DIP_Freq_Filter_hpp_

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
	namespace Freq {
		using namespace std;

		F_PROXY ComplexArray
		FFFilter(ComplexArray &in, ScalarArray &kernel)
		{
			return Math::CSDotMul(in, kernel)
					/ (in.rows() * in.cols());
		}

		F_PROXY ComplexArray
		FFFilter(ComplexArray &in, ComplexArray &kernel)
		{
			return Math::CCDotMul(in, kernel)
					/ (in.rows() * in.cols());
		}

		F_SHORT ScalarArray
		SFFilter(ScalarArray &in, ScalarArray &kernel)
		{
			auto fin = Math::FFT2(in);
			auto fr = FFFilter(fin, kernel);
			return Math::MIFFT2(fr);
		}

		F_SHORT ComplexArray
		FSFilter(ComplexArray &in, ScalarArray &kernel)
		{
			Index ir, ic, kr, kc, sr, sc;
			ir = in.rows();
			ic = in.cols();
			kr = kernel.rows();
			kc = kernel.cols();
			sr = (ir - kr) / 2;
			sc = (ic - kc) / 2;
			ScalarArray sfk(ir, ic);
			memset(sfk.data(), 0, sfk.size() * sizeof(Scalar));
			for (Index y = 0; y < kr; y++)
				for (Index x = 0; x < kc; x++)
					sfk(y + sr, x + sc) = kernel(y, x);
			sfk = Math::MFFT2(sfk);
			return FFFilter(in, sfk);
		}

		F_SHORT ScalarArray
		SSFilter(ScalarArray &in, ScalarArray &kernel)
		{
			auto fin = Math::FFT2(in);
			auto fr = FSFilter(fin, kernel);
			return Math::MIFFT2(fr);
		}
	};
};

#include <DIP/internal/macros_end.hpp>

#endif
