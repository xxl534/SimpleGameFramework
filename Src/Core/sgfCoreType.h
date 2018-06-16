#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <new.h>
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

#define MIN_STRING_CAPACITY 32
#define INVALID_INDEX -1
#define ALIGNMENT_DEFAULT 8

#define SAFE_RELEASE(p)     { if (p) { (p)->Release(); (p)=NULL; } }
#define SAFE_DELETE(p)		{ if (p) { delete (p); (p)=NULL; } }
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p); (p)=NULL; } }
#define SAFE_FREE(p)		{ if(p) { free(p); p = NULL;} }

template<typename T> void
sgfSwap(T& lhs, T& rhs)
{
	T tmp;
	tmp = lhs;
	lhs = rhs;
	rhs = tmp;
}

#define wchar wchar_t