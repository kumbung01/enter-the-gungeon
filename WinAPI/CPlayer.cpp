#include "pch.h"
#include "CPlayer.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CTaskMgr.h"
#include "CDbgRender.h"

#include "CMissile.h"
#include "CLevelMgr.h"
#include "CLevel.h"

#include "CMonster.h"
#include "CCollider.h"
#include "CGuidedMissile.h"

#include "CEngine.h"
#include "CTexture.h"

CPlayer::CPlayer()
	: m_Speed(200.f)
	, m_AttSpeed(10.f)
	, m_AccTime(0.f)
	, m_Texture(nullptr)
{
	// Collider ������Ʈ �߰�
	m_HitBox = new CCollider;
	m_HitBox->SetName(L"HitBox_01");
	m_HitBox->SetScale(Vec2(20.f, 40.f));
	m_HitBox->SetOffset(Vec2(0.f, 20.f));

	AddComponent(m_HitBox);

	// RTTI(RunTime Type Identification(Infomation) ) -> C++ �� ��� dynamic_cast �� �ִ�.

	//CCollider* pC = (CCollider*)GetComponent(L"HitBox_01");
	//CCollider* pC = (CCollider*)GetComponent(COMPONENT_TYPE::COLLIDER);
	//CCollider* pC = GetComponent<CCollider>();

	// ������, ��ü �ߺ� �ε� ����	
	m_Texture = new CTexture;
	m_Texture->Load(L"D:\\JeeHun\\AssortRock NormalClass\\53th\\AR53\\WinAPI\\Fighter.bmp");
}

CPlayer::~CPlayer()
{
	DELETE(m_Texture);
}

void CPlayer::Begin()
{
	m_AccTime = 1.f / m_AttSpeed;
}

void CPlayer::Tick()
{
	Vec2 vPos = GetPos();
	
	if (KEY_PRESSED(LEFT))
		vPos.x -= DT * m_Speed;
	if (KEY_PRESSED(RIGHT))
		vPos.x += DT * m_Speed;
	if (KEY_PRESSED(UP))
		vPos.y -= DT * m_Speed;
	if (KEY_PRESSED(DOWN))
		vPos.y += DT * m_Speed;

	if (KEY_TAP(SPACE))
	{
		//DrawDebugRect(PEN_TYPE::GREEN, GetPos(), GetScale() * 2.f, 3.f);
		//DrawDebugCircle(PEN_TYPE::GREEN, GetPos(), GetScale() * 2.f, 3.f);
		//DrawDebugLine(PEN_TYPE::GREEN, GetPos(), GetPos() + GetScale(), 3.f);
	}

	// �̻��� �߻�
	if (KEY_PRESSED(SPACE))
	{
		// �ð�üũ
		m_AccTime += DT;

		if (1.f / m_AttSpeed <= m_AccTime)
		{
			m_AccTime -= 1.f / m_AttSpeed;

			// �̻��� ����			
			CMissile* pMissile = new CGuidedMissile;
			pMissile->SetPos(vPos + Vec2(0.f, -GetScale().y / 2.f));
			pMissile->SetScale(20.f, 20.f);
			pMissile->SetVelocity(Vec2(cosf(PI / 2.f), -sinf(PI / 2.f)) * 400.f);
			CreateObject(pMissile, LAYER_TYPE::PLAYER_OBJECT);			
		}
	}

	else if (KEY_RELEASED(SPACE))
	{
		m_AccTime = 1.f / m_AttSpeed;
	}

	SetPos(vPos);
}

void CPlayer::Render()
{
	Vec2 Pos = GetPos();		
	UINT Width = m_Texture->GetWidth();
	UINT Height = m_Texture->GetHeight();
	HDC hBackDC = CEngine::GetInst()->GetSecondDC();

	/*BitBlt(hBackDC
		, Pos.x - (Width / 2)
		, Pos.y - (Height / 2)
		, Width, Height
		, m_Texture->GetDC()
		, 0, 0, SRCCOPY);*/

	TransparentBlt(hBackDC
		, Pos.x - (Width / 2)
		, Pos.y - (Height / 2)
		, Width, Height
		, m_Texture->GetDC()
		, 0, 0, Width, Height, RGB(255, 0, 255));
}

void CPlayer::BeginOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider)
{
	if (_OtherObject->GetName() == L"Monster")
	{
		DeleteObject(_OtherObject);
	}
}

void CPlayer::Overlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider)
{
}

void CPlayer::EndOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider)
{
}

