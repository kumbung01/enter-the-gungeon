#include "pch.h"
#include "CObj.h"

#include "CEngine.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"

CObj::CObj()
	: m_Pos{}
	, m_Scale{}
{	
}

CObj::~CObj()
{
}

void CObj::Begin()
{

}

void CObj::Tick()
{
	if (KEY_PRESSED(RIGHT))
	{
		m_Pos.x += 100 * DT;
	}
}

void CObj::FinalTick()
{
}

void CObj::Render()
{
	HDC dc = CEngine::GetInst()->GetSecondDC();

	Rectangle(dc
		, m_Pos.x - m_Scale.x / 2
		, m_Pos.y - m_Scale.y / 2
		, m_Pos.x + m_Scale.x / 2
		, m_Pos.y + m_Scale.y / 2);
}