#include "pch.h"
#include "CMissile.h"

#include "CEngine.h"
#include "CTimeMgr.h"

#include "CCollider.h"

CMissile::CMissile()	
{
	m_Collider = (CCollider*)AddComponent(new CCollider);
	m_Collider->SetScale(Vec2(15.f, 15.f));

	m_Velocity = Vec2(1.f, 1.f);
	m_Velocity.Normalize();
	m_Velocity *= 500.f;
}

CMissile::~CMissile()
{
}


void CMissile::Tick()
{
	Vec2 vPos = GetPos();
	
	vPos += m_Velocity * DT;
	
	SetPos(vPos);

	DrawDebugLine(PEN_TYPE::BLUE, GetPos(), GetPos() + m_Velocity * 0.1f, 0.f);
}

void CMissile::Render()
{
	HDC dc = CEngine::GetInst()->GetSecondDC();

	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	Ellipse(dc, vPos.x - vScale.x / 2.f, vPos.y - vScale.y / 2
		, vPos.x + vScale.x / 2.f, vPos.y + vScale.y / 2.f);
}

