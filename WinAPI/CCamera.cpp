#include "pch.h"
#include "CCamera.h"

#include "CEngine.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"

CCamera::CCamera()
	: m_Target(nullptr)
{

}

CCamera::~CCamera()
{

}

void CCamera::Init()
{
	Vec2 Resolution = CEngine::GetInst()->GetResolution();
	m_LookAt = Resolution / 2.f;
}

void CCamera::Tick()
{
	Vec2 Resolution = CEngine::GetInst()->GetResolution();
	m_Diff = m_LookAt - (Resolution / 2.f);

	if (KEY_PRESSED(KEY::W))
		m_LookAt.y -= DT * 500.f;
	if (KEY_PRESSED(KEY::S))
		m_LookAt.y += DT * 500.f;
	if (KEY_PRESSED(KEY::A))
		m_LookAt.x -= DT * 500.f;
	if (KEY_PRESSED(KEY::D))
		m_LookAt.x += DT * 500.f;
}

void CCamera::Render()
{
}
