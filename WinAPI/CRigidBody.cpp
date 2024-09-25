#include "pch.h"
#include "CRigidBody.h"

CRigidBody::CRigidBody()
	: CComponent(COMPONENT_TYPE::RIGIDBODY)
{
}

CRigidBody::~CRigidBody()
{
}

void CRigidBody::FinalTick()
{
	CObj* pObject = GetOwner();

}