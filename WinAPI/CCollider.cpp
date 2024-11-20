#include "pch.h"
#include "CCollider.h"

#include "CLevelMgr.h"
#include "CLevel.h"
#include "CCamera.h"
#include "CRigidBody.h"

CCollider::CCollider()
	: CComponent(COMPONENT_TYPE::COLLIDER)
	, m_OverlapCount(0)
	, m_RigidBody(nullptr)
	, m_Active(true)
	, m_flag({false})
{
}

CCollider::~CCollider()
{
}

void CCollider::FinalTick()
{
	m_FinalPos = m_Offset + GetOwner()->GetPos();

	// Collider 등록하기
	LAYER_TYPE LayerType = GetOwner()->GetLayerType();
	CLevelMgr::GetInst()->GetCurrentLevel()->RegisterCollider(this, LayerType);


	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(m_FinalPos);
	if(m_OverlapCount)
		DrawDebugRect(PEN_TYPE::RED, vRenderPos, m_Scale, 0.f);
	else
		DrawDebugRect(PEN_TYPE::BLUE, vRenderPos, m_Scale, 0.f);
}


Vec2 CCollider::CalCulateNormal(CCollider* _other)
{
	Vec2 diff = m_FinalPos - _other->m_FinalPos;
	Vec2 scalediff = (m_Scale + _other->m_Scale) / 2.f;

	float comparedX = abs(scalediff.x - abs(diff.x));
	float comparedY = abs(scalediff.y - abs(diff.y));

	if (comparedX <= comparedY)
	{
		return diff.x < 0 ? Vec2(-1.f, 0.f) : Vec2(1.f, 0.f);
	}
	else
	{
		return diff.y < 0 ? Vec2(0.f, -1.f) : Vec2(0.f, 1.f);
	}
}

void CCollider::BeginOverlap(CCollider* _Other)
{
	++m_OverlapCount;

	GetOwner()->BeginOverlap(this, _Other->GetOwner(), _Other);
}

void CCollider::Overlap(CCollider* _Other)
{
	if (m_RigidBody && _Other->IsRigid())
	{
		Vec2 normal = CalCulateNormal(_Other);
		CRigidBody::Dir rigidNormal = m_RigidBody->GetContactNormal();

		if (normal.x < 0)      rigidNormal.left = 1;
		else if (normal.x > 0) rigidNormal.right = 1;
		else if (normal.y > 0) rigidNormal.down = 1;
		else				   rigidNormal.up = 1;

		m_RigidBody->SetContactNormal(rigidNormal);
	}

	GetOwner()->Overlap(this, _Other->GetOwner(), _Other);
}

void CCollider::EndOverlap(CCollider* _Other)
{
	--m_OverlapCount;

	if (m_RigidBody)
		m_RigidBody->SetContactNormal({});

	GetOwner()->EndOverlap(this, _Other->GetOwner(), _Other);
}
