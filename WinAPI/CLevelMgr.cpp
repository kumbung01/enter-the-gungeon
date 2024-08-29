#include "pch.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CEngine.h"

#include "CPlayer.h"
#include "CMonster.h"
#include "CMissile.h"


CLevelMgr::CLevelMgr()
    : m_arrLevel{}
    , m_CurLevel(nullptr)
{

}

CLevelMgr::~CLevelMgr()
{
    Delete_Array(m_arrLevel);
}

void CLevelMgr::Init()
{
    Vec2 vResolution = CEngine::GetInst()->GetResolution();

	// ���� ����       
    CLevel* pLevel = new CLevel;

    // Player ����
    CObj* pObject = new CPlayer;
    pObject->SetPos(vResolution.x / 2.f, vResolution.y / 2.f);
    pObject->SetScale(50.f, 50.f);    
    pLevel->AddObject(pObject);

    // Monster ����
    CMonster* pMonster = new CMonster;
    pMonster->SetPos(600.f, 300.f);
    pMonster->SetScale(100.f, 100.f);

    pMonster->SetDistance(200.f);
    pMonster->SetSpeed(300.f);

    pLevel->AddObject(pMonster);


    //// Missile �߰�
    //CMissile* pMissile = new CMissile;
    //pMissile->SetSpeed(500.f);   

    //pMissile->SetPos(vResolution.x / 2.f, vResolution.y / 2.f);
    //pMissile->SetScale(10.f, 10.f);
    //pLevel->AddObject(pMissile);


    // ������ ������ START ���� ���� ���� ��� ���� ������ �����ϰ�
    // Begin �� ȣ���Ѵ�.
    m_CurLevel = m_arrLevel[(UINT)LEVEL_TYPE::START] = pLevel;
    m_CurLevel->Begin();
}

void CLevelMgr::Progress()
{
    if (nullptr == m_CurLevel)
        return;

    m_CurLevel->Tick();
    m_CurLevel->FinalTick();   
}

void CLevelMgr::Render()
{
    m_CurLevel->Render();
}