#include "pch.h"
#include "CGun.h"
#include "CPlayer.h"
#include "CKeyMgr.h"
#include "CCamera.h"
#include "CAssetMgr.h"
#include "CTimeMgr.h"
#include "CEngine.h"
#include "CSprite.h"
#include "CMissile.h"
#include "CFlipbookPlayer.h"

bool CGun::IsTriggered()
{
	return KEY_PRESSED(KEY::LBTN);
}

void CGun::CreateBullet()
{
	CMissile* pMissile = new CMissile;
	pMissile->SetPos(m_muzzle);
	pMissile->SetScale(20.f, 20.f);
	pMissile->SetVelocity(m_gunDir * 700.f);
	CreateObject(pMissile, LAYER_TYPE::PLAYER_OBJECT);
}

Vec2 CGun::CalculateFireDirection()
{
	Vec2 realMousePos = CCamera::GetInst()->GetRealPos(CKeyMgr::GetInst()->GetMousePos());
	Vec2 fireDirection = realMousePos - m_owner->GetPos();
	fireDirection.Normalize();

	return fireDirection;
}

void CGun::CreateFlipbook()
{
	m_flipbookPlayer = (CFlipbookPlayer*)AddComponent(new CFlipbookPlayer);
	m_flipbookPlayer->SetMagnification(m_magnification);
	//m_flipbookPlayer->SetOffset(Vec2(10.f, 0.f));
}

/*
* fires the bullet to the mouse cursor.
* parameter: none
* returns: none
*/
GUN_STATE CGun::Fire()
{
	if (m_gunState == GUN_STATE::EMPTY)
	{
		if (KEY_TAP(KEY::LBTN))
		{
			return Reload(true);
		}
		else
			return m_gunState;
	}

	if (!IsTriggered())
		return m_gunState;

	if (m_gunState != GUN_STATE::IDLE)
		return m_gunState;

	m_gunState = GUN_STATE::FIRING;

	CreateBullet();
	m_magBullets--;

	if (nullptr != m_flipbookPlayer)
	{
		tAnimState state{ GUN_FIRE, false };
		m_flipbookPlayer->Play(state, 15.f, true);
	}

	CCamera::GetInst()->Oscillation(0.1f, 10.f, 100.f);

	return m_gunState;
}
/*
* reloads the bullets.
* parameter: none,
* returns: none
*/
GUN_STATE CGun::Reload(bool isFired)
{
	if (!KEY_TAP(KEY::R) && !isFired)
		return m_gunState;

	// if R key is tapped or called from Fire()
	 
	if (m_gunState == GUN_STATE::RELOAD ||
		m_gunState == GUN_STATE::RELOADING)
		return m_gunState;

	int bulletsToReload = m_maxMagBullets - m_magBullets;
	if (bulletsToReload == 0)
		return m_gunState;

	m_gunState = GUN_STATE::RELOAD;

	// ÃÑ¾Ë ÀåÀü
	if (!m_bIsInfiniteBullet)
	{
		m_bullets -= bulletsToReload;
	}
	m_magBullets += bulletsToReload;
	
	m_fireTime = 0.f; // resets fireTime

	if (nullptr != m_flipbookPlayer)
	{
		tAnimState state{ GUN_RELOAD,false };
		m_flipbookPlayer->Play(state, 10.f, true);
	}

	return m_gunState;
}

void CGun::Begin()
{
	tAnimState state;
	//state.angle = ToDegree(m_gunDir);
	state.mirror = false;
	state.idx = GUN_IDLE;

	if (nullptr != m_flipbookPlayer)
		m_flipbookPlayer->Play(state, 5.f, true);
}

void CGun::Tick()
{
	switch (m_gunState)
	{
	case GUN_STATE::EMPTY:
	case GUN_STATE::IDLE:
		if (nullptr != m_flipbookPlayer && !m_flipbookPlayer->IsFlipbookMatch(GUN_IDLE))
		{
			tAnimState state{ GUN_IDLE, false };
			m_flipbookPlayer->Play(state, 5.f, true);
		}
		break;
	case GUN_STATE::FIRING:
		m_fireTime += DT;
		if (m_fireTime > m_fireDelay)
		{
			m_fireTime -= m_fireDelay;
			if (m_magBullets == 0)
				m_gunState = GUN_STATE::EMPTY;
			else
				m_gunState = GUN_STATE::IDLE;
		}
		break;
	case GUN_STATE::RELOAD:
		m_gunState = GUN_STATE::RELOADING;
		break;
	case GUN_STATE::RELOADING:
		m_reloadTime += DT;
		if (m_reloadTime > m_reloadDelay)
		{
			m_reloadTime = 0;
			m_gunState = GUN_STATE::IDLE;
		}
		break;
	case GUN_STATE::GROUND:
		// do not update position
		return;
	default:
		break;
	}

	{
		m_gunDir = CalculateFireDirection();

		float offset = 20.f;
		float angle = fabs(ToDegree(m_gunDir));
		//wprintf(L"%.3f ", angle);
		if (m_isRightHand && (100.f <= angle && angle <= 180.f))
		{
			m_isRightHand = false;
		}
		else if (!m_isRightHand && (0.f <= angle && angle <= 80.f))
		{
			m_isRightHand = true;
		}

		m_hand = m_owner->GetPos() + Vec2{ m_isRightHand ? offset : -offset, 20.f };
		Vec2 realPos = m_hand + Vec2{ m_isRightHand ? 10.f : -10.f, -5.f };

		SetPos(realPos);
		m_muzzle = GetPos() + m_gunDir * 9.f;
	}
}

void CGun::Render()
{
	DrawDebugCircle(PEN_TYPE::BLUE, GetRenderPos(), Vec2(50.f, 50.f), 0);

	if (false == m_visible)
		return;

	if (nullptr != m_flipbookPlayer) {
		float angle = ToDegree(m_gunDir);
		if (!m_isRightHand) {
			float sign = angle > 0.f ? 1.f : -1.f;
			angle = (180.f - abs(angle)) * sign;
		}

		// to draw before PC when up
		SetRenderOffset(m_gunDir.y <= 0 ? -20.1f : 0.f);

		m_flipbookPlayer->SetAngle(angle);
		m_flipbookPlayer->SetMirror(!m_isRightHand);
		m_flipbookPlayer->Render();

		if (m_handSprite != nullptr)
		{
			Gdiplus::Graphics* graphics = CEngine::GetInst()->GetBackGraphics();
			Vec2 vPos = CCamera::GetInst()->GetRenderPos(m_hand);
			Vec2 center = m_handSprite->GetSlice() / 2.f;

			Matrix mat;
			mat.Translate(vPos.x, vPos.y);
			mat.Scale(3.f, 3.f);
			mat.Translate(-center.x, -center.y);
			graphics->SetTransform(&mat);

			auto res = graphics->DrawImage(m_handSprite->GetAtlas()->GetImage(),
				0.f, 0.f,
				m_handSprite->GetLeftTop().x, m_handSprite->GetLeftTop().y,
				m_handSprite->GetSlice().x, m_handSprite->GetSlice().y, UnitPixel);

			graphics->ResetTransform();
		}
	}

}

CGun::CGun()
	: m_owner(nullptr)
	, m_flipbookPlayer(nullptr)
	, m_handSprite(nullptr)
	, m_bIsInfiniteBullet(true)
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
	, m_magnification(2.f)
	, m_isRightHand(false)
	, m_visible(true)
{
	
}

CGun::~CGun()
{
}
