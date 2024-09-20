#include "pch.h"
#include "CPlayer.h"

#include "CAssetMgr.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CTaskMgr.h"
#include "CDbgRender.h"

#include "CMissile.h"
#include "CLevelMgr.h"
#include "CLevel.h"

#include "CMonster.h"
#include "CCollider.h"
#include "CFlipbookPlayer.h"
#include "CGuidedMissile.h"

#include "CEngine.h"
#include "CTexture.h"
#include "CFlipbook.h"
#include "CSprite.h"

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
	: m_Speed(200.f)
	, m_AttSpeed(10.f)
	, m_AccTime(0.f)
	, m_HitBox(nullptr)
	, m_FlipbookPlayer(nullptr)
	, m_Texture(nullptr)
{
	// Collider 컴포넌트 추가
	m_HitBox = new CCollider;
	m_HitBox->SetName(L"HitBox_01");
	m_HitBox->SetScale(Vec2(20.f, 40.f));
	m_HitBox->SetOffset(Vec2(0.f, 20.f));

	AddComponent(m_HitBox);

	// Flipbook 생성 및 등록
	CreatePlayerFlipbook();
}

CPlayer::~CPlayer()
{
	DELETE(m_Texture);
}

void CPlayer::Begin()
{
	m_AccTime = 1.f / m_AttSpeed;

	m_FlipbookPlayer->Play(IDLE_DOWN, 5.f, true);
}

void CPlayer::Tick()
{
	Vec2 vPos = GetPos();
	
	if(KEY_TAP(LEFT))
		m_FlipbookPlayer->Play(MOVE_LEFT, 15.f, true);
	if (KEY_TAP(RIGHT))
		m_FlipbookPlayer->Play(MOVE_RIGHT, 15.f, true);
	if (KEY_TAP(UP))
		m_FlipbookPlayer->Play(MOVE_UP, 15.f, true);
	if (KEY_TAP(DOWN))
		m_FlipbookPlayer->Play(MOVE_DOWN, 15.f, true);

	if (KEY_RELEASED(LEFT))
		m_FlipbookPlayer->Play(IDLE_LEFT, 5.f, true);
	if (KEY_RELEASED(RIGHT))
		m_FlipbookPlayer->Play(IDLE_RIGHT, 5.f, true);
	if (KEY_RELEASED(UP))
		m_FlipbookPlayer->Play(IDLE_UP, 5.f, true);
	if (KEY_RELEASED(DOWN))
		m_FlipbookPlayer->Play(IDLE_DOWN, 5.f, true);

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

	// 미사일 발사
	if (KEY_PRESSED(SPACE))
	{
		// 시간체크
		m_AccTime += DT;

		if (1.f / m_AttSpeed <= m_AccTime)
		{
			m_AccTime -= 1.f / m_AttSpeed;

			// 미사일 생성			
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
	m_FlipbookPlayer->Render();
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

void CPlayer::CreatePlayerFlipbook()
{
	// AtlasTexture
	CTexture* pAtlas = CAssetMgr::GetInst()->LoadTexture(L"Link", L"Texture\\link_32.bmp");

	CreateFlipbook(L"LINK_IDLEDOWN", pAtlas, Vec2(0.f, 0.f), Vec2(120.f, 130.), 3);
	CreateFlipbook(L"LINK_IDLELEFT", pAtlas, Vec2(0.f, 130.f), Vec2(120.f, 130.), 3);
	CreateFlipbook(L"LINK_IDLEUP", pAtlas, Vec2(0.f, 260.f), Vec2(120.f, 130.), 1);
	CreateFlipbook(L"LINK_IDLERIGHT", pAtlas, Vec2(0.f, 390.f), Vec2(120.f, 130.), 3);

	CreateFlipbook(L"LINK_MOVEDOWN", pAtlas, Vec2(0.f, 520.f), Vec2(120.f, 130.), 10);
	CreateFlipbook(L"LINK_MOVELEFT", pAtlas, Vec2(0.f, 650.f), Vec2(120.f, 130.), 10);
	CreateFlipbook(L"LINK_MOVEUP", pAtlas, Vec2(0.f, 780.f), Vec2(120.f, 130.), 10);
	CreateFlipbook(L"LINK_MOVERIGHT", pAtlas, Vec2(0.f, 910.f), Vec2(120.f, 130.), 10);



	// FlipbookPlayer 컴포넌트 추가하기
	m_FlipbookPlayer = (CFlipbookPlayer*)AddComponent(new CFlipbookPlayer);
	m_FlipbookPlayer->AddFlipbook(IDLE_DOWN, CAssetMgr::GetInst()->FindFlipbook(L"LINK_IDLEDOWN"));
	m_FlipbookPlayer->AddFlipbook(IDLE_LEFT, CAssetMgr::GetInst()->FindFlipbook(L"LINK_IDLELEFT"));
	m_FlipbookPlayer->AddFlipbook(IDLE_UP,	 CAssetMgr::GetInst()->FindFlipbook(L"LINK_IDLEUP"));
	m_FlipbookPlayer->AddFlipbook(IDLE_RIGHT,CAssetMgr::GetInst()->FindFlipbook(L"LINK_IDLERIGHT"));

	m_FlipbookPlayer->AddFlipbook(MOVE_DOWN, CAssetMgr::GetInst()->FindFlipbook( L"LINK_MOVEDOWN"));
	m_FlipbookPlayer->AddFlipbook(MOVE_LEFT, CAssetMgr::GetInst()->FindFlipbook( L"LINK_MOVELEFT"));
	m_FlipbookPlayer->AddFlipbook(MOVE_UP, CAssetMgr::GetInst()->FindFlipbook(   L"LINK_MOVEUP"));
	m_FlipbookPlayer->AddFlipbook(MOVE_RIGHT, CAssetMgr::GetInst()->FindFlipbook(L"LINK_MOVERIGHT"));

	CSprite* pSprite = CAssetMgr::GetInst()->FindSprite(L"LINK_IDLERIGHT_1");
	pSprite->SetOffset(Vec2(1.f, 0.f));
}

void CPlayer::CreateFlipbook(const wstring& _FlipbookName, CTexture* _Atlas, Vec2 _LeftTop, Vec2 _Slice, int MaxFrame)
{
	// Sprite 생성하기
	for (int i = 0; i < MaxFrame; ++i)
	{
		CSprite* pSprite = new CSprite;
		pSprite->Create(_Atlas, Vec2(_LeftTop.x + (_Slice.x * i), _LeftTop.y), _Slice);

		wchar_t Key[50] = {};
		swprintf_s(Key, 50, (_FlipbookName + L"_%d").c_str(), i);
		CAssetMgr::GetInst()->AddSprite(Key, pSprite);
	}

	// Flipbook 생성하기
	CFlipbook* pFlipbook = new CFlipbook;

	for (int i = 0; i < MaxFrame; ++i)
	{
		wchar_t Key[50] = {};
		swprintf_s(Key, 50, (_FlipbookName + L"_%d").c_str(), i);
		pFlipbook->AddSprite(CAssetMgr::GetInst()->FindSprite(Key));
	}

	CAssetMgr::GetInst()->AddFlipbook(_FlipbookName, pFlipbook);
}

