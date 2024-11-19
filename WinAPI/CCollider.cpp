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
		DrawDebugRect(PEN_TYPE::GREEN, vRenderPos, m_Scale, 0.f);
}


Vec2 CCollider::CalCulateNormal(CCollider* _other)
{
	Vec2 myPos = m_FinalPos + m_Offset;
	Vec2 urPos = _other->m_FinalPos + _other->m_Offset;
	Vec2 diff = myPos - urPos;

	float diffx = abs(diff.x);
	float diffy = abs(diff.y);

	float scalediffx = (m_Scale.x + _other->m_Scale.x) / 2.f;
	float scalediffy = (m_Scale.y + _other->m_Scale.y) / 2.f;

	float comparedX = scalediffx - diffx;
	float comparedY = scalediffy - diffy;

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
	if (m_RigidBody)
	{
		Vec2 normal = CalCulateNormal(_Other);
		Vec2 rigidNormal = m_RigidBody->GetContactNormal();

		if (abs(normal.x) > 0.f) rigidNormal.x = normal.x;
		else rigidNormal.y = normal.y;

		m_RigidBody->SetContactNormal(rigidNormal);
	}

	GetOwner()->Overlap(this, _Other->GetOwner(), _Other);
}

void CCollider::EndOverlap(CCollider* _Other)
{
	--m_OverlapCount;

	if (m_RigidBody)
		m_RigidBody->SetContactNormal({ 0.f, 0.f });

	GetOwner()->EndOverlap(this, _Other->GetOwner(), _Other);
}
