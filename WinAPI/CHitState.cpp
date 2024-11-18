#include "pch.h"
#include "CHitState.h"
#include "CLevelMgr.h"
#include "CFlipbookPlayer.h"
#include "CMonster.h"
#include "CPlayer.h"
#include "CRigidBody.h"
#include "CGun.h"

tAnimState CHitState::ProcessAnimState(Vec2 dir)
{
	int animIdx;

	if (dir.y < 0)
	{
		animIdx = dir.x < 0 ? BULLET_HIT_BACK_RIGHT : BULLET_HIT_BACK_LEFT;
	}
	else
	{
		animIdx = dir.x < 0 ? BULLET_HIT_RIGHT : BULLET_HIT_LEFT;
	}
	
	return { animIdx, false };
}

void CHitState::Enter()
{
	CMonster* pMon = (CMonster*)GetOwnerObj();
	pMon->GetGun()->SetVisible(false);

	m_flipbookPlayer = pMon->GetComponent<CFlipbookPlayer>();
	Vec2 hitDir = pMon->GetRigidBody()->GetVelocity();
	hitDir.Normalize();

	tAnimState animState = ProcessAnimState(hitDir);
	m_flipbookPlayer->Play(animState, 7.f, false);
}

void CHitState::FinalTick()
{
	if (m_flipbookPlayer->IsFinish())
	{
		GetFSM()->ChangeState(L"Trace");
	}
}

void CHitState::Exit()
{
}

CHitState::CHitState()
	: m_flipbookPlayer(nullptr)
{
}

CHitState::~CHitState()
{
}
