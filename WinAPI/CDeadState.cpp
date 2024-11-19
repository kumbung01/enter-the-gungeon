#include "pch.h"
#include "CDeadState.h"
#include "CMonster.h"
#include "CRigidBody.h"
#include "CFlipbookPlayer.h"
#include "CCollider.h"
#include "CTimeMgr.h"

tAnimState CDeadState::ProcessAnimState(Vec2 dir)
{
	int idx = 0;
	dir.Normalize();

	// left or right side
	if (abs(dir.x) >= abs(dir.y) * 2.f)
	{
		idx = dir.x >= 0.f ? BULLET_DEATH_LEFT_SIDE : BULLET_DEATH_RIGHT_SIDE;
	}
	// front or back side
	else if (abs(dir.y) >= abs(dir.x) * 2.f)
	{
		idx = dir.y >= 0.f ? BULLET_DEATH_BACK_SOUTH : BULLET_DEATH_FRONT_NORTH;
	}
	// diagonal
	else
	{
		if (dir.x >= 0.f)
		{
			idx = dir.y >= 0.f ? BULLET_DEATH_LEFT_BACK : BULLET_DEATH_LEFT_FRONT;
		}
		else
		{
			idx = dir.y >= 0.f ? BULLET_DEATH_RIGHT_BACK : BULLET_DEATH_RIGHT_FRONT;
		}
	}
	return { idx, false };
}

void CDeadState::Enter()
{
	CMonster* pMon = (CMonster*)GetOwnerObj();
	Vec2 hitDir = pMon->GetRigidBody()->GetVelocity();
	CCollider* collider = pMon->GetComponent<CCollider>();
	pMon->SetVelocity(hitDir * 0.1f);

	tAnimState animState = ProcessAnimState(hitDir);
	m_flipbookPlayer = pMon->GetComponent<CFlipbookPlayer>();
	if (m_flipbookPlayer)
	{
		m_flipbookPlayer->Play(animState, 10.f, false);
	}
}

void CDeadState::FinalTick()
{
	m_deadAccTime += DT;
	if (m_deadAccTime >= m_deadTime)
	{
		DeleteObject(GetOwnerObj());
	}
}

void CDeadState::Exit()
{
}

CDeadState::CDeadState()
	: m_flipbookPlayer(nullptr)
	, m_deadTime(5.f)
	, m_deadAccTime(0.f)
{
}

CDeadState::~CDeadState()
{
}
