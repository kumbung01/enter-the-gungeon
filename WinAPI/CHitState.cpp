#include "pch.h"
#include "CHitState.h"
#include "CLevelMgr.h"
#include "CFlipbookPlayer.h"
#include "CMonster.h"
#include "CPlayer.h"
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
	if (m_targetObject == nullptr)
	{
		m_targetObject = CLevelMgr::GetInst()->FindObjectByName(LAYER_TYPE::PLAYER, L"Player");
	}
	CMonster* pMon = (CMonster*)GetOwnerObj();
	pMon->GetGun()->SetVisible(false);

	m_flipbookPlayer = pMon->GetComponent<CFlipbookPlayer>();
	m_hitDir = pMon->GetPos() - m_targetObject->GetPos();
	m_hitDir.Normalize();

	tAnimState animState = ProcessAnimState(m_hitDir);
	m_flipbookPlayer->Play(animState, 7.f, false);
}

void CHitState::FinalTick()
{
	if (m_flipbookPlayer->IsFinish())
	{
		GetFSM()->ChangeState(L"Trace");
	}
	else
	{
		GetOwnerObj()->SetPos(GetOwnerObj()->GetPos() + m_hitDir * 0.33f);
	}
}

void CHitState::Exit()
{
}

CHitState::CHitState()
	: m_flipbookPlayer(nullptr)
	, m_hitDir(0.f, 0.f)
	, m_targetObject(nullptr)
{
}

CHitState::~CHitState()
{
}
