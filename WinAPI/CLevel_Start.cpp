#include "pch.h"
#include "CLevel_Start.h"

#include "CEngine.h"

#include "CPlayer.h"
#include "CMonster.h"
#include "CMissile.h"
#include "CPlatform.h"
#include "CMap.h"
#include "CCursor.h"
#include "CGun.h"
#include "CReloadUI.h"
#include "CRevolver.h"
#include "CMonsterRevolver.h"
#include "CMonsterShotgun.h"

#include "CCollisionMgr.h"
#include "CCollider.h"

#include "CTileMap.h"
#include "CPathMgr.h"
#include "CCamera.h"

#include "CAssetMgr.h"
#include "CSound.h"

CLevel_Start::CLevel_Start()
{

}

CLevel_Start::~CLevel_Start()
{

}

void CLevel_Start::Begin()
{
    ShowCursor(false);

    // 배경음 지정
    CSound* pBGM = CAssetMgr::GetInst()->LoadSound(L"BattleBGM", L"Sound\\BGM_Stage1.wav");
    if (nullptr != pBGM)
    {
        pBGM->SetVolume(70.f);
        //pBGM->PlayToBGM(true);
    }
    
    // 화면 해상도 
    Vec2 vResolution = CEngine::GetInst()->GetResolution();

    // Player 생성
    CPlayer* pPlayer = new CPlayer;
    pPlayer->SetName(L"Player");
    pPlayer->SetPos(vResolution.x / 2.f, 100.f);
    pPlayer->SetScale(50.f, 50.f);

    AddObject(pPlayer, LAYER_TYPE::PLAYER);

    CGun* gun = new CRevolver;
    gun->SetName(L"Revolver");
    gun->SetOwner(pPlayer);
    pPlayer->SetGun(gun);
    AddObject(gun, LAYER_TYPE::GUN);

    CReloadBar* ui = new CReloadBar;
    ui->SetOwner(pPlayer);
    pPlayer->SetReloadBar(ui);
    AddObject(ui, LAYER_TYPE::INGAME_UI);

    // Monster 생성
    CMonster* pMonster = new CMonster;
    pMonster->SetName(L"Monster");
    pMonster->SetPos(300.f, 120.f);
    pMonster->SetScale(100.f, 100.f);
    AddObject(pMonster, LAYER_TYPE::MONSTER);

    gun = new CMonsterShotgun;
    gun->SetOwner(pMonster);
    pMonster->SetGun(gun);
    gun->SetName(L"MonsterShotgun");
    AddObject(gun, LAYER_TYPE::GUN);


    pMonster = new CMonster;
    pMonster->SetName(L"Monster");
    pMonster->SetPos(1000.f, 500.f);
    pMonster->SetScale(100.f, 100.f);
    AddObject(pMonster, LAYER_TYPE::MONSTER);

    gun = new CMonsterRevolver;
    gun->SetOwner(pMonster);
    pMonster->SetGun(gun);
    gun->SetName(L"MonsterRevolver");
    AddObject(gun, LAYER_TYPE::GUN);


    //// Platform Object 추가
    CObj* pPlatform = new CPlatform;
    pPlatform->SetPos(vResolution.x / 2.f, (vResolution.y * 3.f) / 4.f);
    AddObject(pPlatform, LAYER_TYPE::TILE);


    auto pos = pPlatform->GetPos();
    pPlatform = new CPlatform;
    pPlatform->SetPos(pos + Vec2(350.f, 75.f));
    AddObject(pPlatform, LAYER_TYPE::TILE);

    // TileMap Object 추가
    CMap* pTileMap = new CMap;
    pTileMap->SetPos(Vec2(0.f, 0.f));
    wstring FilePath = CPathMgr::GetContentPath();
    //pTileMap->GetTileMap()->LoadTileMap(FilePath + L"TileMap\\Temp.tile");
    AddObject(pTileMap, LAYER_TYPE::TILE);

    // TileMap Object 추가
    pTileMap = new CMap;
    pTileMap->SetPos(Vec2(1000.f, 1000.f));
    AddObject(pTileMap, LAYER_TYPE::TILE);
    //pTileMap->GetTileMap()->LoadTileMap(FilePath + L"TileMap\\Temp.tile");

 /*   tTile* pTile = pTileMap->GetTileMap()->GetTileInfo(0, 0);
    pTile->ImgIdx = 5;
    pTile->isWall = true;
    AddObject(pTileMap, LAYER_TYPE::TILE);*/


    // Cursor 추가
    CCursor* pCursor = new CCursor;
    pCursor->SetPos(Vec2(0.f, 0.f));
    pCursor->SetScale(Vec2(50.f, 50.f));
    AddObject(pCursor, LAYER_TYPE::INGAME_UI);


    // 충돌 설정
    CCollisionMgr::GetInst()->CollisionCheckClear();
    CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER_OBJECT, LAYER_TYPE::MONSTER);
    CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::MONSTER);
    CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::MONSTER_OBJECT);
    CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::TILE);
    CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::MONSTER, LAYER_TYPE::TILE);
    CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER_OBJECT, LAYER_TYPE::TILE);
    CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::MONSTER_OBJECT, LAYER_TYPE::TILE);

    // Camera 효과
    CCamera::GetInst()->SetTarget(pPlayer);
    CCamera::GetInst()->SetState(CAMERA_STATE::FOLLOW_PLAYER);
    //CCamera::GetInst()->PostProcessEffect(HEART, 0.5f);  

    // 부모 CLevel 의 Begin 호출
    CLevel::Begin();
}

void CLevel_Start::Render()
{
    CLevel::Render();

    TextOut(CEngine::GetInst()->GetSecondDC(), 10, 10, L"Start Level", wcslen(L"Start Level"));
}

void CLevel_Start::End()
{
    DeleteAllObject();
}
