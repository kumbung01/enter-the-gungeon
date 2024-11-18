#include "pch.h"
#include "CDieState.h"

tAnimState CDieState::ProcessAnimState(Vec2 dir)
{
	return tAnimState();
}

void CDieState::Enter()
{
}

void CDieState::FinalTick()
{
	DeleteObject(GetOwnerObj());
}

void CDieState::Exit()
{
}

CDieState::CDieState()
{
}

CDieState::~CDieState()
{
}
