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


template<typename T1, typename T2>
void Delete_Map(map<T1, T2>& _map)
{
	typename map<T1, T2>::iterator iter = _map.begin();

	for (; iter != _map.end(); ++iter)
	{
		delete iter->second;
	}

	_map.clear();
}





//class CLevel;
//void Delete_Array(CLevel* (&arr)[5])
//{
//	for (int i = 0; i < 5; ++i)
//	{
//		DELETE(arr[i]);
//	}
//}