#include "pch.h"
#include "CPlayer.h"

#include "CAssetMgr.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CTaskMgr.h"
#include "CDbgRender.h"

#include "CMissile.h"
#include "CLevelMgr.h"
#include "CLevel.h"

#include "CMonster.h"
#include "CCollider.h"
#include "CGuidedMissile.h"

#include "CEngine.h"
#include "CTexture.h"

CPlayer::CPlayer()
	: m_Speed(200.f)
	, m_AttSpeed(10.f)
	, m_AccTime(0.f)
	, m_Texture(nullptr)
{
	// Collider 컴포넌트 추가
	m_HitBox = new CCollider;
	m_HitBox->SetName(L"HitBox_01");
	m_HitBox->SetScale(Vec2(20.f, 40.f));
	m_HitBox->SetOffset(Vec2(0.f, 20.f));

	AddComponent(m_HitBox);

	// 텍스쳐 로딩하기
	m_Texture = CAssetMgr::GetInst()->LoadTexture(L"PlayerTexture", L"Texture\\Fighter.bmp");
}

CPlayer::~CPlayer()
{
	DELETE(m_Texture);
}

void CPlayer::Begin()
{
	m_AccTime = 1.f / m_AttSpeed;
}

void CPlayer::Tick()
{
	Vec2 vPos = GetPos();
	
	if (KEY_PRESSED(LEFT))
		vPos.x -= DT * m_Speed;
	if (KEY_PRESSED(RIGHT))
		vPos.x += DT * m_Speed;
	if (KEY_PRESSED(UP))
		vPos.y -= DT * m_Speed;
	if (KEY_PRESSED(DOWN))
		vPos.y += DT * m_Speed;

	if (KEY_TAP(SPACE))
	{
		//DrawDebugRect(PEN_TYPE::GREEN, GetPos(), GetScale() * 2.f, 3.f);
		//DrawDebugCircle(PEN_TYPE::GREEN, GetPos(), GetScale() * 2.f, 3.f);
		//DrawDebugLine(PEN_TYPE::GREEN, GetPos(), GetPos() + GetScale(), 3.f);
	}

	// 미사일 발사
	if (KEY_PRESSED(SPACE))
	{
		// 시간체크
		m_AccTime += DT;

		if (1.f / m_AttSpeed <= m_AccTime)
		{
			m_AccTime -= 1.f / m_AttSpeed;

			// 미사일 생성			
			CMissile* pMissile = new CGuidedMissile;
			pMissile->SetPos(vPos + Vec2(0.f, -GetScale().y / 2.f));
			pMissile->SetScale(20.f, 20.f);
			pMissile->SetVelocity(Vec2(cosf(PI / 2.f), -sinf(PI / 2.f)) * 400.f);
			CreateObject(pMissile, LAYER_TYPE::PLAYER_OBJECT);			
		}
	}

	else if (KEY_RELEASED(SPACE))
	{
		m_AccTime = 1.f / m_AttSpeed;
	}

	SetPos(vPos);
}

void CPlayer::Render()
{
	Vec2 Pos = GetPos();		
	UINT Width = m_Texture->GetWidth();
	UINT Height = m_Texture->GetHeight();
	HDC hBackDC = CEngine::GetInst()->GetSecondDC();

	TransparentBlt(hBackDC
		, Pos.x - (Width / 2)
		, Pos.y - (Height / 2)
		, Width, Height
		, m_Texture->GetDC()
		, 0, 0, Width, Height, RGB(255, 0, 255));
}

void CPlayer::BeginOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider)
{
	if (_OtherObject->GetName() == L"Monster")
	{
		DeleteObject(_OtherObject);
	}
}

void CPlayer::Overlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider)
{
}

void CPlayer::EndOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider)
{
}

