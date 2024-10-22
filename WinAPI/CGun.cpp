#include "pch.h"
#include "CGun.h"
#include "CKeyMgr.h"
#include "CCamera.h"
#include "CTimeMgr.h"

#include "CMissile.h"
/*
* fires the bullet to the mouse cursor.
* parameter: none
* returns: fire result. true: fired, false: needs reload
*/
FIRE_RESULT CGun::Fire()
{
	m_fireTime += DT;

	if (!KEY_TAP(KEY::LBTN))
		return WAIT;

	if (m_fireTime <= m_fireDelay)
		return WAIT;

	if (m_magBullets == 0)
		return RELOAD;

	m_fireTime -= m_fireDelay;

	Vec2 mousePos = CKeyMgr::GetInst()->GetMousePos();
	Vec2 realMousePos = CCamera::GetInst()->GetRealPos(mousePos);
	Vec2 fireDir = realMousePos - m_owner->GetPos();
	fireDir.Normalize();

	CMissile* pMissile = new CMissile;
	pMissile->SetPos(GetPos());
	pMissile->SetScale(20.f, 20.f);
	pMissile->SetVelocity(fireDir * 500.f);
	CreateObject(pMissile, LAYER_TYPE::PLAYER_OBJECT);

	return FIRED;
}
/*
* reloads the bullets.
* parameter: none,
* returns: reload time. if negative, then failed to reload(not enough bullets)
*/
float CGun::Reload()
{
	return 0;
}

void CGun::Tick()
{
	SetPos(m_owner->GetPos());
}

void CGun::Render()
{
	DrawDebugCircle(PEN_TYPE::BLUE, GetRenderPos(), Vec2(50.f, 50.f), 0);
}

CGun::CGun()
	: m_owner(nullptr)
	//, m_fireType(SEMIAUTO)
	, m_fireDelay(0.01f)
	, m_fireTime(0.01f)
	, m_reloadDelay(3.f)
	, m_reloadTime(0.f)
	, m_magBullets(6)
	, m_maxMagBullets(6)
	, m_bullets(-1)
	, m_maxBullets(-1)
	, m_bulletSpread(0.f)
	, m_knockback(0.f)
{
}

CGun::~CGun()
{
}
