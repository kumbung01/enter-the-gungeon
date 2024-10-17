#include "pch.h"
#include "CTraceState.h"

CTraceState::CTraceState()
{
}

CTraceState::~CTraceState()
{
}

void CTraceState::Enter()
{
	// Level 에서 추적대상 플레이어를 찾는다.
}

void CTraceState::FinalTick()
{
	// 몬스터의 스탯정보를 가져온다.

	// 몬스터의 이동속에 맞게 플레이어를 향해서 이동한다.

	// 플레이어가 공격범위 안으로 들어오면 Attack 상태로 변경한다.

	// 만약에 추적중에 피격을 당하면, 피격상태로 전환다.

}

void CTraceState::Exit()
{
}