#include "pch.h"
#include "func.h"
#include "pch.h"
#include "func.h"

#include "CTaskMgr.h"
#include "CDbgRender.h"

void CreateObject(CObj* _NewObject, LAYER_TYPE _Layer)
{
	tTask task = {TASK_TYPE::CREATE_OBJECT,  (DWORD_PTR)_NewObject , (DWORD_PTR)_Layer };
	CTaskMgr::GetInst()->AddTask(task);
}

void DeleteObject(CObj* _DeleteObj)
{
	tTask task = {};

	task.Type = TASK_TYPE::DELETE_OBJECT;
	task.Param0 = (DWORD_PTR)_DeleteObj;

	CTaskMgr::GetInst()->AddTask(task);
}

#include "CObj.h"
bool IsValid(CObj*& _Object)
{
	if (nullptr == _Object)
	{
		return false;
	}	
	else if (_Object->IsDead())
	{
		_Object = nullptr;
		return false;
	}

	return true;
}

void DrawDebugRect(PEN_TYPE _pen, Vec2 _Pos, Vec2 _Scale, float _Duration)
{
	tDbgRenderInfo info = {};

	info.Type = DEBUG_SHAPE::RECT;
	info.Color = _pen;
	info.Position0 = _Pos;	
	info.Scale = _Scale;
	info.Duration = _Duration;
	info.Time = 0.f;

	CDbgRender::GetInst()->AddDbgInfo(info);
}

void DrawDebugCircle(PEN_TYPE _pen, Vec2 _Pos, Vec2 _Scale, float _Duration)
{
	tDbgRenderInfo info = {};

	info.Type = DEBUG_SHAPE::CIRCLE;
	info.Color = _pen;
	info.Position0 = _Pos;
	info.Scale = _Scale;
	info.Duration = _Duration;
	info.Time = 0.f;

	CDbgRender::GetInst()->AddDbgInfo(info);
}

void DrawDebugLine(PEN_TYPE _pen, Vec2 _Start, Vec2 _End, float _Duration)
{
	tDbgRenderInfo info = {};

	info.Type = DEBUG_SHAPE::LINE;
	info.Color = _pen;
	info.Position0 = _Start;
	info.Position1 = _End;	
	info.Duration = _Duration;
	info.Time = 0.f;

	CDbgRender::GetInst()->AddDbgInfo(info);
}
