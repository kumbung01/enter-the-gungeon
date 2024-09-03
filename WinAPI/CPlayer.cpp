#include "pch.h"
#include "CPlayer.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CTaskMgr.h"

#include "CMissile.h"
#include "CLevelMgr.h"
#include "CLevel.h"

#include "CCollider.h"

CPlayer::CPlayer()
	: m_Speed(200.f)
	, m_AttSpeed(10.f)
	, m_AccTime(0.f)
{
	// Collider 컴포넌트 추가
	m_HitBox = new CCollider;
	m_HitBox->SetName(L"HitBox_01");
	m_HitBox->SetScale(Vec2(60.f, 60.f));
	AddComponent(m_HitBox);

	// RTTI(RunTime Type Identification(Infomation) ) -> C++ 의 경우 dynamic_cast 가 있다.

	//CCollider* pC = (CCollider*)GetComponent(L"HitBox_01");
	//CCollider* pC = (CCollider*)GetComponent(COMPONENT_TYPE::COLLIDER);
	//CCollider* pC = GetComponent<CCollider>();

}

CPlayer::~CPlayer()
{
	
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

	
	// 미사일 발사
	if (KEY_PRESSED(SPACE))
	{
		// 시간체크
		m_AccTime += DT;

		if (1.f / m_AttSpeed <= m_AccTime)
		{
			m_AccTime -= 1.f / m_AttSpeed;

			// 미사일 생성
			for (int i = 0; i < 3; ++i)
			{
				CMissile* pMissile = new CMissile;
				pMissile->SetPos(vPos + Vec2(-20.f + i * 20.f, -GetScale().y / 2.f));
				pMissile->SetScale(20.f, 20.f);				
				CreateObject(pMissile, LAYER_TYPE::PLAYER_OBJECT);
			}
		}
	}

	else if (KEY_RELEASED(SPACE))
	{
		m_AccTime = 1.f / m_AttSpeed;
	}


	SetPos(vPos);
}

