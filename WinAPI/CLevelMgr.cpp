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
	// ���� ����       
    CLevel* pLevel = new CLevel;

    // ������Ʈ 1�� �����غ���
    Vec2 vResolution = CEngine::GetInst()->GetResolution();

    CObj* pObject = new CObj;
    pObject->SetPos(vResolution.x / 2.f, vResolution.y / 2.f);
    pObject->SetScale(50.f, 50.f);    
    pLevel->AddObject(pObject);

    // ������Ʈ 1�� �� �����
    pObject = new CObj;
    pObject->SetPos(500.f, 500.f);
    pObject->SetScale(200.f, 200.f);
    pLevel->AddObject(pObject);

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
    m_CurLevel->Render();
}
