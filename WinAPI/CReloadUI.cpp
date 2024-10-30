#include "pch.h"
#include "CReloadUI.h"
#include "CTimeMgr.h"



void CReloadBar::Draw(float _duration)
{
	m_currentTime = 0.f;
	m_duration = _duration;
	m_state = UI_STATE::DRAWING;
}

void CReloadBar::Tick()
{
	switch (m_state)
	{
	case UI_STATE::IDLE:
		break;
	case UI_STATE::DRAWING:
		SetPos(m_owner->GetPos() + Vec2(0.f, -50.f)); // update only when drawing state
		m_currentTime += DT;
		if (m_currentTime >= m_duration) {
			m_state = UI_STATE::IDLE;
		}
		break;
	}
}

void CReloadBar::Render()
{
	if (m_state == UI_STATE::DRAWING)
	{
		// TODO:change to pixel texture.
		DrawDebugRect(PEN_TYPE::GREEN, GetRenderPos(), Vec2(100.f, 20.f), 0.f);
		float percentage = m_currentTime / m_duration;
		DrawDebugRect(PEN_TYPE::BLUE, GetRenderPos() + Vec2(percentage * 50.f - 50.f, 0.f), 
			Vec2(100.f * percentage, 20.f), 0.f);
	}
}

CReloadBar::CReloadBar()
	: m_owner(nullptr)
	, m_duration(0.f)
	, m_currentTime(0.f)
	, m_state(UI_STATE::IDLE)
{
}

CReloadBar::~CReloadBar()
{
}
