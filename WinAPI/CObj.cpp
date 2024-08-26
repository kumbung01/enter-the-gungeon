#include "pch.h"
#include "CObj.h"

#include "CEngine.h"

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
	m_Pos.x += 0.0001f;
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