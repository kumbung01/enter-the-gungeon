#include "pch.h"
#include "CSurpriseState.h"
#include "CFlipbookPlayer.h"
#include "CMonster.h"
#include "CLevelMgr.h"

tAnimState CSurpriseState::ProcessAnimState(Vec2 dir)
{
	if (dir.x < 0.f)
	{
		return { BULLET_SURPRISE_LEFT, false };
	}
	else
		return { BULLET_SURPRISE_RIGHT, false };
}

void CSurpriseState::Enter()
{
	// 소유자(몬스터) 의 FlipbookPlayer 를 이용해서 특정 플립북(애니메이션) 을 재생시킨다.
	CMonster* pMon = (CMonster*)GetOwnerObj();
	CFlipbookPlayer* pFP = pMon->GetComponent<CFlipbookPlayer>();
	if (pFP)
	{
		Vec2 playerPos = CLevelMgr::GetInst()->FindObjectByName(LAYER_TYPE::PLAYER, L"Player")->GetPos();
		Vec2 dir = playerPos - pMon->GetPos();
		pFP->Play(ProcessAnimState(dir), 5.f, false);
	}
}

void CSurpriseState::FinalTick()
{
	CFlipbookPlayer* pFP = (CFlipbookPlayer*)GetOwnerObj()->GetComponent<CFlipbookPlayer>();
	if (pFP->IsFinish())
	{
		GetFSM()->ChangeState(L"Trace");
	}
}

void CSurpriseState::Exit()
{
}

CSurpriseState::CSurpriseState()
{
}

CSurpriseState::~CSurpriseState()
{
}
