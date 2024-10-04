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
	// ���������ӿ� ��ϵ� �浹ü�� ��� ����
	for (UINT i = 0; i < (UINT)LAYER_TYPE::END; ++i)
	{
		m_vecCollider[i].clear();
	}

	// ���� �ȿ� �ִ� ��ü�鿡�� Tick ȣ��
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
		vector<CObj*>& vecObjects = m_vecObjects[i];
		vector<CObj*>::iterator iter = vecObjects.begin();
		for (; iter != vecObjects.end(); )
		{
			if ((*iter)->IsDead())
			{
				iter = vecObjects.erase(iter);
			}
			else
			{
				(*iter)->Render();
				++iter;
			}
		}			
	}
}

void CLevel::AddObject(CObj* _Object, LAYER_TYPE _Type)
{
	m_vecObjects[(UINT)_Type].push_back(_Object);
	_Object->m_LayerType = _Type; // ������Ʈ�� �Ҽ� ���̾ �˷���
}

void CLevel::DeleteObject(int _LayerIdx)
{	
	for (size_t i = 0; i < m_vecObjects[_LayerIdx].size(); ++i)
	{
		if (m_vecObjects[_LayerIdx][i]->IsDead())
			continue;

		delete m_vecObjects[_LayerIdx][i];
	}	

	m_vecObjects[_LayerIdx].clear();
}

void CLevel::DeleteAllObject()
{
	for (int i = 0; i < (int)LAYER_TYPE::END; ++i)
	{
		DeleteObject(i);
	}
}