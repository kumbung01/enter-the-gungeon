#include "pch.h"
#include "func.h"
#include "pch.h"
#include "func.h"

#include "CTaskMgr.h"

void CreateObject(CObj* _NewObject, LAYER_TYPE _Layer)
{
	tTask task = {TASK_TYPE::CREATE_OBJECT,  (DWORD_PTR)_NewObject , (DWORD_PTR)_Layer };
	CTaskMgr::GetInst()->AddTask(task);
}
