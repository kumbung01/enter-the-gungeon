#include "pch.h"
#include "CGun.h"
#include "CPlayer.h"
#include "CKeyMgr.h"
#include "CCamera.h"
#include "CTimeMgr.h"

#include "CMissile.h"
bool CGun::Trigger()
{
	return KEY_PRESSED(KEY::LBTN);
}

void CGun::CreateBullet()
{
	CMissile* pMissile = new CMissile;
	pMissile->SetPos(GetPos());
	pMissile->SetScale(20.f, 20.f);
	pMissile->SetVelocity(m_fireDir * 900.f);
	CreateObject(pMissile, LAYER_TYPE::PLAYER_OBJECT);

	m_magBullets--;
}

void CGun::CalculateFireDirection()
{
	Vec2 mousePos = CKeyMgr::GetInst()->GetMousePos();
	Vec2 realMousePos = CCamera::GetInst()->GetRealPos(mousePos);
	m_fireDir = realMousePos - m_owner->GetPos();
	m_fireDir.Normalize();
}

/*
* fires the bullet to the mouse cursor.
* parameter: none
* returns: none
*/
void CGun::Fire()
{
	if (m_magBullets == 0)
	{
		if (KEY_TAP(KEY::LBTN))
		{
			Reload(true);
			return;
		}
		else if (KEY_PRESSED(KEY::LBTN))
			return; // just hang
		else
			return; // idle
	}

	if (!KEY_PRESSED(KEY::LBTN))
		return;

	if (m_gunState != GUN_STATE::IDLE)
		return;

	CreateBullet();

	m_gunState = GUN_STATE::FIRING;
}
/*
* reloads the bullets.
* parameter: none,
* returns: none
*/
void CGun::Reload(bool isFired)
{
	if (!KEY_TAP(KEY::R) && !isFired)
		return;

	// if R key is tapped or called from Fire()

	if (m_gunState != GUN_STATE::IDLE)
		return;

	int bulletsToReload = m_maxMagBullets - m_magBullets;
	if (bulletsToReload == 0)
		return;

	// ÃÑ¾Ë ÀåÀü
	if (!m_bIsInfiniteBullet)
	{
		m_bullets -= bulletsToReload;
	}
	m_magBullets += bulletsToReload;
	
	m_fireTime = 0.f; // resets fireTime

	if (m_owner->GetName() == L"Player")
	{
		CPlayer* player = (CPlayer*)m_owner;
		player->Reload(m_reloadDelay);
	}

	m_gunState = GUN_STATE::RELOADING;

	return;
}

void CGun::Tick()
{
	switch (m_gunState)
	{
	case GUN_STATE::IDLE:
		break;
	case GUN_STATE::FIRING:
		m_fireTime += DT;
		if (m_fireTime > m_fireDelay)
		{
			m_fireTime -= m_fireDelay;
			m_gunState = GUN_STATE::IDLE;
		}
		break;
	case GUN_STATE::RELOADING:
		//DrawDebugRect(PEN_TYPE::RED, GetRenderPos(), Vec2(30.f, 30.f), 0.f);
		m_reloadTime += DT;
		if (m_reloadTime > m_reloadDelay)
		{
			m_reloadTime = 0;
			m_gunState = GUN_STATE::IDLE;
		}
		break;
	default:
		break;
	}

	CalculateFireDirection();
	SetPos(m_owner->GetPos() + m_fireDir * 70.f);
}

void CGun::Render()
{
	DrawDebugCircle(PEN_TYPE::BLUE, GetRenderPos(), Vec2(50.f, 50.f), 0);
}

CGun::CGun()
	: m_owner(nullptr)
	, m_bIsInfiniteBullet(true)
	//, m_fireType(SEMIAUTO)
	, m_gunState(GUN_STATE::IDLE)
	, m_fireDelay(0.3f)
	, m_fireTime(0.f)
	, m_reloadDelay(2.f)
	, m_reloadTime(0.f)
	, m_magBullets(6)
	, m_maxMagBullets(6)
	, m_bullets(350)
	, m_maxBullets(350)
	, m_bulletSpread(0.f)
	, m_knockback(0.f)
{
}

CGun::~CGun()
{
}
