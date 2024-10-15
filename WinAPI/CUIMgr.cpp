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
	vector<CObj*>& vecUI = pCurLevel->m_vecObjects[(UINT)LAYER_TYPE::UI];

	// ���콺 ���ʹ�ư�� ���� ��Ȳ üũ
	KEY_STATE LBtnState = CKeyMgr::GetInst()->GetKeyState(KEY::LBTN);

	// reverse itertor �� �̿��ؼ� vector �� �������� ��ȸ�Ѵ�.
	vector<CObj*>::reverse_iterator riter = vecUI.rbegin();
	for (; riter != vecUI.rend(); ++riter)
	{
		// UI ���̾ �ִ� ������Ʈ�� ��¥ UI ��ü���� Ȯ�� �� �ٿ�ĳ����
		CUI* pParentUI = dynamic_cast<CUI*>((*riter));
		assert(pParentUI);

		// �ֻ��� �θ� UI ����, ������ �ڽĵ� �� ���� �켱������ ���� UI �� ã�Ƽ� ��ȯ�Ѵ�.
		CUI* pPriorityUI = GetPriorityUI(pParentUI);
		if (nullptr == pPriorityUI)
		{
			ReleaseCheck(pParentUI);
			continue;
		}

		// UI �� ���ȴ��� Ȯ��
		if (LBtnState == KEY_STATE::TAP)
		{
			pPriorityUI->m_LBtnDown = true;
			pPriorityUI->MouseLBtnDown();

			// vector ���� ���� �� ���� �ڷ� �����ش�.
			vecUI.erase((++riter).base());
			vecUI.push_back(pParentUI);
			break;
		}

		// UI �� Ŭ���ƴ��� üũ
		if (LBtnState == KEY_STATE::RELEASED)
		{			
			if(pPriorityUI->m_LBtnDown)
				pPriorityUI->MouseLBtnClikced();
			else
				pPriorityUI->MouseReleased();

			// LBtn Ű�� �����Ǿ��� ������, ���� ���¸� �����Ѵ�.			
			ReleaseCheck(pParentUI);
		}
	}
}

CUI* CUIMgr::GetPriorityUI(CUI* _ParentUI)
{
	CUI* pPriorityUI = nullptr;

	// Queue ������ �� List
	static list<CUI*> queue;
	queue.clear();

	// �ֻ��� �θ� UI �Է�
	queue.push_back(_ParentUI);

	// Queue �� ������� �ʴٸ� �ݺ��� ����
	while (!queue.empty())
	{
		CUI* pUI = queue.front();
		queue.pop_front();

		for (size_t i = 0; i < pUI->m_vecChildUI.size(); ++i)
		{
			queue.push_back(pUI->m_vecChildUI[i]);
		}

		if (pUI->IsMouseHover())
			pPriorityUI = pUI;
	}

	return pPriorityUI;
}


void CUIMgr::ReleaseCheck(CUI* _UI)
{
	// Queue ������ �� List
	static list<CUI*> queue;
	queue.clear();

	// �ֻ��� �θ� UI �Է�
	queue.push_back(_UI);

	// Queue �� ������� �ʴٸ� �ݺ��� ����
	while (!queue.empty())
	{
		CUI* pUI = queue.front();
		queue.pop_front();

		for (size_t i = 0; i < pUI->m_vecChildUI.size(); ++i)
		{
			queue.push_back(pUI->m_vecChildUI[i]);
		}
				
		if(KEY_RELEASED(KEY::LBTN))
			pUI->m_LBtnDown = false;
	}
}
