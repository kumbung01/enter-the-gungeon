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
	// ���� �����ȿ� �ִ� UI ���� �����´�.
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();

	// ������ �߰��� �ֻ��� �θ� UI ��
	const vector<CObj*>& vecUI = pCurLevel->GetObjects(LAYER_TYPE::UI);

	// ���콺 ���ʹ�ư�� ���� ��Ȳ üũ
	KEY_STATE LBtnState = CKeyMgr::GetInst()->GetKeyState(KEY::LBTN);

	for (size_t i = 0; i < vecUI.size(); ++i)
	{
		// UI ���̾ �ִ� ������Ʈ�� ��¥ UI ��ü���� Ȯ�� �� �ٿ�ĳ����
		CUI* pUI = dynamic_cast<CUI*>(vecUI[i]);
		assert(pUI);

		// �ֻ��� �θ� UI ����, ������ �ڽĵ� �� ���� �켱������ ���� UI �� ã�Ƽ� ��ȯ�Ѵ�.
		// pUI = GetPriorityUI(pUI);

		// UI �� ���ȴ��� Ȯ��
		if (LBtnState == KEY_STATE::TAP && pUI->IsMouseHover())
		{
			pUI->m_LBtnDown = true;
			pUI->MouseLBtnDown();
		}

		// UI �� Ŭ���ƴ��� üũ
		if (LBtnState == KEY_STATE::RELEASED)
		{
			if (pUI->IsMouseHover())
			{
				if(pUI->m_LBtnDown)
					pUI->MouseLBtnClikced();
				else
					pUI->MouseReleased();
			}

			// LBtn Ű�� �����Ǿ��� ������, ���� ���¸� �����Ѵ�.
			pUI->m_LBtnDown = false;
		}
	}
}

CUI* CUIMgr::GetPriorityUI(CUI* _ParentUI)
{
	return nullptr;
}
