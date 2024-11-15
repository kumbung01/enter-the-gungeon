#include "pch.h"
#include "CTraceState.h"

#include "CLevelMgr.h"
#include "CMonster.h"
#include "CTimeMgr.h"
#include "CMonsterMissile.h"
#include "CFlipbookPlayer.h"
#include "CGun.h"

CTraceState::CTraceState()
	: m_TargetObject(nullptr)
	, m_animState({BULLET_IDLE_RIGHT, false})
{
}

CTraceState::~CTraceState()
{
}

// idle, run, cover
tAnimState ProcessAnimState(Vec2 dir, MONSTER_STATE state)
{
	tAnimState animState = { BULLET_IDLE_RIGHT, false };

	if (dir.y < 0.f)
	{
		if (state == MONSTER_STATE::RUN)
		{
			if (dir.x >= 0.f)
				animState.idx = BULLET_RUN_RIGHT_BACK;
			else
				animState.idx = BULLET_RUN_LEFT_BACK;
		}
		else
		{
			animState.idx = BULLET_IDLE_BACK;
		}

	}
	else
	{
		if (dir.x >= 0.f)
		{
			switch (state)
			{
			case MONSTER_STATE::RUN:
				animState.idx = BULLET_RUN_RIGHT;
				break;
			case MONSTER_STATE::IDLE:
			default:
				animState.idx = BULLET_IDLE_RIGHT;
				break;
			}
		}
		else
		{
			switch (state)
			{
			case MONSTER_STATE::RUN:
				animState.idx = BULLET_RUN_LEFT;
				break;
			case MONSTER_STATE::IDLE:
			default:
				animState.idx = BULLET_IDLE_LEFT;
				break;
			}
		}
	}

	return animState;
}

void CTraceState::Enter()
{
	// Level ���� ������� �÷��̾ ã�´�.
	if (nullptr == m_TargetObject)
	{
		m_TargetObject = CLevelMgr::GetInst()->FindObjectByName(LAYER_TYPE::PLAYER, L"Player");
	}
	CMonster* pMon = dynamic_cast<CMonster*>(GetOwnerObj());
	pMon->GetGun()->SetVisible(true);
}

void CTraceState::FinalTick()
{
	// ������ ���������� �����´�.	
	CMonster* pMon = dynamic_cast<CMonster*>(GetOwnerObj());
	assert(pMon);
	tMonInfo& info = pMon->GetMonInfo();

	// ������ �̵��ӿ� �°� �÷��̾ ���ؼ� �̵��Ѵ�.
	// �̵� ���� ���
	Vec2 vMoveDir = m_TargetObject->GetPos() - pMon->GetPos();
	float dist = vMoveDir.Length();
	vMoveDir.Normalize();

	// �ش� ��������, �ӷ¿� �°� �������Ӹ��� �̵�
	if (dist >= info.AttRange)
	{
		Vec2 vPos = pMon->GetPos() + vMoveDir * info.Speed * DT;
		pMon->SetPos(vPos);
	}

	MONSTER_STATE state = (dist >= info.AttRange) ? MONSTER_STATE::RUN : MONSTER_STATE::IDLE;
	tAnimState animState = ProcessAnimState(vMoveDir, state);
	if (m_animState != animState)
	{
		m_animState = animState;
		pMon->GetComponent<CFlipbookPlayer>()->Play(animState, 10.f, true);
	}

	// �� �߻�
	pMon->GetGun()->Fire();
	

	// ���࿡ �����߿� �ǰ��� ���ϸ�, �ǰݻ��·� ��ȯ��.

		
	// �������� �ð�ȭ
	DrawDebugCircle(PEN_TYPE::RED, pMon->GetRenderPos(), Vec2(info.AttRange * 2.f, info.AttRange * 2.f), 0.f);
	DrawDebugCircle(PEN_TYPE::BLUE, pMon->GetRenderPos(), Vec2(info.DetectRange * 2.f, info.DetectRange * 2.f), 0.f);
}

void CTraceState::Exit()
{
}