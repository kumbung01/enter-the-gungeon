#include "pch.h"
#include "CTaskMgr.h"

#include "CLevelMgr.h"
#include "CLevel.h"
#include "CObj.h"

CTaskMgr::CTaskMgr()
{
}

CTaskMgr::~CTaskMgr()
{
}

void CTaskMgr::Tick()
{
	for (size_t i = 0; i < m_Task.size(); ++i)
	{
		switch (m_Task[i].Type)
		{
		case TASK_TYPE::CREATE_OBJECT:
		{
			CObj* pObject = (CObj*)m_Task[i].Param0;			
			LAYER_TYPE Type = (LAYER_TYPE)m_Task[i].Param1;
			CLevelMgr::GetInst()->GetCurrentLevel()->AddObject(pObject, Type);
			pObject->Begin();
		}
			break;
		case TASK_TYPE::DELETE_OBJECT:


			break;
		case TASK_TYPE::CHANGE_LEVEL:


			break;	
		}
	}

	m_Task.clear();
}