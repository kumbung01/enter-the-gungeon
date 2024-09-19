#include "pch.h"
#include "CFlipbookPlayer.h"

#include "CTimeMgr.h"
#include "CFlipbook.h"

CFlipbookPlayer::CFlipbookPlayer()
	: CComponent(COMPONENT_TYPE::FLIPBOOKPLAYER)
	, m_CurFlipbook(nullptr)
	, m_SpriteIdx(0)
	, m_FPS(0.f)
	, m_Time(0.f)
	, m_Repeat(false)
	, m_Finish(false)
{
}

CFlipbookPlayer::~CFlipbookPlayer()
{
}

void CFlipbookPlayer::FinalTick()
{
	// 현재 재생중인 Flipbook 이 없으면 끝
	if (nullptr == m_CurFlipbook)
	{
		return;
	}

	CSprite* Sprite = m_CurFlipbook->GetSprite(m_SpriteIdx);

	// Sprite 를 화면에 그린다.


	// FPS 에 따른 시간체크
	m_Time += DT;
	if (1.f / m_FPS <= m_Time)
	{
		m_Time -= 1.f / m_FPS;
		++m_SpriteIdx;

		// 마지막 Sprite 에 도달했다면
		// 1. 반복재생 -> 0 번 인덱스로 변경

		// 2. 한번재생 -> 마지막 스프라이트 인덱스를 유지

	}
}