#include "pch.h"
#include "CReloadUI.h"
#include "CTimeMgr.h"
#include "CEngine.h"
#include "CAssetMgr.h"
#include "CFlipbookPlayer.h"
#include "CFlipbook.h"


void CReloadBar::Draw(DRAW_TYPE _type, float _duration)
{
	m_currentTime = 0.f;
	m_duration = _duration;
	m_type = _type;
	m_state = UI_STATE::DRAWING;
	float fps = m_frameCount / m_duration;
	m_flipbookPlayer->Play({ 0, false }, fps, false);
}

void CReloadBar::Tick()
{
	SetPos(m_owner->GetPos() + Vec2(0.f, -50.f)); // update only when drawing state
	switch (m_state)
	{
	case UI_STATE::IDLE:
		break;
	case UI_STATE::DRAWING:
		m_currentTime += DT;
		if (m_currentTime >= m_duration) {
			m_state = UI_STATE::IDLE;
		}
		break;
	}
}

void CReloadBar::Render()
{
	if (m_state == UI_STATE::DRAWING && m_type == DRAW_TYPE::RELOADING)
	{
		m_flipbookPlayer->Render();
	}
	else if (m_type == DRAW_TYPE::EMPTY)
	{
		TextOut(CEngine::GetInst()->GetSecondDC(), GetRenderPos().x - 25, GetRenderPos().y, L"Reload", wcslen(L"Reload"));
	}
}

CReloadBar::CReloadBar()
	: m_owner(nullptr)
	, m_duration(0.f)
	, m_currentTime(0.f)
	, m_state(UI_STATE::IDLE)
	, m_type(DRAW_TYPE::NONE)
	, m_flipbookPlayer(nullptr)
{
	m_flipbookPlayer = (CFlipbookPlayer*)AddComponent(new CFlipbookPlayer);
	m_flipbookPlayer->SetMagnification(2.5f);

	CFlipbook* flipbook = CAssetMgr::GetInst()->LoadFlipbook(L"reload_bar", L"Flipbook\\ReloadBar\\reload_bar.flip");
	m_frameCount = flipbook->GetMaxSpriteCount();
	m_flipbookPlayer->AddFlipbook(flipbook);
}

CReloadBar::~CReloadBar()
{
}
