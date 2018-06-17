#pragma once
/********************************************************************
	created:	2018/06/17
	created:	17:6:2018   13:40
	filename: 	E:\SimpleGameFramework\Src\Core\sgfMatrix.h
	file path:	E:\SimpleGameFramework\Src\Core
	file base:	sgfMatrix
	file ext:	h
	author:		Xiexuelong
	
	purpose:	
*********************************************************************/

namespace sgf
{
	template<template T>
	struct TMatrix44
	{
		union
		{
			struct 
			{
				T _11, _12, _13, _14;
				T _21, _22, _23, _24;
				T _31, _32, _33, _34;
				T _41, _42, _43, _44;
			};
			T f[16];
			T m[4][4];
		};

		T&				operator()(const int32 a_row, const int32 a_col);
		const T&		operator()(const int32 a_row, const int32 a_col) const;
		float*			operator[](const int32 a_row);
		const float*	operator[](const int32 a_row) const;

		TMatrix44<T>&	operator+=(const TMatrix44<T>& a_rhs);
		TMatrix44<T>	operator+(const TMatrix44<T>& a_rhs) const;
		TMatrix44<T>&	operator-=(const TMatrix44<T>& a_rhs);
		TMatrix44<T>	operator-(const TMatrix44<T>& a_rhs) const;
		TMatrix44<T>&	operator*=(const T a_val);
		TMatrix44<T>	operator*(const T a_val) const;
		TMatrix44<T>&	operator/=(const T a_val);
		TMatrix44<T>	operator/(const T a_val) const;
		bool			operator==(const TMatrix44<T>& a_rhs) const;
		bool			operator!=(const TMatrix44<T>& a_rhs) const;
	};
}

#include "sgfMatrix.inl"