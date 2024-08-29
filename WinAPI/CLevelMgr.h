#pragma once

class CLevel;

class CLevelMgr
{
	SINGLE(CLevelMgr)
private:
	CLevel*		m_arrLevel[(UINT)LEVEL_TYPE::END];	// 모든 레벨들
	CLevel*		m_CurLevel;							// 현재 재생중인 레벨

public:
	CLevel* GetCurrentLevel() { return m_CurLevel; }


public:
	void Init();
	void Progress();

public:
	void Render();
};

