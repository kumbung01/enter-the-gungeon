#pragma once

class CUI;


// ��� UI �� �߿��� � UI �� Focuse �������� �˻�
// Focuse ���� UI �� �̺�Ʈ ó���� �� �� �ֵ��� ��� UI �� ���� �� �˻��ϴ� ����
class CUIMgr
{
	SINGLE(CUIMgr);
private:
	CUI*	m_FocusedUI;	// ��Ŀ�� �Ǿ��ִ� UI
	CUI*	m_PriorityUI;	// ��Ŀ�� �Ǿ��ִ� UI ������ �ٽ� ���� �켱������ ���� UI

public:	
	void Tick();

private:
	CUI* GetPriorityUI(CUI* _ParentUI);

};

