#include "pch.h"
#include "CPlayerHPUI.h"
#include "CEngine.h"
#include "CLevelMgr.h"
#include "CPlayer.h"

void CPlayerHPUI::Begin()
{
	m_Player = (CPlayer*)CLevelMgr::GetInst()->FindObjectByName(LAYER_TYPE::PLAYER, L"Player");
}

void CPlayerHPUI::Tick()
{
	m_HP = m_Player->GetCurHP();
}

void CPlayerHPUI::Render()
{
	WCHAR buf[50];

	wsprintf(buf, L"HP: %d", m_HP);

	TextOut(CEngine::GetInst()->GetSecondDC(), 30, 30, buf, wcslen(buf));
}

CPlayerHPUI::CPlayerHPUI()
	: m_HP(0)
	, m_Player(nullptr)
{
	
}

CPlayerHPUI::~CPlayerHPUI()
{
}
