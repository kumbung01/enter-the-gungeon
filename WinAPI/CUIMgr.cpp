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

	// 레벨에 추가된 최상위 부모 UI 들
	const vector<CObj*>& vecUI = pCurLevel->GetObjects(LAYER_TYPE::UI);

	// 마우스 왼쪽버튼이 눌린 상황 체크
	KEY_STATE LBtnState = CKeyMgr::GetInst()->GetKeyState(KEY::LBTN);

	for (size_t i = 0; i < vecUI.size(); ++i)
	{
		// UI 레이어에 있는 오브젝트가 진짜 UI 객체인지 확인 및 다운캐스팅
		CUI* pUI = dynamic_cast<CUI*>(vecUI[i]);
		assert(pUI);

		// 최상위 부모 UI 포함, 본인의 자식들 중 가장 우선순위가 높은 UI 를 찾아서 반환한다.
		// pUI = GetPriorityUI(pUI);

		// UI 가 눌렸는지 확인
		if (LBtnState == KEY_STATE::TAP && pUI->IsMouseHover())
		{
			pUI->m_LBtnDown = true;
			pUI->MouseLBtnDown();
		}

		// UI 가 클릭됐는지 체크
		if (LBtnState == KEY_STATE::RELEASED)
		{
			if (pUI->IsMouseHover())
			{
				if(pUI->m_LBtnDown)
					pUI->MouseLBtnClikced();
				else
					pUI->MouseReleased();
			}

			// LBtn 키가 해제되었기 때문에, 눌린 상태를 해제한다.
			pUI->m_LBtnDown = false;
		}
	}
}

CUI* CUIMgr::GetPriorityUI(CUI* _ParentUI)
{
	return nullptr;
}
