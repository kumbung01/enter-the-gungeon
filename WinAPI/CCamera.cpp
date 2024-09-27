#include "pch.h"
#include "CCamera.h"

#include "CEngine.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"

#include "CObj.h"

CCamera::CCamera()
	: m_Target(nullptr)
	, m_Duration(0.f)
	, m_Amplitude(0.f)
	, m_Frequency(0.f)
	, m_Time(0.f)
	, m_Dir(1.f)
	, m_bOscillation(false)
{
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