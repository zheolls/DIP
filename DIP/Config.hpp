#ifndef _DIP_Config_hpp_
#define _DIP_Config_hpp_

#ifdef CONFIG_DIP_INLINE_PROXY
#	define _DIP_DECL_PROXY inline
#else
#	define _DIP_DECL_PROXY
#endif

#ifdef CONFIG_DIP_INLINE_GETTER
#	define _DIP_DECL_GETTER inline
#else
#	define _DIP_DECL_GETTER _DIP_DECL_PROXY
#endif

#ifdef CONFIG_DIP_INLINE_SHORT
#	define _DIP_DECL_SHORT inline
#else
#	define _DIP_DECL_SHORT
#endif

#ifdef CONFIG_DIP_INLINE_MEDIUM
#	define _DIP_DECL_MEDIUM inline
#else
#	define _DIP_DECL_MEDIUM
#endif

#ifdef CONFIG_DIP_INLINE_LONG
#	define _DIP_DECL_LONG inline
#else
#	define _DIP_DECL_LONG
#endif

#ifdef CONFIG_DIP_SCALAR_TYPE_FLOAT
#	define _DIP_SCALAR_TYPE float
#endif

#ifdef CONFIG_DIP_SCALAR_TYPE_DOUBLE
#	define _DIP_SCALAR_TYPE double
#endif

#ifdef CONFIG_DIP_SCALAR_TYPE_LONGDOUBLE
#	define _DIP_SCALAR_TYPE long double
#endif

#ifdef CONFIG_DIP_EIGEN_INDEX_TYPE
#	define EIGEN_DEFAULT_DENSE_INDEX_TYPE CONFIG_DIP_EIGEN_INDEX_TYPE
#else
#	define EIGEN_DEFAULT_DENSE_INDEX_TYPE long
#endif

#endif
