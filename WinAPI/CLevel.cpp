#include "pch.h"
#include "CLevel.h"

#include "CObj.h"

CLevel::CLevel()
{
}

CLevel::~CLevel()
{
	for (UINT i = 0; i < (UINT)LAYER_TYPE::END; ++i)
	{
		Delete_Vector(m_vecObjects[i]);
	}
}

void CLevel::Begin()
{
	for (UINT i = 0; i < (UINT)LAYER_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_vecObjects[i].size(); ++j)
		{
			m_vecObjects[i][j]->Begin();
		}
	}	
}

void CLevel::Tick()
{
	// 이전프레임에 등록된 충돌체들 등록 해제
	for (UINT i = 0; i < (UINT)LAYER_TYPE::END; ++i)
	{
		m_vecCollider[i].clear();
	}



	for (UINT i = 0; i < (UINT)LAYER_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_vecObjects[i].size(); ++j)
		{
			m_vecObjects[i][j]->Tick();
		}
	}
}

void CLevel::FinalTick()
{
	for (UINT i = 0; i < (UINT)LAYER_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_vecObjects[i].size(); ++j)
		{
			m_vecObjects[i][j]->FinalTick();
		}
	}
}

void CLevel::Render()
{
	for (UINT i = 0; i < (UINT)LAYER_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_vecObjects[i].size(); ++j)
		{
			m_vecObjects[i][j]->Render();
		}
	}
}

void CLevel::AddObject(CObj* _Object, LAYER_TYPE _Type)
{
	m_vecObjects[(UINT)_Type].push_back(_Object);
	_Object->m_LayerType = _Type; // 오브젝트의 소속 레이어를 알려줌
}