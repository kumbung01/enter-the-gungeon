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