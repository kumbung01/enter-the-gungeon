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
	float Speed = 200.f;
	m_Pos.x += Speed * DT;
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