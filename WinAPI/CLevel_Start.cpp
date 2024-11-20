#include "pch.h"
#include "CLevel_Start.h"

#include "CEngine.h"

#include "CPlayer.h"
#include "CMonster.h"
#include "CMissile.h"
#include "CPlatform.h"
#include "CMap.h"
#include "CStartRoom.h"
#include "CRoom1.h"
#include "CCorridor.h"
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

void CLevel_Start::LoadAssets()
{
    // player flipbook
    CAssetMgr::GetInst()->LoadFlipbook(L"rogue_idle", L"Flipbook\\SpaceRogue\\rogue_idle.flip");
    CAssetMgr::GetInst()->LoadFlipbook(L"rogue_idle_back", L"Flipbook\\SpaceRogue\\rogue_idle_back.flip");
    CAssetMgr::GetInst()->LoadFlipbook(L"rogue_idle_backwards", L"Flipbook\\SpaceRogue\\rogue_idle_backwards.flip");
    CAssetMgr::GetInst()->LoadFlipbook(L"rogue_idle_backwards_hands2", L"Flipbook\\SpaceRogue\\rogue_idle_backwards_hands2.flip");
    CAssetMgr::GetInst()->LoadFlipbook(L"rogue_idle_back_hands", L"Flipbook\\SpaceRogue\\rogue_idle_back_hands.flip");
    CAssetMgr::GetInst()->LoadFlipbook(L"rogue_idle_back_hand_left", L"Flipbook\\SpaceRogue\\rogue_idle_back_hand_left.flip");
    CAssetMgr::GetInst()->LoadFlipbook(L"rogue_idle_back_hand_right", L"Flipbook\\SpaceRogue\\rogue_idle_back_hand_right.flip");
    CAssetMgr::GetInst()->LoadFlipbook(L"rogue_idle_front", L"Flipbook\\SpaceRogue\\rogue_idle_front.flip");
    CAssetMgr::GetInst()->LoadFlipbook(L"rogue_idle_front_hands", L"Flipbook\\SpaceRogue\\rogue_idle_front_hands.flip");
    CAssetMgr::GetInst()->LoadFlipbook(L"rogue_idle_front_hand_left", L"Flipbook\\SpaceRogue\\rogue_idle_front_hand_left.flip");
    CAssetMgr::GetInst()->LoadFlipbook(L"rogue_idle_front_hand_right", L"Flipbook\\SpaceRogue\\rogue_idle_front_hand_right.flip");
    CAssetMgr::GetInst()->LoadFlipbook(L"rogue_idle_hands", L"Flipbook\\SpaceRogue\\rogue_idle_hands.flip");
    CAssetMgr::GetInst()->LoadFlipbook(L"rogue_idle_hands2", L"Flipbook\\SpaceRogue\\rogue_idle_hands2.flip");

    CAssetMgr::GetInst()->LoadFlipbook(L"rogue_run_front", L"Flipbook\\SpaceRogue\\rogue_run_front.flip");
    CAssetMgr::GetInst()->LoadFlipbook(L"rogue_run_front_hands", L"Flipbook\\SpaceRogue\\rogue_run_front_hands.flip");
    CAssetMgr::GetInst()->LoadFlipbook(L"rogue_run_front_hands2", L"Flipbook\\SpaceRogue\\rogue_run_front_hands2.flip");
    CAssetMgr::GetInst()->LoadFlipbook(L"rogue_run_front_hands_left", L"Flipbook\\SpaceRogue\\rogue_run_front_hands_left.flip");
    CAssetMgr::GetInst()->LoadFlipbook(L"rogue_run_back", L"Flipbook\\SpaceRogue\\rogue_run_back.flip");
    CAssetMgr::GetInst()->LoadFlipbook(L"rogue_run_back_hands", L"Flipbook\\SpaceRogue\\rogue_run_back_hands.flip");
    CAssetMgr::GetInst()->LoadFlipbook(L"rogue_run_back_hands2", L"Flipbook\\SpaceRogue\\rogue_run_back_hands2.flip");
    CAssetMgr::GetInst()->LoadFlipbook(L"rogue_run_back_hands_left", L"Flipbook\\SpaceRogue\\rogue_run_back_hands_left.flip");
    CAssetMgr::GetInst()->LoadFlipbook(L"rogue_run_backward", L"Flipbook\\SpaceRogue\\rogue_run_backward.flip");
    CAssetMgr::GetInst()->LoadFlipbook(L"rogue_run_backward_hands2", L"Flipbook\\SpaceRogue\\rogue_run_backward_hands2.flip");
    CAssetMgr::GetInst()->LoadFlipbook(L"rogue_run_forward", L"Flipbook\\SpaceRogue\\rogue_run_forward.flip");
    CAssetMgr::GetInst()->LoadFlipbook(L"rogue_run_forward_hands", L"Flipbook\\SpaceRogue\\rogue_run_forward_hands.flip");
    CAssetMgr::GetInst()->LoadFlipbook(L"rogue_run_forward_hands2", L"Flipbook\\SpaceRogue\\rogue_run_forward_hands2.flip");

    CAssetMgr::GetInst()->LoadFlipbook(L"rogue_dodge_back", L"Flipbook\\SpaceRogue\\rogue_dodge_back.flip");
    CAssetMgr::GetInst()->LoadFlipbook(L"rogue_dodge_front", L"Flipbook\\SpaceRogue\\rogue_dodge_front.flip");
    CAssetMgr::GetInst()->LoadFlipbook(L"rogue_dodge_left", L"Flipbook\\SpaceRogue\\rogue_dodge_left.flip");
    CAssetMgr::GetInst()->LoadFlipbook(L"rogue_dodge_left_back", L"Flipbook\\SpaceRogue\\rogue_dodge_left_back.flip");

    // gun flipbook
    CAssetMgr::GetInst()->LoadFlipbook(L"bulletbro_revolver_green_idle", L"Flipbook\\Weapon\\bulletbro_revolver_green_idle.flip");
    CAssetMgr::GetInst()->LoadFlipbook(L"bulletbro_revolver_green_enemy_charge", L"Flipbook\\Weapon\\bulletbro_revolver_green_enemy_charge.flip");
    CAssetMgr::GetInst()->LoadFlipbook(L"bulletbro_revolver_green_fire", L"Flipbook\\Weapon\\bulletbro_revolver_green_fire.flip");

    CAssetMgr::GetInst()->LoadFlipbook(L"shotgun_idle", L"Flipbook\\Weapon\\shotgun_idle.flip");
    CAssetMgr::GetInst()->LoadFlipbook(L"shotgun_enemy_fire", L"Flipbook\\Weapon\\shotgun_enemy_fire.flip");
    CAssetMgr::GetInst()->LoadFlipbook(L"shotgun_fire", L"Flipbook\\Weapon\\shotgun_fire.flip");

    // monster flipbook
    CAssetMgr::GetInst()->LoadFlipbook(L"bullet_cover_left_idle", L"Flipbook\\BulletMan\\bullet_cover_left_idle.flip");
    CAssetMgr::GetInst()->LoadFlipbook(L"bullet_cover_left_leap", L"Flipbook\\BulletMan\\bullet_cover_left_leap.flip");
    CAssetMgr::GetInst()->LoadFlipbook(L"bullet_cover_right_idle", L"Flipbook\\BulletMan\\bullet_cover_right_idle.flip");
    CAssetMgr::GetInst()->LoadFlipbook(L"bullet_cover_right_leap", L"Flipbook\\BulletMan\\bullet_cover_right_leap.flip");
    CAssetMgr::GetInst()->LoadFlipbook(L"bullet_death_back_south", L"Flipbook\\BulletMan\\bullet_death_back_south.flip");
    CAssetMgr::GetInst()->LoadFlipbook(L"bullet_death_front_north", L"Flipbook\\BulletMan\\bullet_death_front_north.flip");
    CAssetMgr::GetInst()->LoadFlipbook(L"bullet_death_left_back", L"Flipbook\\BulletMan\\bullet_death_left_back.flip");
    CAssetMgr::GetInst()->LoadFlipbook(L"bullet_death_left_front", L"Flipbook\\BulletMan\\bullet_death_left_front.flip");
    CAssetMgr::GetInst()->LoadFlipbook(L"bullet_death_left_side", L"Flipbook\\BulletMan\\bullet_death_left_side.flip");
    CAssetMgr::GetInst()->LoadFlipbook(L"bullet_death_right_back", L"Flipbook\\BulletMan\\bullet_death_right_back.flip");
    CAssetMgr::GetInst()->LoadFlipbook(L"bullet_death_right_front", L"Flipbook\\BulletMan\\bullet_death_right_front.flip");
    CAssetMgr::GetInst()->LoadFlipbook(L"bullet_death_right_side", L"Flipbook\\BulletMan\\bullet_death_right_side.flip");
    CAssetMgr::GetInst()->LoadFlipbook(L"bullet_die_left", L"Flipbook\\BulletMan\\bullet_die_left.flip");
    CAssetMgr::GetInst()->LoadFlipbook(L"bullet_die_left_back", L"Flipbook\\BulletMan\\bullet_die_left_back.flip");
    CAssetMgr::GetInst()->LoadFlipbook(L"bullet_die_right", L"Flipbook\\BulletMan\\bullet_die_right.flip");
    CAssetMgr::GetInst()->LoadFlipbook(L"bullet_die_right_back", L"Flipbook\\BulletMan\\bullet_die_right_back.flip");
    CAssetMgr::GetInst()->LoadFlipbook(L"bullet_hit_back_left", L"Flipbook\\BulletMan\\bullet_hit_back_left.flip");
    CAssetMgr::GetInst()->LoadFlipbook(L"bullet_hit_back_right", L"Flipbook\\BulletMan\\bullet_hit_back_right.flip");
    CAssetMgr::GetInst()->LoadFlipbook(L"bullet_hit_left", L"Flipbook\\BulletMan\\bullet_hit_left.flip");
    CAssetMgr::GetInst()->LoadFlipbook(L"bullet_hit_right", L"Flipbook\\BulletMan\\bullet_hit_right.flip");
    CAssetMgr::GetInst()->LoadFlipbook(L"bullet_idle_back", L"Flipbook\\BulletMan\\bullet_idle_back.flip");
    CAssetMgr::GetInst()->LoadFlipbook(L"bullet_idle_left", L"Flipbook\\BulletMan\\bullet_idle_left.flip");
    CAssetMgr::GetInst()->LoadFlipbook(L"bullet_idle_right", L"Flipbook\\BulletMan\\bullet_idle_right.flip");
    CAssetMgr::GetInst()->LoadFlipbook(L"bullet_pitfall_right", L"Flipbook\\BulletMan\\bullet_pitfall_right.flip");
    CAssetMgr::GetInst()->LoadFlipbook(L"bullet_run_left", L"Flipbook\\BulletMan\\bullet_run_left.flip");
    CAssetMgr::GetInst()->LoadFlipbook(L"bullet_run_left_back", L"Flipbook\\BulletMan\\bullet_run_left_back.flip");
    CAssetMgr::GetInst()->LoadFlipbook(L"bullet_run_right", L"Flipbook\\BulletMan\\bullet_run_right.flip");
    CAssetMgr::GetInst()->LoadFlipbook(L"bullet_run_right_back", L"Flipbook\\BulletMan\\bullet_run_right_back.flip");
    CAssetMgr::GetInst()->LoadFlipbook(L"bullet_shooting_left", L"Flipbook\\BulletMan\\bullet_shooting_left.flip");
    CAssetMgr::GetInst()->LoadFlipbook(L"bullet_shooting_right", L"Flipbook\\BulletMan\\bullet_shooting_right.flip");
    CAssetMgr::GetInst()->LoadFlipbook(L"bullet_spawn", L"Flipbook\\BulletMan\\bullet_spawn.flip");
    CAssetMgr::GetInst()->LoadFlipbook(L"bullet_surprise_left", L"Flipbook\\BulletMan\\bullet_surprise_left.flip");
    CAssetMgr::GetInst()->LoadFlipbook(L"bullet_surprise_right", L"Flipbook\\BulletMan\\bullet_surprise_right.flip");
    // tilemap
    CAssetMgr::GetInst()->LoadTexture(L"TileMapAtlas", L"Texture\\CastleTile.png");

}

void CLevel_Start::Begin()
{
    printf("clevel::begin() starts\n");
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
    pPlayer->SetPos(0.f, 0.f);
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

#if 0
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
#endif

#if 0
    //// Platform Object 추가
    CObj* pPlatform = new CPlatform;
    pPlatform->SetPos(vResolution.x / 2.f, (vResolution.y * 3.f) / 4.f);
    AddObject(pPlatform, LAYER_TYPE::TILE);


    auto pos = pPlatform->GetPos();
    pPlatform = new CPlatform;
    pPlatform->SetPos(pos + Vec2(350.f, 75.f));
    AddObject(pPlatform, LAYER_TYPE::TILE);
#endif

    float mod = TILE_SIZE * 2.5f;
    
    // TileMap Object 추가
    CMap* pTileMap = new CStartRoom(0.f, 0.f);
    wstring FilePath = CPathMgr::GetContentPath();
    //pTileMap->GetTileMap()->LoadTileMap(FilePath + L"TileMap\\Temp.tile");
    AddObject(pTileMap, LAYER_TYPE::TILE);

    {
        float x = 6.5f * mod;
        float y = 12.5f * mod;

        AddObject(new CCorridor(x, y, 10, 3, true), LAYER_TYPE::TILE);
    }

    {
        float x = 18.f * mod;
        float y = 32.5f * mod;

        AddObject(new CRoom1(x, y), LAYER_TYPE::TILE);
    }

    // TileMap Object 추가

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
    CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER_OBJECT,  LAYER_TYPE::MONSTER);
    CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER,         LAYER_TYPE::MONSTER);
    CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER,         LAYER_TYPE::MONSTER_OBJECT);
    CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER,         LAYER_TYPE::TILE);
    CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER,         LAYER_TYPE::WALL);
    CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::MONSTER,        LAYER_TYPE::WALL);
    CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::MONSTER,        LAYER_TYPE::MONSTER);
    CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER_OBJECT,  LAYER_TYPE::WALL);
    CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::MONSTER_OBJECT, LAYER_TYPE::WALL);

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
    printf("clevel::end()\n");
    DeleteAllObject();
}
