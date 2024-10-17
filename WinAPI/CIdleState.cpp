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
	// Level 안에 있는 플레이어를 찾는다.

	// 몬스터의 스탯을 가져온다.

	// 플레이어가 몬스터의 인지범위 내에 있는지 확인한다.

	// 범위 밖이면 return;

	// 범위 안에 있으면 자신의 상태를 TraceState
}

void CIdleState::Exit()
{
}