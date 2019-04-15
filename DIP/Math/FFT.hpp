#ifndef _DIP_Math_FFT_hpp_
#define _DIP_Math_FFT_hpp_

#include <DIP/Config.hpp>
#include <DIP/Math/ArrayOperations.hpp>
#include <DIP/Types.hpp>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <fftw3.h>

#include <DIP/internal/macros_begin.hpp>

namespace DIP {
	namespace Math {
		using namespace std;

		F_PROXY ComplexArray
		FFT2(ScalarArray &in)
		{
			ComplexArray ret(in.rows(), in.cols());
#if defined(CONFIG_DIP_SCALAR_TYPE_FLOAT)
			fftwf_plan plan = fftwf_plan_dft_r2c_2d(
					in.rows(),
					in.cols(),
					in.data(),
					(fftwf_complex *)ret.data(),
					FFTW_ESTIMATE
					);
			fftwf_execute(plan);
			fftwf_destroy_plan(plan);
#elif defined(CONFIG_DIP_SCALAR_TYPE_DOUBLE)
			fftw_plan plan = fftw_plan_dft_r2c_2d(
					in.rows(),
					in.cols(),
					in.data(),
					(fftw_complex *)ret.data(),
					FFTW_ESTIMATE
					);
			fftw_execute(plan);
			fftw_destroy_plan(plan);
#elif defined(CONFIG_DIP_SCALAR_TYPE_LONGDOUBLE)
			fftwl_plan plan = fftwl_plan_dft_r2c_2d(
					in.rows(),
					in.cols(),
					in.data(),
					(fftwl_complex *)ret.data(),
					FFTW_ESTIMATE
					);
			fftwl_execute(plan);
			fftwl_destroy_plan(plan);
#else
#error Unsupported scalar type
#endif
			// to do: fill out remaining half?
			return ret;
		}

		F_SHORT ScalarArray
		MFFT2(ScalarArray &in)
		{
			auto ret = FFT2(in);
			return ArrayABS(ret);
		}

		F_SHORT ScalarArray
		AFFT2(ScalarArray &in)
		{
			auto ret = FFT2(in);
			return ArrayARG(ret);
		}

		F_PROXY ComplexArray
		IFFT2(ComplexArray &in)
		{
			ComplexArray ret(in.rows(), in.cols());
#if defined(CONFIG_DIP_SCALAR_TYPE_FLOAT)
			fftwf_plan plan = fftwf_plan_dft_2d(
					in.rows(),
					in.cols(),
					(fftwf_complex *)in.data(),
					(fftwf_complex *)ret.data(),
					FFTW_BACKWARD,
					FFTW_ESTIMATE
					);
			fftwf_execute(plan);
			fftwf_destroy_plan(plan);
#elif defined(CONFIG_DIP_SCALAR_TYPE_DOUBLE)
			fftw_plan plan = fftw_plan_dft_2d(
					in.rows(),
					in.cols(),
					(fftw_complex *)in.data(),
					(fftw_complex *)ret.data(),
					FFTW_BACKWARD,
					FFTW_ESTIMATE
					);
			fftw_execute(plan);
			fftw_destroy_plan(plan);
#elif defined(CONFIG_DIP_SCALAR_TYPE_LONGDOUBLE)
			fftwl_plan plan = fftwl_plan_dft_2d(
					in.rows(),
					in.cols(),
					(fftwl_complex *)in.data(),
					(fftwl_complex *)ret.data(),
					FFTW_BACKWARD,
					FFTW_ESTIMATE
					);
			fftwl_execute(plan);
			fftwl_destroy_plan(plan);
#else
#error Unsupported scalar type
#endif
			return ret;
		}

		F_SHORT ScalarArray
		MIFFT2(ComplexArray &in)
		{
			ScalarArray ret(in.rows(), in.cols());
#if defined(CONFIG_DIP_SCALAR_TYPE_FLOAT)
			fftwf_plan plan = fftwf_plan_dft_c2r_2d(
					in.rows(),
					in.cols(),
					(fftwf_complex *)in.data(),
					(Scalar *)ret.data(),
					FFTW_ESTIMATE
					);
			fftwf_execute(plan);
			fftwf_destroy_plan(plan);
#elif defined(CONFIG_DIP_SCALAR_TYPE_DOUBLE)
			fftw_plan plan = fftw_plan_dft_c2r_2d(
					in.rows(),
					in.cols(),
					(fftw_complex *)in.data(),
					(Scalar *)ret.data(),
					FFTW_ESTIMATE
					);
			fftw_execute(plan);
			fftw_destroy_plan(plan);
#elif defined(CONFIG_DIP_SCALAR_TYPE_LONGDOUBLE)
			fftwl_plan plan = fftwl_plan_dft_c2r_2d(
					in.rows(),
					in.cols(),
					(fftwl_complex *)in.data(),
					(Scalar *)ret.data(),
					FFTW_ESTIMATE
					);
			fftwl_execute(plan);
			fftwl_destroy_plan(plan);
#else
#error Unsupported scalar type
#endif
			return ret;
		}
	};
};

#include <DIP/internal/macros_end.hpp>

#endif
