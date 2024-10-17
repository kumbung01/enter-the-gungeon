#include "pch.h"
#include "CIdleState.h"


#include "CLevelMgr.h"
#include "CObj.h"
#include "CFlipbookPlayer.h"

#include "CMonster.h"


CIdleState::CIdleState()
	: m_TargetObject(nullptr)
{
}

CIdleState::~CIdleState()
{
}

void CIdleState::Enter()
{	
	// ������(����) �� FlipbookPlayer �� �̿��ؼ� Ư�� �ø���(�ִϸ��̼�) �� �����Ų��.
	CFlipbookPlayer* pFP = GetOwnerObj()->GetComponent<CFlipbookPlayer>();
	if (pFP)
	{
		//pFP->Play();
	}
}

void CIdleState::FinalTick()
{
	// Level �ȿ� �ִ� �÷��̾ ã�´�.
	if (nullptr == m_TargetObject)
	{
		m_TargetObject = CLevelMgr::GetInst()->FindObjectByName(LAYER_TYPE::PLAYER, L"Player");
	}

	// ������ ������ �����´�.
	CMonster* pMon = dynamic_cast<CMonster*>(GetOwnerObj());
	assert(pMon);
	const tMonInfo& info = pMon->GetMonInfo();

	// �÷��̾ ������ �������� ���� �ִ��� Ȯ���Ѵ�.
	if (m_TargetObject)
	{
		Vec2 vTargetPos = m_TargetObject->GetPos();
		Vec2 vPos = pMon->GetPos();
		float fDist = (vTargetPos - vPos).Length();

		// ���� �ȿ� ������ �ڽ��� ���¸� TraceState
		if (fDist < info.DetectRange)
		{
			GetFSM()->ChangeState(L"Trace");
		}
	}

	// �������� �ð�ȭ
	DrawDebugCircle(PEN_TYPE::BLUE, pMon->GetPos(), Vec2(info.DetectRange * 2.f, info.DetectRange * 2.f), 0.f);
}

void CIdleState::Exit()
{
}