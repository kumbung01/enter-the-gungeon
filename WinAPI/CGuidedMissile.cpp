#include "pch.h"
#include "CGuidedMissile.h"


#include "CLevelMgr.h"
#include "CLevel.h"
#include "CCollider.h"

CGuidedMissile::CGuidedMissile()	
	: m_Target(nullptr)
	, m_DetectRange(700.f)
{
	GetCollider()->SetScale(Vec2(50.f, 50.f));
}

CGuidedMissile::~CGuidedMissile()
{
}

void CGuidedMissile::Tick()
{
	// Ÿ���� ��ȿ�ϸ�
	if (IsValid(m_Target))
	{
		//TraceTarget_0();
		TraceTarget_1();
	}

	// Ÿ���� ��ȿ���� ������
	else
	{
		// ���� ����� ã�´�.
		FindTarget();
	}

	DrawDebugCircle(PEN_TYPE::BLUE, GetPos(), Vec2(m_DetectRange * 2.f, m_DetectRange*2.f), 0.f);

	CMissile::Tick();
}

void CGuidedMissile::FindTarget()
{
	m_Target = nullptr;

	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	const vector<CObj*>& vecMon = pCurLevel->GetObjects(LAYER_TYPE::MONSTER);

	// �̻��� ���ΰ� ���� ����� ����� Ÿ������ �����Ѵ�.
	Vec2 vPos = GetPos(); // �̻��� ������ ��ġ
	float MinDistance = m_DetectRange;

	for (size_t i = 0; i < vecMon.size(); ++i)
	{
		if (vecMon[i]->IsDead())
			continue;

		Vec2 vMonPos = vecMon[i]->GetPos(); // ������ ��ġ
		float Dist = (vPos - vMonPos).Length();

		// �ּҰŸ��� ���ŵ� ���
		if (Dist < MinDistance)
		{
			MinDistance = Dist;
			m_Target = vecMon[i];
		}
	}
}

void CGuidedMissile::TraceTarget_0()
{
	// Ÿ���� ���ؼ� �̵������� �����Ѵ�.
	Vec2 vDir = (m_Target->GetPos() - GetPos());
	vDir.Normalize(); // �������� ���� ��������
	vDir *= GetVelocity().Length();
	SetVelocity(vDir);
}

void CGuidedMissile::TraceTarget_1()
{
	// Ÿ���� ���ؼ� ���� �ش�.
	// 1. Ÿ���� ���� ������ �˾Ƴ���.
	Vec2 vDir = m_Target->GetPos() - GetPos();
	vDir.Normalize();
	AddForce(vDir * 500.f);
}

void CGuidedMissile::TraceTarget_2()
{
	// Ÿ���� ���� ������ ȸ����Ų��.

}

void CGuidedMissile::BeginOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider)
{
	if (_OtherObject->GetName() == L"Monster")
	{
		//DeleteObject(this);
		//DeleteObject(_OtherObject);
	}		
}