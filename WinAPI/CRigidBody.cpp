#include "pch.h"
#include "CRigidBody.h"

#include "CTimeMgr.h"

CRigidBody::CRigidBody()
	: CComponent(COMPONENT_TYPE::RIGIDBODY)
	, m_Mass(1.f)
	, m_InitialSpeed(0.f)
	, m_MaxSpeed(1000.f)
	, m_bGround(false)
	, m_Friction(100.f)
	, m_bPrevMove(false)
	, m_bMove(false)
	, m_Mode(RIGIDBODY_MODE::TOPVIEW)
{

}

CRigidBody::~CRigidBody()
{

}

void CRigidBody::FinalTick()
{
	if (RIGIDBODY_MODE::TOPVIEW == m_Mode)
		FinalTick_TopView();
	else
		FinalTick_BeltScroll();
}

void CRigidBody::FinalTick_TopView()
{
	CObj* pObject = GetOwner();

	// F / M == A
	Vec2 vAccel = m_Force / m_Mass;

	// ���ӵ��� ���� �ӵ��� ��ȭ
	m_Velocity += vAccel * DT;

	// ���� üũ
	CheckState();

	// �ʱ�ӵ� ���
	CalcInitSpeed();

	// �����¿� ���� �ӵ� ����
	CalcFriction();

	// �ִ�ӷ� ����
	CalcMaxSpeed();

	// �ӵ��� ���� �̵�
	Vec2 vPos = pObject->GetPos();
	vPos += m_Velocity * DT;
	pObject->SetPos(vPos);

	// �� �ʱ�ȭ
	m_Force = Vec2(0.f, 0.f);
}

void CRigidBody::FinalTick_BeltScroll()
{

}

void CRigidBody::CheckState()
{
	// ���� ���¸� �������·� ����
	m_bPrevMove = m_bMove;

	if (m_Velocity.Length() == 0.f && m_Force.Length() == 0.f)
		m_bMove = false;
	else
		m_bMove = true;
}

void CRigidBody::CalcInitSpeed()
{
	if (m_bPrevMove == false && m_bMove == true)
	{
		Vec2 vDir = m_Velocity;
		vDir.Normalize();
		m_Velocity += vDir * m_InitialSpeed;
	}
}

void CRigidBody::CalcFriction()
{
	float Speed = m_Velocity.Length();

	if (0.f != Speed)
	{
		Speed -= m_Friction * m_Mass * DT;
		if (Speed < 0.f)
			Speed = 0.f;

		m_Velocity.Normalize();
		m_Velocity *= Speed;
	}
}

void CRigidBody::CalcMaxSpeed()
{
	float Speed = m_Velocity.Length();

	if (m_MaxSpeed < Speed)
	{
		Speed = m_MaxSpeed;
		m_Velocity.Normalize();
		m_Velocity *= Speed;
	}
}
