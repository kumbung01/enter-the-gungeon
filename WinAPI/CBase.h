#pragma once

class CBase
{
private:
	static UINT g_NextID;

private:	
	wstring		m_Name;
	const UINT	m_ID;

public:
	// inline Ű���� or ����� �Լ��� ������ ��� ==> inline �Լ�
	// �ڵ尡 ����, ��� �󵵰� ���� ��
	// Get, Set �� �Լ���
	void SetName(const wstring& _Name) { m_Name = _Name; }
	const wstring& GetName() { return m_Name; }
	UINT GetID() { return m_ID; }
	void operator =(const CBase& _Origin) { m_Name = _Origin.m_Name; }

public:
	CBase();
	CBase(const CBase& _Origin);
	virtual ~CBase();
};

