#include "pch.h"
#include "CCollider.h"

CCollider::CCollider()
	: CComponent(COMPONENT_TYPE::COLLIDER)
{
}

CCollider::~CCollider()
{
}

void CCollider::FinalTick()
{
	m_FinalPos = m_Offset + GetOwner()->GetPos();

	DrawDebugRect(PEN_TYPE::GREEN, m_FinalPos, m_Scale, 0.f);
}


void CCollider::BeginOverlap(CCollider* _Other)
{
}

void CCollider::Overlap(CCollider* _Other)
{
}

void CCollider::EndOverlap(CCollider* _Other)
{
}
