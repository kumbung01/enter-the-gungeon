#include "pch.h"
#include "CCollider.h"

#include "CLevelMgr.h"
#include "CLevel.h"

CCollider::CCollider()
	: CComponent(COMPONENT_TYPE::COLLIDER)
	, m_Collision(false)
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

	if(m_Collision)
		DrawDebugRect(PEN_TYPE::RED, m_FinalPos, m_Scale, 0.f);
	else
		DrawDebugRect(PEN_TYPE::GREEN, m_FinalPos, m_Scale, 0.f);
}


void CCollider::BeginOverlap(CCollider* _Other)
{
	m_Collision = true;
}

void CCollider::Overlap(CCollider* _Other)
{
}

void CCollider::EndOverlap(CCollider* _Other)
{
	m_Collision = false;
}
