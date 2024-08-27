#include "pch.h"
#include "CObj.h"

#include "CEngine.h"
#include "CTimeMgr.h"

CObj::CObj()
	: m_Pos{}
	, m_Scale{}
{	
}

CObj::~CObj()
{
}

void CObj::Tick()
{
	// GetAsynkKeyState �� ��ȯ���� 0x0001 : �Լ� ȣ��������� �ȴ����ְ�, ���������� �������� �ִ�.
	//						       0x8000 : �Լ� ȣ������� �����ְ�, �������� �ȴ��Ⱦ���.
	if (GetAsyncKeyState(VK_RIGHT) & 0x8001)
	{
		float Speed = 200.f;
		m_Pos.x += Speed * DT;
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8001)
	{

	}
}

void CObj::Render()
{
	HDC dc = CEngine::GetInst()->GetMainDC();

	Rectangle(dc
		, m_Pos.x - m_Scale.x / 2
		, m_Pos.y - m_Scale.y / 2
		, m_Pos.x + m_Scale.x / 2
		, m_Pos.y + m_Scale.y / 2);
}