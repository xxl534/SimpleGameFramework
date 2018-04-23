#pragma once

#include <string.h>
#ifndef ASSERT
#include<assert.h>
#define ASSERT assert
#endif // !ASSERT

#ifdef _MSC_VER
	#define INLINE		__forceinline
#else
	#define INLINE		inline
#endif

typedef signed char int8;
typedef signed short int16;
typedef signed int int32;
typedef signed long long int64;
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;

#define wchar wchar_t