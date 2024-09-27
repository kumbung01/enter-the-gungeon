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
	, m_GravityAccel(Vec2(0.f, 980.f))
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

	// Velocity Debug Render
	DrawDebugLine(PEN_TYPE::BLUE, GetOwner()->GetRenderPos(), GetOwner()->GetRenderPos() + m_Velocity * 0.3f, 0.f);
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
	CalcInitSpeed_TopView();

	// �����¿� ���� �ӵ� ����
	CalcFriction_TopView();

	// �ִ�ӷ� ����
	CalcMaxSpeed_TopView();

	// �ӵ��� ���� �̵�
	Vec2 vPos = pObject->GetPos();
	vPos += m_Velocity * DT;
	pObject->SetPos(vPos);

	// �� �ʱ�ȭ
	m_Force = Vec2(0.f, 0.f);
}

void CRigidBody::FinalTick_BeltScroll()
{
	CObj* pObject = GetOwner();

	// F / M == A
	Vec2 vAccel = m_Force / m_Mass;

	// ���ӵ��� ���� �ӵ��� ��ȭ
	m_VelocityX += Vec2(vAccel.x * DT, 0.f);
	m_VelocityY += Vec2(0.f, vAccel.y * DT);

	if (m_Velocity.Length() != 0.f)
		int a = 0;

	// ���� üũ
	CheckState();

	// �ʱ�ӵ� ���
	CalcInitSpeed_BeltScroll();

	// �����¿� ���� �ӵ� ����
	CalcFriction_BeltScroll();

	// �ִ�ӷ� ����
	CalcMaxSpeed_BeltScroll();

	// �߷� ���ӵ� ���	
	if(false == m_bGround) // ���߿� ���� ���
		m_VelocityY += m_GravityAccel * DT;
	else if(0.f < m_VelocityY.y )
	{
		m_VelocityY.y = 0.f;
	}

	// ���ص� �ӵ��� ���ļ� ���� �ӵ��� ����Ѵ�.
	m_Velocity = m_VelocityX + m_VelocityY;

	// �ӵ��� ���� �̵�
	Vec2 vPos = pObject->GetPos();
	vPos += m_Velocity * DT;
	pObject->SetPos(vPos);

	// �ʱ�ȭ
	m_Force = Vec2(0.f, 0.f);
	m_Self = false;
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

void CRigidBody::CalcInitSpeed_TopView()
{
	if (m_bPrevMove == false && m_bMove == true && m_Self)
	{
		Vec2 vDir = m_Velocity;
		vDir.Normalize();
		m_Velocity += vDir * m_InitialSpeed;
	}
}

void CRigidBody::CalcInitSpeed_BeltScroll()
{
	if (m_bPrevMove == false && m_bMove == true && m_Self)
	{
		Vec2 vDir = m_VelocityX;
		vDir.Normalize();
		m_VelocityX += vDir * m_InitialSpeed;
	}
}

void CRigidBody::CalcFriction_TopView()
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

void CRigidBody::CalcFriction_BeltScroll()
{
	float Speed = m_VelocityX.Length();

	if (0.f != Speed)
	{
		Speed -= m_Friction * m_Mass * DT;
		if (Speed < 0.f)
			Speed = 0.f;

		m_VelocityX.Normalize();
		m_VelocityX *= Speed;
	}
}

void CRigidBody::CalcMaxSpeed_TopView()
{
	float Speed = m_Velocity.Length();

	if (m_MaxSpeed < Speed)
	{
		Speed = m_MaxSpeed;
		m_Velocity.Normalize();
		m_Velocity *= Speed;
	}
}

void CRigidBody::CalcMaxSpeed_BeltScroll()
{
	float Speed = m_VelocityX.Length();

	if (m_MaxSpeed < Speed)
	{
		Speed = m_MaxSpeed;
		m_VelocityX.Normalize();
		m_VelocityX *= Speed;
	}
}

void CRigidBody::Jump()
{
	if (RIGIDBODY_MODE::TOPVIEW == m_Mode || !m_bGround)
		return;

	m_VelocityY += m_JumpVelocity;
	m_bGround = false;
}