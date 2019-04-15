#ifndef _DIP_Math_ArrayOperations_hpp_
#define _DIP_Math_ArrayOperations_hpp_

#include <DIP/Config.hpp>

#include <cstdlib>
#include <cmath>
#include <DIP/Types.hpp>

#include <DIP/internal/macros_begin.hpp>

namespace DIP {
	namespace Math {
		using namespace std;

		F_SHORT ComplexArray
		CCDotMul(ComplexArray &A, ComplexArray &B)
		{
			assert(A.rows() == B.rows());
			assert(A.cols() == B.cols());
			ComplexArray R(A.rows(), A.cols());
			for (Index y = 0; y < A.rows(); y++)
				for (Index x = 0; x < A.cols(); x++)
					R(y, x) = A(y, x) * B(y, x);
			return R;
		}

		F_SHORT ComplexArray
		CSDotMul(ComplexArray &A, ScalarArray &B)
		{
			assert(A.rows() == B.rows());
			assert(A.cols() == B.cols());
			ComplexArray R(A.rows(), A.cols());
			for (Index y = 0; y < A.rows(); y++)
				for (Index x = 0; x < A.cols(); x++) {
					R(y, x).real(A(y, x).real() * B(y, x));
					R(y, x).imag(A(y, x).imag() * B(y, x));
				};
			return R;
		}

		F_SHORT ScalarArray
		SSDotMul(ScalarArray &A, ScalarArray &B)
		{
			assert(A.rows() == B.rows());
			assert(A.cols() == B.cols());
			ScalarArray R(A.rows(), A.cols());
			for (Index y = 0; y < A.rows(); y++)
				for (Index x = 0; x < A.cols(); x++)
					R(y, x) = A(y, x) * B(y, x);
			return R;
		}

		F_SHORT ScalarArray
		ArrayABS(ComplexArray &in)
		{
			ScalarArray ret(in.rows(), in.cols());
			for (Index y = 0; y < in.rows(); y++)
				for (Index x = 0; x < in.cols(); x++)
					ret(y, x) = abs(in(y, x));
			return ret;
		}

		F_SHORT ScalarArray
		ArrayARG(ComplexArray &in)
		{
			ScalarArray ret(in.rows(), in.cols());
			for (Index y = 0; y < in.rows(); y++)
				for (Index x = 0; x < in.cols(); x++) {
					auto v = in(y, x);
					auto r = atan(v.imag() / v.real());
					if (r < 0)
						r += 2 * M_PI;
					ret(y, x) = r;
				}
			return ret;
		}
	};
};

#include <DIP/internal/macros_end.hpp>

#endif
