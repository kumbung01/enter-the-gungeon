#include "pch.h"
#include "CLevel_Start.h"

#include "CEngine.h"

#include "CPlayer.h"
#include "CMonster.h"
#include "CMissile.h"
#include "CPlatform.h"
#include "CMap.h"

#include "CCollisionMgr.h"
#include "CCollider.h"

#include "CTileMap.h"

CLevel_Start::CLevel_Start()
{

}

CLevel_Start::~CLevel_Start()
{

}



void CLevel_Start::Begin()
{
    // ȭ�� �ػ� 
    Vec2 vResolution = CEngine::GetInst()->GetResolution();

    // Player ����
    CObj* pObject = new CPlayer;
    pObject->SetName(L"Player");
    pObject->SetPos(vResolution.x / 2.f, 100.f);
    pObject->SetScale(50.f, 50.f);

    AddObject(pObject, LAYER_TYPE::PLAYER);

    // Monster ����
    CMonster* pMonster = new CMonster;
    pMonster->SetName(L"Monster");
    pMonster->SetPos(300.f, 120.f);
    pMonster->SetScale(100.f, 100.f);
    pMonster->SetDistance(200.f);
    pMonster->SetSpeed(300.f);
    AddObject(pMonster, LAYER_TYPE::MONSTER);

    pMonster = new CMonster;
    pMonster->SetName(L"Monster");
    pMonster->SetPos(1000.f, 120.f);
    pMonster->SetScale(100.f, 100.f);
    pMonster->SetDistance(200.f);
    pMonster->SetSpeed(300.f);
    AddObject(pMonster, LAYER_TYPE::MONSTER);

    // Platform Object �߰�
    CObj* pPlatform = new CPlatform;
    pPlatform->SetPos(vResolution.x / 2.f, (vResolution.y * 3.f) / 4.f);
    AddObject(pPlatform, LAYER_TYPE::TILE);

    // TileMap Object �߰�
    CMap* pTileMap = new CMap;
    pTileMap->SetPos(Vec2(0.f, 0.f));
    pTileMap->GetTileMap()->LoadTileMap(L"TileMap\\Temp.tile");
    AddObject(pTileMap, LAYER_TYPE::TILE);

    // TileMap Object �߰�
    pTileMap = new CMap;
    pTileMap->SetPos(Vec2(1000.f, 1000.f));
    pTileMap->GetTileMap()->LoadTileMap(L"TileMap\\Temp.tile");
    AddObject(pTileMap, LAYER_TYPE::TILE);


    // �浹 ����
    CCollisionMgr::GetInst()->CollisionCheckClear();
    CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER_OBJECT, LAYER_TYPE::MONSTER);
    CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::MONSTER);
    CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::TILE);

    // �θ� CLevel �� Begin ȣ��
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
