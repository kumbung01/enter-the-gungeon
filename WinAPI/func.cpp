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

void ChangeLevel(LEVEL_TYPE _NextLevel)
{
	tTask task = {};

	task.Type = TASK_TYPE::CHANGE_LEVEL;
	task.Param0 = (DWORD_PTR)_NextLevel;

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

Vec2 Rotate(Vec2 _Dir, float _Angle)
{
	_Dir.Normalize();

	Vec2 vRotate = Vec2( cosf(_Angle) * _Dir.x - sinf(_Angle) * _Dir.y
						, sinf(_Angle) * _Dir.x + cosf(_Angle) * _Dir.y);

	return vRotate;
}

bool GetClockWise(Vec2 _A, Vec2 _B)
{
	float F = _A.x* _B.y - _A.y * _B.x;

	if (0.f < F)
		return true;

	return false;
}

#include "CAssetMgr.h"
#include "CAsset.h"
void SaveAssetRef(CAsset* _Asset, FILE* _File)
{
	// �����Ϸ��� Asset �� nullptr �̸� 0 �ϳ� �����Ѵ�.
	int Asset = !!_Asset;
	fwrite(&Asset, sizeof(int), 1, _File);
	if (!Asset)
		return;

	// Asset �� ������ �����Ѵ�.
	ASSET_TYPE type = _Asset->GetAssetType();
	fwrite(&type, sizeof(ASSET_TYPE), 1, _File);

	// �����Ϸ��� Asset �� Key, Path �� �����´�.
	const wstring& strKey = _Asset->GetKey();
	const wstring& strPath = _Asset->GetRelativePath();
	
	// Asset �� Key, Path ���ڿ��� �����Ѵ�.
	size_t len = strKey.length();
	fwrite(&len, sizeof(size_t), 1, _File);
	fwrite(strKey.c_str(), sizeof(wchar_t), strKey.length(), _File);

	len = strPath.length();
	fwrite(&len, sizeof(size_t), 1, _File);
	fwrite(strPath.c_str(), sizeof(wchar_t), strPath.length(), _File);
}

CAsset* LoadAssetRef(FILE* _File)
{
	// �ҷ������� Asset �� ������ Ȯ��
	int Asset = 0;
	fread(&Asset, sizeof(int), 1, _File);
	if (!Asset)
		return nullptr;

	// �ҷ��� Asset �� ������ �о���δ�.
	ASSET_TYPE type;
	fread(&type, sizeof(ASSET_TYPE), 1, _File);

	// �ҷ��� Asset �� Ű Path �� �˾Ƴ���.
	wstring strKey, strPath;	

	wchar_t buffer[255] = {};

	size_t len = 0;
	fread(&len, sizeof(size_t), 1, _File);
	fread(buffer, sizeof(wchar_t), len, _File);
	strKey = buffer;

	wmemset(buffer, 0, 255);	
		
	fread(&len, sizeof(size_t), 1, _File);
	fread(buffer, sizeof(wchar_t), len, _File);
	strPath = buffer;

	CAsset* pAsset = nullptr;
	switch (type)
	{
	case ASSET_TYPE::TEXTURE:
		pAsset = (CAsset*)CAssetMgr::GetInst()->LoadTexture(strKey, strPath);
		break;
	case ASSET_TYPE::SOUND:
		//pAsset = CAssetMgr::GetInst()->LoadTexture();
		break;
	case ASSET_TYPE::SPRITE:
		pAsset = (CAsset*)CAssetMgr::GetInst()->LoadSprite(strKey, strPath);
		break;
	case ASSET_TYPE::FLIPBOOK:
		pAsset = (CAsset*)CAssetMgr::GetInst()->LoadFlipbook(strKey, strPath);
		break;
	}

	return pAsset;
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


// 0.f ~ 1.f ���� ���� �Լ�
float Saturate(float _Ratio)
{
	if (_Ratio < 0.f)
		_Ratio = 0.f;
	else if (1.f < _Ratio)
		_Ratio = 1.f;	

	return _Ratio;
}


// 0.f ~ 1.f ���� ���� �Լ�
float EaseInOut(float t)
{
	return t * t * (3.0f - 2.0f * t);
}