#include "pch.h"
#include "CTraceState.h"

#include "CLevelMgr.h"
#include "CMonster.h"
#include "CTimeMgr.h"
#include "CMonsterMissile.h"
#include "CGun.h"

CTraceState::CTraceState()
	: m_TargetObject(nullptr)
{
}

CTraceState::~CTraceState()
{
}

void CTraceState::Enter()
{
	// Level 에서 추적대상 플레이어를 찾는다.
	if (nullptr == m_TargetObject)
	{
		m_TargetObject = CLevelMgr::GetInst()->FindObjectByName(LAYER_TYPE::PLAYER, L"Player");
	}
	CMonster* pMon = dynamic_cast<CMonster*>(GetOwnerObj());
	pMon->GetGun()->SetVisible(true);
}

void CTraceState::FinalTick()
{
	// 몬스터의 스탯정보를 가져온다.	
	CMonster* pMon = dynamic_cast<CMonster*>(GetOwnerObj());
	assert(pMon);
	tMonInfo& info = pMon->GetMonInfo();

	// 몬스터의 이동속에 맞게 플레이어를 향해서 이동한다.
	// 이동 방향 계산
	Vec2 vMoveDir = m_TargetObject->GetPos() - pMon->GetPos();
	float dist = vMoveDir.Length();
	vMoveDir.Normalize();

	// 해당 방향으로, 속력에 맞게 매프레임마다 이동
	if (dist >= info.AttRange)
	{
		Vec2 vPos = pMon->GetPos() + vMoveDir * info.Speed * DT;
		pMon->SetPos(vPos);
	}

	// 총 발사
	pMon->GetGun()->Fire();
	

	// 만약에 추적중에 피격을 당하면, 피격상태로 전환다.

		
	// 인지범위 시각화
	DrawDebugCircle(PEN_TYPE::RED, pMon->GetRenderPos(), Vec2(info.AttRange * 2.f, info.AttRange * 2.f), 0.f);
	DrawDebugCircle(PEN_TYPE::BLUE, pMon->GetRenderPos(), Vec2(info.DetectRange * 2.f, info.DetectRange * 2.f), 0.f);
}

void CTraceState::Exit()
{
}