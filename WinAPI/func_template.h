#pragma once

#include "pch.h"

template<typename T>
void Delete_Vector(vector<T*>& _vec)
{
	for (size_t i = 0; i < _vec.size(); ++i)
	{
		DELETE(_vec[i]);
	}

	_vec.clear();
}


template<typename T, int ArraySize>
void Delete_Array(T* (&arr)[ArraySize])
{
	for (int i = 0; i < ArraySize; ++i)
	{
		DELETE(arr[i]);
	}
}

//class CLevel;
//void Delete_Array(CLevel* (&arr)[5])
//{
//	for (int i = 0; i < 5; ++i)
//	{
//		DELETE(arr[i]);
//	}
//}