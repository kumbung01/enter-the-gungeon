#include "pch.h"
#include "CPlayer.h"

#include "CCamera.h"
#include "CAssetMgr.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CTaskMgr.h"
#include "CDbgRender.h"

#include "CMissile.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CGun.h"
#include "CReloadUI.h"

#include "CMonster.h"
#include "CCollider.h"
#include "CFlipbookPlayer.h"
#include "CGuidedMissile.h"

#include "CEngine.h"
#include "CTexture.h"
#include "CFlipbook.h"
#include "CSprite.h"
#include "CRigidBody.h"

enum PLAYER_ANIM_STATE
{
	IDLE_UP,
	IDLE_DOWN,
	IDLE_LEFT,
	IDLE_RIGHT,

	MOVE_UP,
	MOVE_DOWN,
	MOVE_LEFT,
	MOVE_RIGHT,	
};


CPlayer::CPlayer()
	: m_Speed(0.2f)
	, m_AttSpeed(10.f)
	, m_AccTime(0.f)
	, m_HitBox(nullptr)
	, m_FlipbookPlayer(nullptr)
	, m_gun(nullptr)
	//, m_RigidBody(nullptr)
{
	// Collider ������Ʈ �߰�
	m_HitBox = new CCollider;
	m_HitBox->SetName(L"HitBox_01");
	m_HitBox->SetScale(Vec2(60.f, 60.f));
	m_HitBox->SetOffset(Vec2(0.f, 0.f));

	AddComponent(m_HitBox);



	// Flipbook ���� �� ���
	//CreatePlayerFlipbook();

	//// RigidBody ������Ʈ �߰�
	//m_RigidBody = (CRigidBody*)AddComponent(new CRigidBody);
	//m_RigidBody->SetMode(RIGIDBODY_MODE::BELTSCROLL);
	//m_RigidBody->SetInitialSpeed(100.f);
	//m_RigidBody->SetMaxSpeed(500.f);
	//m_RigidBody->SetMass(1.f);
	//m_RigidBody->SetFriction(700.f);
	//m_RigidBody->SetJumpVelocity(Vec2(0.f, -500.f));
}

CPlayer::~CPlayer()
{	
}

void CPlayer::Begin()
{
	m_AccTime = 1.f / m_AttSpeed;

	//m_FlipbookPlayer->Play(IDLE_DOWN, 5.f, true);

	//CCamera::GetInst()->SetTarget(this);


}

void CPlayer::Tick()
{
	//if (KEY_TAP(LEFT))
	//{
	//	m_FlipbookPlayer->Play(MOVE_LEFT, 15.f, true);		
	//}	
	//if (KEY_TAP(RIGHT))
	//{
	//	m_FlipbookPlayer->Play(MOVE_RIGHT, 15.f, true);		
	//}		
	//if (KEY_TAP(UP))
	//{
	//	m_FlipbookPlayer->Play(MOVE_UP, 15.f, true);		
	//}	
	//if (KEY_TAP(DOWN))
	//{
	//	m_FlipbookPlayer->Play(MOVE_DOWN, 15.f, true);		
	//}		

	//if (KEY_RELEASED(LEFT))
	//	m_FlipbookPlayer->Play(IDLE_LEFT, 5.f, true);
	//if (KEY_RELEASED(RIGHT))
	//	m_FlipbookPlayer->Play(IDLE_RIGHT, 5.f, true);
	/*if (KEY_RELEASED(UP))
		m_FlipbookPlayer->Play(IDLE_UP, 5.f, true);
	if (KEY_RELEASED(DOWN))
		m_FlipbookPlayer->Play(IDLE_DOWN, 5.f, true);*/

	Vec2 cursorPos = CCamera::GetInst()->GetRealPos(CKeyMgr::GetInst()->GetMousePos());

	Vec2 moveDir = { 0.f, 0.f };

	if (KEY_PRESSED(KEY::A))
		//m_RigidBody->AddForce(Vec2(-1000.f, 0.f), true);
		moveDir += Vec2(-0.1f, 0.f);
	if (KEY_PRESSED(KEY::D))
		moveDir += Vec2(0.1f, 0.f);
	if (KEY_PRESSED(KEY::W))
		moveDir += Vec2(0.f, -0.1f);
	if (KEY_PRESSED(KEY::S))
		moveDir += Vec2(0.f, 0.1f);
	
	if (moveDir.x != 0.f || moveDir.y != 0.f)
		moveDir.Normalize();

	SetPos(GetPos() + moveDir * m_Speed);

	if (m_gun != nullptr)
	{
		GUN_STATE fireResult = m_gun->Fire();
		GUN_STATE reloadResult = m_gun->Reload(false);
		if (fireResult == GUN_STATE::RELOAD || reloadResult == GUN_STATE::RELOAD)
		{
			this->Reload(m_gun->GetReloadDelay());
		}
	}

	if (KEY_TAP(SPACE))
	{
		CCamera::GetInst()->PostProcessEffect(HEART, 0.2f);
		//m_RigidBody->Jump();
		//DrawDebugRect(PEN_TYPE::GREEN, GetPos(), GetScale() * 2.f, 3.f);
		//DrawDebugCircle(PEN_TYPE::GREEN, GetPos(), GetScale() * 2.f, 3.f);
		//DrawDebugLine(PEN_TYPE::GREEN, GetPos(), GetPos() + GetScale(), 3.f);
	}

	DrawDebugCircle(PEN_TYPE::RED, GetRenderPos(), Vec2(5.f, 5.f), 0.f);
}

void CPlayer::Render()
{
	//m_FlipbookPlayer->Render();
}

void CPlayer::BeginOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider)
{
	if (_OtherObject->GetName() == L"Monster")
	{
		//DeleteObject(_OtherObject);
	}
}

void CPlayer::Overlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider)
{
}

void CPlayer::EndOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider)
{
}

void CPlayer::CreatePlayerFlipbook()
{
	return;
	// AtlasTexture
	CTexture* pAtlas = CAssetMgr::GetInst()->LoadTexture(L"Link", L"Texture\\link_32.bmp");

	/*CreateFlipbook(L"LINK_IDLEDOWN", pAtlas, Vec2(0.f, 0.f), Vec2(120.f, 130.), 3);
	CreateFlipbook(L"LINK_IDLELEFT", pAtlas, Vec2(0.f, 130.f), Vec2(120.f, 130.), 3);
	CreateFlipbook(L"LINK_IDLEUP", pAtlas, Vec2(0.f, 260.f), Vec2(120.f, 130.), 1);
	CreateFlipbook(L"LINK_IDLERIGHT", pAtlas, Vec2(0.f, 390.f), Vec2(120.f, 130.), 3);
	CreateFlipbook(L"LINK_MOVEDOWN", pAtlas, Vec2(0.f, 520.f), Vec2(120.f, 130.), 10);
	CreateFlipbook(L"LINK_MOVELEFT", pAtlas, Vec2(0.f, 650.f), Vec2(120.f, 130.), 10);
	CreateFlipbook(L"LINK_MOVEUP", pAtlas, Vec2(0.f, 780.f), Vec2(120.f, 130.), 10);
	CreateFlipbook(L"LINK_MOVERIGHT", pAtlas, Vec2(0.f, 910.f), Vec2(120.f, 130.), 10);*/

	// FlipbookPlayer ������Ʈ �߰��ϱ�
	m_FlipbookPlayer = (CFlipbookPlayer*)AddComponent(new CFlipbookPlayer);
	
	m_FlipbookPlayer->AddFlipbook(IDLE_DOWN, CAssetMgr::GetInst()->LoadFlipbook(L"LINK_IDLEDOWN" , L"Flipbook\\LINK_IDLEDOWN.flip" ));
	m_FlipbookPlayer->AddFlipbook(IDLE_LEFT, CAssetMgr::GetInst()->LoadFlipbook(L"LINK_IDLELEFT",  L"Flipbook\\LINK_IDLELEFT.flip" ));
	m_FlipbookPlayer->AddFlipbook(IDLE_UP,	 CAssetMgr::GetInst()->LoadFlipbook(L"LINK_IDLEUP"	,  L"Flipbook\\LINK_IDLEUP.flip"   ));
	m_FlipbookPlayer->AddFlipbook(IDLE_RIGHT,CAssetMgr::GetInst()->LoadFlipbook(L"LINK_IDLERIGHT", L"Flipbook\\LINK_IDLERIGHT.flip" ));

	m_FlipbookPlayer->AddFlipbook(MOVE_DOWN, CAssetMgr::GetInst()->LoadFlipbook( L"LINK_MOVEDOWN"	,L"Flipbook\\LINK_MOVEDOWN.flip" ));
	m_FlipbookPlayer->AddFlipbook(MOVE_LEFT, CAssetMgr::GetInst()->LoadFlipbook( L"LINK_MOVELEFT"	,L"Flipbook\\LINK_MOVELEFT.flip" ));
	m_FlipbookPlayer->AddFlipbook(MOVE_UP, CAssetMgr::GetInst()->LoadFlipbook(   L"LINK_MOVEUP"		,L"Flipbook\\LINK_MOVEUP.flip"   ));
	m_FlipbookPlayer->AddFlipbook(MOVE_RIGHT, CAssetMgr::GetInst()->LoadFlipbook(L"LINK_MOVERIGHT"	,L"Flipbook\\LINK_MOVERIGHT.flip"));

	CSprite* pSprite = CAssetMgr::GetInst()->FindSprite(L"LINK_IDLERIGHT_1");
	pSprite->SetOffset(Vec2(1.f, 0.f));
}

void CPlayer::CreateFlipbook(const wstring& _FlipbookName, CTexture* _Atlas, Vec2 _LeftTop, Vec2 _Slice, int MaxFrame)
{
	return;
	// Sprite �����ϱ�
	//for (int i = 0; i < MaxFrame; ++i)
	//{
	//	CSprite* pSprite = new CSprite;
	//	pSprite->Create(_Atlas, Vec2(_LeftTop.x + (_Slice.x * i), _LeftTop.y), _Slice);

	//	wchar_t Key[50] = {};
	//	swprintf_s(Key, 50, (_FlipbookName + L"_%d").c_str(), i);
	//	CAssetMgr::GetInst()->AddSprite(Key, pSprite);

	//	wstring strSavePath = L"Sprite\\";
	//	strSavePath += pSprite->GetKey();
	//	pSprite->Save(strSavePath);
	//}

	for (int i = 0; i < MaxFrame; ++i)
	{
		wchar_t Key[50] = {};
		swprintf_s(Key, 50, (_FlipbookName + L"_%d").c_str(), i);		
		wstring Path = L"Sprite\\";		
		Path += Key;
		CAssetMgr::GetInst()->LoadSprite(Key, Path + L".sprite");
	}


	// Flipbook �����ϱ�
	//CFlipbook* pFlipbook = new CFlipbook;

	//for (int i = 0; i < MaxFrame; ++i)
	//{
	//	wchar_t Key[50] = {};
	//	swprintf_s(Key, 50, (_FlipbookName + L"_%d").c_str(), i);
	//	pFlipbook->AddSprite(CAssetMgr::GetInst()->FindSprite(Key));		
	//}

	//CAssetMgr::GetInst()->AddFlipbook(_FlipbookName, pFlipbook);
	//wstring Path = L"Flipbook\\";
	//pFlipbook->Save(Path + _FlipbookName);
}

void CPlayer::Reload(float _duration)
{
	m_reloadUI->DrawUI(_duration);
}

