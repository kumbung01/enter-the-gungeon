#include "pch.h"
#include "CRigidBody.h"

#include "CTimeMgr.h"

CRigidBody::CRigidBody()
	: CComponent(COMPONENT_TYPE::RIGIDBODY)
	, m_Mass(1.f)
	, m_InitialSpeed(0.f)
	, m_MaxSpeed(1000.f)
	, m_bGround(false)
{
}

CRigidBody::~CRigidBody()
{
}

void CRigidBody::FinalTick()
{
	CObj* pObject = GetOwner();

	// F / M == A
	Vec2 vAccel = m_Force / m_Mass;

	// ���ӵ��� ���� �ӵ��� ��ȭ
	m_Velocity += vAccel * DT;

	// ���� ���¸� �������·� ����
	m_bPrevMove = m_bMove;

	if (m_Velocity.Length() == 0.f && m_Force.Length() == 0.f)	
		m_bMove = false;	
	else	
		m_bMove = true;

	if (m_bPrevMove == false && m_bMove == true)
	{
		Vec2 vDir = m_Velocity;
		vDir.Normalize();
		m_Velocity += vDir * m_InitialSpeed;
	}

	// �ӵ��� ���� �̵�
	Vec2 vPos = pObject->GetPos();
	vPos += m_Velocity * DT;
	pObject->SetPos(vPos);

	// �� �ʱ�ȭ
	m_Force = Vec2(0.f, 0.f);
}