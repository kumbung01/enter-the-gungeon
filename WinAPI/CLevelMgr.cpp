#include "pch.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CLevel_Start.h"
#include "CLevel_Editor.h"
#include "CKeyMgr.h"



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
    m_arrLevel[(UINT)LEVEL_TYPE::START] = new CLevel_Start;
    m_arrLevel[(UINT)LEVEL_TYPE::EDITOR] = new CLevel_Editor;

    // ���� ������ CLevel_Start �� ����
    m_CurLevel = m_arrLevel[(UINT)LEVEL_TYPE::START];
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

void CLevelMgr::ChangeLevel(LEVEL_TYPE _NextLevel)
{
    // 1. ���� ������ �����Ϸ��� ������ �����ϸ� �ƹ��ϵ� ���Ͼ��.
    //if (m_CurLevel == m_arrLevel[(UINT)_NextLevel])
        //return;

    // 2. ���� ������ End �� ȣ���Ų��.
    m_CurLevel->End();

    // 3. ���� ��û�� ������ ���� ������ �����Ѵ�.
    m_CurLevel = m_arrLevel[(UINT)_NextLevel];

    // 3. ����� ������ Begin �� ȣ���Ų��.
    m_CurLevel->Begin();
}

CObj* CLevelMgr::FindObjectByName(LAYER_TYPE _Layer, const wstring& _Name)
{
    if (nullptr == m_CurLevel)
        return nullptr;

    return m_CurLevel->FindObjectByName(_Layer, _Name);
}