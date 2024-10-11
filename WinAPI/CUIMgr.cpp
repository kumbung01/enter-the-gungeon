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

	const vector<CObj*>& vecUI = pCurLevel->GetObjects(LAYER_TYPE::UI);

	// ���콺 ���ʹ�ư�� ���� ��Ȳ üũ
	bool bLbtnDown = KEY_TAP(KEY::LBTN);

	for (size_t i = 0; i < vecUI.size(); ++i)
	{
		// UI ���̾ �ִ� ������Ʈ�� ��¥ UI ��ü���� Ȯ�� �� �ٿ�ĳ����
		CUI* pUI = dynamic_cast<CUI*>(vecUI[i]);
		assert(pUI);

		// UI �� ���ȴ��� Ȯ��
		if (bLbtnDown && pUI->IsMouseHover())
		{
			pUI->MouseLBtnDown();
		}
	}
}
