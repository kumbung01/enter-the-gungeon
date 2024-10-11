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
	, m_Effect(POST_PROCESS::FADE_IN)
	, m_PostProcess(false)
	, m_PPTime(0.f)
	, m_PPDuration(0.f)
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
	
	// ī�޶� ���� ȿ��
	Oscillation();
}

void CCamera::Render()
{
	if (!m_PostProcess)
		return;

	// �����
	float NormalizedAge = Saturate(m_PPTime / m_PPDuration);
	int Alpha = 0.f;

	// FADE_IN : ���� �������		255 -> 0
	// FADE_OUT : ���� ��ο�����		0 -> 255
	if (FADE_IN == m_Effect)
	{
		Alpha = (int)(1.f - 255.f * NormalizedAge);
	}
	else if (FADE_OUT == m_Effect)
	{
		Alpha = (int)(255.f * NormalizedAge);
	}

	// ��ó�� ȿ���ð��� ����Ǹ� ����� Off �Ѵ�.
	m_PPTime += DT;
	if (m_PPDuration <= m_PPTime)
	{
		m_PostProcess = false;
	}

	HDC dc = CEngine::GetInst()->GetSecondDC();
	BLENDFUNCTION blend = {};

	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0;
	blend.SourceConstantAlpha = Alpha; // �߰� ���ĺ���
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
	
	// ���� ����ũ�⸦ �Ѿ������, ������ ��ȯ�Ѵ�.
	if (m_Amplitude < fabs(m_Offset.y))
	{
		// ���� �ִ�ġ�� ����
		m_Offset.y = m_Amplitude * m_Dir; 

		// ���� ��ȯ
		m_Dir *= -1.f;				

		// �ʰ����� ��ȯ�� ���������� ������Ŵ
		m_Offset.y +=  m_Dir * (m_Amplitude - fabs(m_Offset.y)); 
	}

	m_Time += DT;
	if (m_Duration <= m_Time)
	{
		m_bOscillation = false;
		m_Offset = Vec2(0.f, 0.f);
	}	
}