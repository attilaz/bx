/*
 * Copyright 2016- Attila Kocsis. All rights reserved.
 * License: https://github.com/attilaz/tinystl#license-bsd-2-clause
 */

#ifndef TINYSTL_CONFIG_H_HEADER_GUARD
#define TINYSTL_CONFIG_H_HEADER_GUARD

#ifndef TINYSTL_ASSERT
#ifdef DEBUG
	#include <assert.h>
	#define TINYSTL_ASSERT(expr, msg)    assert(expr && msg)
#else
	#define TINYSTL_ASSERT(expr, msg)    do {} while (0)
#endif
#endif

// Define extra functions in config.h to extend functionality

//#define TINYSTL_VECTOR_CLASS_EXTRA
//#define TINYSTL_UNORDERED_MAP_CLASS_EXTRA
//#define TINYSTL_UNORDERED_SET_CLASS_EXTRA
//#define TINYSTL_VECTOR_CLASS_EXTRA

#endif
