#include "pch.h"
#include "CMissile.h"

#include "CEngine.h"
#include "CTimeMgr.h"
#include "CSprite.h"
#include "CAssetMgr.h"

#include "CCollider.h"

CMissile::CMissile()
	: m_Mass(1.f)
	, m_VelocityScale(1.f)
	, m_damage(5.f)
	, m_sprite(nullptr)
	, m_knockBack(100.f)
	, m_magnification(3.f)
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

void CMissile::CreateSprite()
{
	m_sprite = CAssetMgr::GetInst()->LoadSprite(L"bullet_variant_001", L"Sprite\\Projectile\\bullet_variant\\bullet_variant_001.sprite");
}

void CMissile::Begin()
{
	CreateSprite();
}

void CMissile::Tick()
{
	// 누적된 힘을 확인한다.
	// 누적된 힘에의해서 생겨난 가속도를 계산한다.
	// F = M * A
	Vec2 vAccel = m_Force / m_Mass;

	// 가속도에 따른 속도의 변화 적용
	m_Velocity += vAccel * DT;


	// 속도에 따른 이동
	Vec2 vPos = GetPos();	
	vPos += m_Velocity * m_VelocityScale * DT;
	SetPos(vPos);

	DrawDebugLine(PEN_TYPE::BLUE, GetRenderPos(), GetRenderPos() + m_Velocity * 0.1f, 0.f);

	// 적용중인 힘 리셋
	m_Force = Vec2(0.f, 0.f);
}

void CMissile::Render()
{
	HDC bufDC = CEngine::GetInst()->GetBufferDC();
	HDC backDC = CEngine::GetInst()->GetSecondDC();
	CTexture* tex = m_sprite->GetAtlas();
	Vec2 slice = m_sprite->GetSlice();
	Vec2 leftTop = m_sprite->GetLeftTop();
	Vec2 vPos = GetRenderPos() - slice / 2.f * m_magnification;

	StretchBlt(bufDC,
		0, 0,
		slice.x * m_magnification,
		slice.x * m_magnification,
		tex->GetDC(),
		leftTop.x,
		leftTop.y,
		slice.x,
		slice.y,
		SRCCOPY);

	TransparentBlt(backDC,
		vPos.x,
		vPos.y,
		slice.x * m_magnification,
		slice.y * m_magnification,
		bufDC,
		0, 0,
		slice.x * m_magnification,
		slice.y * m_magnification,
		Color::Magenta);
}

void CMissile::BeginOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider)
{
	DeleteObject(this);
}

