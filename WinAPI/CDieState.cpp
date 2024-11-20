#include "pch.h"
#include "CDieState.h"
#include "CMonster.h"
#include "CRigidBody.h"
#include "CFlipbookPlayer.h"
#include "CCollider.h"

tAnimState CDieState::ProcessAnimState(Vec2 dir)
{
	int idx = 0;

	if (dir.x > 0.f)
		idx = dir.y > 0.f ? BULLET_DIE_LEFT : BULLET_DIE_LEFT_BACK;
	else
		idx = dir.y > 0.f ? BULLET_DIE_RIGHT : BULLET_DIE_RIGHT_BACK;


	return tAnimState{ idx, false };
}

void CDieState::Enter()
{
	CMonster* pMon = (CMonster*)GetOwnerObj();
	Vec2 hitDir = pMon->GetRigidBody()->GetVelocity();
	CCollider* collider = pMon->GetComponent<CCollider>();
	pMon->SetVelocity(hitDir * 7.f);

	tAnimState animState = ProcessAnimState(hitDir);
	m_flipbookPlayer = pMon->GetComponent<CFlipbookPlayer>();
	if (m_flipbookPlayer)
	{
		m_flipbookPlayer->Play(animState, 10.f, false);
	}

	DeleteCObject((CObj*)pMon->GetGun());
}

void CDieState::FinalTick()
{
	if (m_flipbookPlayer->IsFinish())
	{
		GetFSM()->ChangeState(L"Dead");
	}
}

void CDieState::Exit()
{
}

CDieState::CDieState()
	:m_flipbookPlayer(nullptr)
{
}

CDieState::~CDieState()
{
}
