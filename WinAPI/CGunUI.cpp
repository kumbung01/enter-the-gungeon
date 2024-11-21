#include "pch.h"
#include "CGunUI.h"
#include "CLevelMgr.h"
#include "CPlayer.h"
#include "CGun.h"
#include "CEngine.h"

void CGunUI::Begin()
{
	m_Player = (CPlayer*)CLevelMgr::GetInst()->FindObjectByName(LAYER_TYPE::PLAYER, L"Player");
	m_renderPos = CEngine::GetInst()->GetResolution() * 0.9f;
}

void CGunUI::Tick()
{
}

void CGunUI::Render()
{
	CGun* gun = m_Player->GetGun();

	WCHAR buf[50];

	wsprintf(buf, L"GunType: %s", gun->GetName().c_str());

	TextOut(CEngine::GetInst()->GetSecondDC(), m_renderPos.x, m_renderPos.y, buf, wcslen(buf));

	wsprintf(buf, L"Bullets: %d / %d", gun->GetMagBullets(), gun->GetMaxMagBullets());

	TextOut(CEngine::GetInst()->GetSecondDC(), m_renderPos.x, m_renderPos.y + 20, buf, wcslen(buf));
}

CGunUI::CGunUI()
	: m_Player(nullptr)
{
}

CGunUI::~CGunUI()
{
}
