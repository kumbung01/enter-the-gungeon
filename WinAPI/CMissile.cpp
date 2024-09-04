#include "pch.h"
#include "CMissile.h"

#include "CEngine.h"
#include "CTimeMgr.h"

CMissile::CMissile()
	: m_Speed(500.f)
	, m_Angle(PI / 4.f)
{
}

CMissile::~CMissile()
{
}




void CMissile::Tick()
{
	Vec2 vPos = GetPos();

	//vPos.y -= DT * m_Speed;
	vPos.x += cosf(m_Angle) * m_Speed * DT;
	vPos.y -= sinf(m_Angle) * m_Speed * DT;
	

	Vec2 vDir = Vec2(cosf(m_Angle) * m_Speed, -sinf(m_Angle) * m_Speed);
	DrawDebugLine(PEN_TYPE::BLUE, GetPos(), GetPos() + vDir, 0.f);

	SetPos(vPos);
}

void CMissile::Render()
{
	HDC dc = CEngine::GetInst()->GetSecondDC();

	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	Ellipse(dc, vPos.x - vScale.x / 2.f, vPos.y - vScale.y / 2
		, vPos.x + vScale.x / 2.f, vPos.y + vScale.y / 2.f);
}

