#include "pch.h"
#include "CMonster.h"

#include "CEngine.h"
#include "CTimeMgr.h"
#include "CCollider.h"

#include "CAssetMgr.h"
#include "CTexture.h"


CMonster::CMonster()
	: m_Dir(1)
	, m_Speed(300.f)
	, m_Dist(100.f)
{
	m_Collider = (CCollider*)AddComponent(new CCollider);
	m_Collider->SetScale(Vec2(100.f, 100.f));

	m_Tex = CAssetMgr::GetInst()->LoadTexture(L"Character", L"Texture\\Character.png");
}

CMonster::~CMonster()
{
}

void CMonster::Begin()
{
	// ������ �����Ҷ� �ʱ� ��ġ�� ���
	m_InitPos = GetPos();
}

void CMonster::Tick()
{
	return;

	Vec2 vPos = GetPos();

	vPos.x += DT * m_Speed * m_Dir;
	
	float fDistance = fabs(m_InitPos.x - vPos.x);

	if (m_Dist < fDistance)
	{
		vPos.x = m_InitPos.x + m_Dir * m_Dist;
		m_Dir *= -1;
	}

	SetPos(vPos);
}

void CMonster::Render()
{
	HDC dc = CEngine::GetInst()->GetSecondDC();

	Vec2 vPos = GetRenderPos();
	Vec2 vScale = GetScale();

	BitBlt(dc
		, vPos.x - m_Tex->GetWidth() / 2.f
		, vPos.y - m_Tex->GetHeight() / 2
		, m_Tex->GetWidth()
		, m_Tex->GetHeight()
		, m_Tex->GetDC()
		, 0, 0
		, SRCCOPY);


	//AlphaBlend();



	/*Ellipse(dc, vPos.x - vScale.x / 2.f, vPos.y - vScale.y / 2
		, vPos.x + vScale.x / 2.f, vPos.y + vScale.y / 2.f );*/
}



void CMonster::BeginOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider)
{
	if (_OtherObject->GetName() == L"Player")
	{
		// �÷��̾�� �ε����� ���� ���������� �Ѿ��.
		ChangeLevel(LEVEL_TYPE::EDITOR);
	}
}