#include "pch.h"
#include "CLevel.h"

#include "CObj.h"
#include "CTaskMgr.h"
#include "CCamera.h"
#include "CEngine.h"

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

	// 레벨 안에 있는 물체들에게 Tick 호출
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
				if (IsInCamera(*iter))
					m_renderQueue.push(*iter);
				++iter;
			}
		}
	}

	while (!m_renderQueue.empty())
	{
		auto obj = m_renderQueue.top();
		m_renderQueue.pop();
		obj->Render();
	}
}

void CLevel::AddObject(CObj* _Object, LAYER_TYPE _Type)
{
	m_vecObjects[(UINT)_Type].push_back(_Object);
	_Object->m_LayerType = _Type; // 오브젝트의 소속 레이어를 알려줌
}


CObj* CLevel::FindObjectByName(LAYER_TYPE _Layer, const wstring& _Name)
{
	vector<CObj*>& vec = m_vecObjects[(UINT)_Layer];
	
	for (size_t i = 0; i < vec.size(); ++i)
	{
		if (vec[i]->GetName() == _Name)
			return vec[i];
	}

	return nullptr;
}

bool CLevel::IsInCamera(CObj* obj)
{
	Vec2 cameraPos = CEngine::GetInst()->GetResolution() / 2.f;
	Vec2 cameraScale = CEngine::GetInst()->GetResolution() * 1.1f;

	Vec2 objRenderPos = obj->GetRenderPos();
	Vec2 objScale = obj->GetScale();

	Vec2 vDiff = cameraPos - objRenderPos;
	Vec2 scaleDiff = (cameraScale + objScale) / 2.f;

	return (fabs(vDiff.x) < scaleDiff.x && fabs(vDiff.y) < scaleDiff.y);
}

int CLevel::GetObjCount(LAYER_TYPE _layer)
{
	return m_vecObjects[(int)_layer].size();
}

void CLevel::DeleteObjects(int _LayerIdx)
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
		DeleteObjects(i);
	}
}
