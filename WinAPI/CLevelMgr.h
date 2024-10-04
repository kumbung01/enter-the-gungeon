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

private:
	void ChangeLevel(LEVEL_TYPE _NextLevel);

public:
	void Init();
	void Progress();

public:
	void Render();

	friend class CTaskMgr;
};

