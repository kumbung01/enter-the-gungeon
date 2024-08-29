#include "pch.h"
#include "CMonster.h"

#include "CEngine.h"
#include "CTimeMgr.h"


CMonster::CMonster()
	: m_Dir(1)
	, m_Speed(300.f)
	, m_Dist(100.f)
{
}

CMonster::~CMonster()
{
}

void CMonster::Begin()
{
	// 레벨이 시작할때 초기 위치값 기록
	m_InitPos = GetPos();
}

void CMonster::Tick()
{
	Vec2 vPos = GetPos();

	vPos.x += DT * m_Speed * m_Dir;
	
	float fDistance = fabs(m_InitPos.x - vPos.x);

	if (m_Dist < fDistance)
	{
		vPos.x = m_InitPos.x + m_Dir * m_Dist;
		m_Dir *= -1;
	}

	SetPos(vPos);
}

void CMonster::Render()
{
	HDC dc = CEngine::GetInst()->GetSecondDC();

	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	Ellipse(dc, vPos.x - vScale.x / 2.f, vPos.y - vScale.y / 2
		, vPos.x + vScale.x / 2.f, vPos.y + vScale.y / 2.f );
}
