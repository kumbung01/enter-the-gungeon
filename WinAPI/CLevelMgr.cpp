#include "pch.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CEngine.h"

#include "CObj.h"


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
	// 레벨 제작       
    CLevel* pLevel = new CLevel;

    // 오브젝트 1개 생성해보기
    Vec2 vResolution = CEngine::GetInst()->GetResolution();

    CObj* pObject = new CObj;
    pObject->SetPos(vResolution.x / 2.f, vResolution.y / 2.f);
    pObject->SetScale(50.f, 50.f);    
    pLevel->AddObject(pObject);

    // 오브젝트 1개 더 만들기
    pObject = new CObj;
    pObject->SetPos(500.f, 500.f);
    pObject->SetScale(200.f, 200.f);
    pLevel->AddObject(pObject);

    // 생성한 레벨을 START 레벨 이자 현재 재생 중인 레벨로 설정하고
    // Begin 을 호출한다.
    m_CurLevel = m_arrLevel[(UINT)LEVEL_TYPE::START] = pLevel;
    m_CurLevel->Begin();
}

void CLevelMgr::Progress()
{
    if (nullptr == m_CurLevel)
        return;

    m_CurLevel->Tick();
    m_CurLevel->FinalTick();
    m_CurLevel->Render();
}
