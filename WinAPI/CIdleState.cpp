#include "pch.h"
#include "CIdleState.h"


#include "CFlipbookPlayer.h"


CIdleState::CIdleState()
{
}

CIdleState::~CIdleState()
{
}

void CIdleState::Enter()
{	
	CFlipbookPlayer* pFP = GetOwnerObj()->GetComponent<CFlipbookPlayer>();
	if (pFP)
	{
		//pFP->Play();
	}
}

void CIdleState::FinalTick()
{
	// Level �ȿ� �ִ� �÷��̾ ã�´�.

	// ������ ������ �����´�.

	// �÷��̾ ������ �������� ���� �ִ��� Ȯ���Ѵ�.

	// ���� ���̸� return;

	// ���� �ȿ� ������ �ڽ��� ���¸� TraceState
}

void CIdleState::Exit()
{
}