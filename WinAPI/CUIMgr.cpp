#include "pch.h"
#include "CUIMgr.h"

#include "CLevelMgr.h"
#include "CLevel.h"
#include "CUI.h"

#include "CKeyMgr.h"

CUIMgr::CUIMgr()
	: m_FocusedUI(nullptr)
	, m_PriorityUI(nullptr)
{

}

CUIMgr::~CUIMgr()
{

}

void CUIMgr::Tick()
{
	// 현재 레벨안에 있는 UI 들을 가져온다.
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();

	const vector<CObj*>& vecUI = pCurLevel->GetObjects(LAYER_TYPE::UI);

	// 마우스 왼쪽버튼이 눌린 상황 체크
	bool bLbtnDown = KEY_TAP(KEY::LBTN);

	for (size_t i = 0; i < vecUI.size(); ++i)
	{
		// UI 레이어에 있는 오브젝트가 진짜 UI 객체인지 확인 및 다운캐스팅
		CUI* pUI = dynamic_cast<CUI*>(vecUI[i]);
		assert(pUI);

		// UI 가 눌렸는지 확인
		if (bLbtnDown && pUI->IsMouseHover())
		{
			pUI->MouseLBtnDown();
		}
	}
}
