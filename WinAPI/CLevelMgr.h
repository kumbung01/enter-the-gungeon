#pragma once

class CLevel;

class CLevelMgr
{
	SINGLE(CLevelMgr)
private:
	CLevel*		m_arrLevel[(UINT)LEVEL_TYPE::END];	// ��� ������
	CLevel*		m_CurLevel;							// ���� ������� ����

public:
	CLevel* GetCurrentLevel() { return m_CurLevel; }


public:
	void Init();
	void Progress();

public:
	void Render();
};

