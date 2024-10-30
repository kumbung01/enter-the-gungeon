#include "pch.h"
#include "CTraceState.h"

#include "CLevelMgr.h"
#include "CMonster.h"
#include "CTimeMgr.h"

CTraceState::CTraceState()
	: m_TargetObject(nullptr)
{
}

CTraceState::~CTraceState()
{
}

void CTraceState::Enter()
{
	// Level ���� ������� �÷��̾ ã�´�.
	if (nullptr == m_TargetObject)
	{
		m_TargetObject = CLevelMgr::GetInst()->FindObjectByName(LAYER_TYPE::PLAYER, L"Player");
	}
}

void CTraceState::FinalTick()
{
	// ������ ���������� �����´�.	
	CMonster* pMon = dynamic_cast<CMonster*>(GetOwnerObj());
	assert(pMon);
	const tMonInfo& info = pMon->GetMonInfo();

	// ������ �̵��ӿ� �°� �÷��̾ ���ؼ� �̵��Ѵ�.
	// �̵� ���� ���
	Vec2 vMoveDir = m_TargetObject->GetPos() - pMon->GetPos();
	vMoveDir.Normalize();

	// �ش� ��������, �ӷ¿� �°� �������Ӹ��� �̵�
	Vec2 vPos = pMon->GetPos() + vMoveDir * info.Speed * DT;
	pMon->SetPos(vPos);

	// �÷��̾ ���ݹ��� ������ ������ Attack ���·� �����Ѵ�.

	// ���࿡ �����߿� �ǰ��� ���ϸ�, �ǰݻ��·� ��ȯ��.

		
	// �������� �ð�ȭ
	DrawDebugCircle(PEN_TYPE::BLUE, pMon->GetRenderPos(), Vec2(info.DetectRange * 2.f, info.DetectRange * 2.f), 0.f);
}

void CTraceState::Exit()
{
}