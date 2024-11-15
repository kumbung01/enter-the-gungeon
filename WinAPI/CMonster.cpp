#include "pch.h"
#include "CMonster.h"
#include "CMissile.h"

#include "CEngine.h"
#include "CTimeMgr.h"
#include "CCollider.h"

#include "CAssetMgr.h"
#include "CTexture.h"
#include "CFSM.h"

#include "CIdleState.h"
#include "CTraceState.h"

CMonster::CMonster()
	: m_Dir(1)
	, m_Speed(300.f)
	, m_Dist(100.f)
	, m_Collider(nullptr)
	, m_FSM(nullptr)
{
	m_Tex = CAssetMgr::GetInst()->LoadTexture(L"Character", L"Texture\\TX_GlowScene_2.png");

	// Collider 컴포넌트 추가
	m_Collider = (CCollider*)AddComponent(new CCollider);
	m_Collider->SetScale(Vec2(100.f, 100.f));

	// 몬스터 스탯
	m_Info.MaxHP = 25.f;
	m_Info.CurHP = 25.f;
	m_Info.AttRange = 100.f;
	m_Info.DetectRange = 200.f;
	m_Info.Speed = 100.f;
	m_Info.AttDelay = 1.f;

	// FSM 컴포넌트 추가
	m_FSM = (CFSM*)AddComponent(new CFSM);

	// FSM 에 상태 추가
	m_FSM->AddState(L"Idle", new CIdleState);
	m_FSM->AddState(L"Trace", new CTraceState);
}

CMonster::~CMonster()
{
}

void CMonster::Begin()
{
	m_FSM->ChangeState(L"Idle");

	// 레벨이 시작할때 초기 위치값 기록
	m_InitPos = GetPos();
}

void CMonster::Tick()
{
	//return;

	//Vec2 vPos = GetPos();

	//vPos.x += DT * m_Speed * m_Dir;
	//
	//float fDistance = fabs(m_InitPos.x - vPos.x);

	//if (m_Dist < fDistance)
	//{
	//	vPos.x = m_InitPos.x + m_Dir * m_Dist;
	//	m_Dir *= -1;
	//}

	//SetPos(vPos);
}

void CMonster::Render()
{
	HDC dc = CEngine::GetInst()->GetSecondDC();

	Vec2 vPos = GetRenderPos();
	Vec2 vScale = GetScale();

	//BitBlt(dc
	//	, vPos.x - m_Tex->GetWidth() / 2.f
	//	, vPos.y - m_Tex->GetHeight() / 2
	//	, m_Tex->GetWidth()
	//	, m_Tex->GetHeight()
	//	, m_Tex->GetDC()
	//	, 0, 0
	//	, SRCCOPY);

	BLENDFUNCTION blend = {};

	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0;
	blend.SourceConstantAlpha = 127;
	blend.AlphaFormat = AC_SRC_ALPHA;

	AlphaBlend(dc
		, vPos.x - m_Tex->GetWidth() / 2.f
		, vPos.y - m_Tex->GetHeight() / 2.f
		, m_Tex->GetWidth()
		, m_Tex->GetHeight()
		, m_Tex->GetDC()
		, 0, 0
		, m_Tex->GetWidth()
		, m_Tex->GetHeight()
		, blend);

	/*Ellipse(dc, vPos.x - vScale.x / 2.f, vPos.y - vScale.y / 2
		, vPos.x + vScale.x / 2.f, vPos.y + vScale.y / 2.f );*/
}



void CMonster::BeginOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider)
{
	if (_OtherObject->GetLayerType() == LAYER_TYPE::PLAYER_OBJECT)
	{
		auto pMissile = (CMissile*)_OtherObject;
		m_Info.CurHP -= pMissile->GetDamage();
		if (m_Info.CurHP <= 0)
			DeleteObject(this);
	}
}