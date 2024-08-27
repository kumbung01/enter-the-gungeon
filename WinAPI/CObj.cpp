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
	// GetAsynkKeyState 의 반환값이 0x0001 : 함수 호출시점에는 안눌려있고, 그전까지는 눌린적이 있다.
	//						       0x8000 : 함수 호출시점에 눌려있고, 이전에는 안눌렸었다.
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