#include "pch.h"
#include "CGuidedMissile.h"


#include "CLevelMgr.h"
#include "CLevel.h"
#include "CCollider.h"

CGuidedMissile::CGuidedMissile()	
	: m_Target(nullptr)
	, m_DetectRange(700.f)
{
	GetCollider()->SetScale(Vec2(50.f, 50.f));
}

CGuidedMissile::~CGuidedMissile()
{
}

void CGuidedMissile::Tick()
{
	// 타겟이 유효하면
	if (IsValid(m_Target))
	{
		//TraceTarget_0();
		TraceTarget_1();
	}

	// 타겟이 유효하지 않으면
	else
	{
		// 다음 대상을 찾는다.
		FindTarget();
	}

	DrawDebugCircle(PEN_TYPE::BLUE, GetPos(), Vec2(m_DetectRange * 2.f, m_DetectRange*2.f), 0.f);

	CMissile::Tick();
}

void CGuidedMissile::FindTarget()
{
	m_Target = nullptr;

	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	const vector<CObj*>& vecMon = pCurLevel->GetObjects(LAYER_TYPE::MONSTER);

	// 미사일 본인과 가장 가까운 대상을 타겟으로 지정한다.
	Vec2 vPos = GetPos(); // 미사일 본인의 위치
	float MinDistance = m_DetectRange;

	for (size_t i = 0; i < vecMon.size(); ++i)
	{
		if (vecMon[i]->IsDead())
			continue;

		Vec2 vMonPos = vecMon[i]->GetPos(); // 몬스터의 위치
		float Dist = (vPos - vMonPos).Length();

		// 최소거리가 갱신된 경우
		if (Dist < MinDistance)
		{
			MinDistance = Dist;
			m_Target = vecMon[i];
		}
	}
}

void CGuidedMissile::TraceTarget_0()
{
	// 타겟을 향해서 이동방향을 설정한다.
	Vec2 vDir = (m_Target->GetPos() - GetPos());
	vDir.Normalize(); // 목적지를 향한 방향정보
	vDir *= GetVelocity().Length();
	SetVelocity(vDir);
}

void CGuidedMissile::TraceTarget_1()
{
	// 타겟을 향해서 힘을 준다.
	// 1. 타겟을 향한 방향을 알아낸다.
	Vec2 vDir = m_Target->GetPos() - GetPos();
	vDir.Normalize();
	AddForce(vDir * 500.f);
}

void CGuidedMissile::TraceTarget_2()
{
	// 타겟을 향한 방향을 회전시킨다.

}

void CGuidedMissile::BeginOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider)
{
	if (_OtherObject->GetName() == L"Monster")
	{
		//DeleteObject(this);
		//DeleteObject(_OtherObject);
	}		
}