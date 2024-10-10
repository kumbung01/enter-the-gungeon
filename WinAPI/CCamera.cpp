#include "pch.h"
#include "CCamera.h"

#include "CEngine.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"

#include "CObj.h"

#include "CAssetMgr.h"
#include "CTexture.h"

CCamera::CCamera()
	: m_Target(nullptr)
	, m_Duration(0.f)
	, m_Amplitude(0.f)
	, m_Frequency(0.f)
	, m_Time(0.f)
	, m_Dir(1.f)
	, m_bOscillation(false)
{
	Vec2 vResolution = CEngine::GetInst()->GetResolution();
	m_CamTex = CAssetMgr::GetInst()->CreateTexture(L"CameraTex", (UINT)vResolution.x, (UINT)vResolution.y);
}

CCamera::~CCamera()
{
}

void CCamera::Init()
{
	Vec2 Resolution = CEngine::GetInst()->GetResolution();
	m_LookAt = Resolution / 2.f;

	m_Offset = Vec2(0.f, 0.f);
}

void CCamera::Tick()
{
	Vec2 Resolution = CEngine::GetInst()->GetResolution();
	m_Diff = (m_LookAt + m_Offset) - (Resolution / 2.f);

	if (KEY_PRESSED(KEY::W))
		m_LookAt.y -= DT * 500.f;
	if (KEY_PRESSED(KEY::S))
		m_LookAt.y += DT * 500.f;
	if (KEY_PRESSED(KEY::A))
		m_LookAt.x -= DT * 500.f;
	if (KEY_PRESSED(KEY::D))
		m_LookAt.x += DT * 500.f;

	if (m_Target)
	{
		m_LookAt = m_Target->GetPos();
	}
	
	// 카메라 진동 효과
	Oscillation();
}

void CCamera::Render()
{
	HDC dc = CEngine::GetInst()->GetSecondDC();

	BLENDFUNCTION blend = {};

	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0;
	blend.SourceConstantAlpha = 0; // 추가 알파블렌드
	blend.AlphaFormat = 0;

	AlphaBlend(dc
		, 0.f, 0.f
		, m_CamTex->GetWidth()
		, m_CamTex->GetHeight()
		, m_CamTex->GetDC()
		, 0, 0
		, m_CamTex->GetWidth()
		, m_CamTex->GetHeight()
		, blend);
}

void CCamera::Oscillation()
{
	if (false == m_bOscillation)
		return;

	float Speed = m_Amplitude * 4.f * m_Frequency;
	m_Offset.y += Speed * m_Dir * DT;
	
	// 만약 진폭크기를 넘어서버리면, 방향을 전환한다.
	if (m_Amplitude < fabs(m_Offset.y))
	{
		// 진폭 최대치로 설정
		m_Offset.y = m_Amplitude * m_Dir; 

		// 방향 전환
		m_Dir *= -1.f;				

		// 초과량을 전환된 방향쪽으로 전진시킴
		m_Offset.y +=  m_Dir * (m_Amplitude - fabs(m_Offset.y)); 
	}

	m_Time += DT;
	if (m_Duration <= m_Time)
	{
		m_bOscillation = false;
		m_Offset = Vec2(0.f, 0.f);
	}	
}