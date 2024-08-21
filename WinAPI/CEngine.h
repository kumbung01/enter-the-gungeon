#pragma once


// ���α׷��� �ֻ��� ������
class CEngine
{
	SINGLE(CEngine);
private:
	HINSTANCE	m_hInst;		// ���μ��� �ּ�
	HWND		m_hWnd;			// ���� ������ �ڵ�
	POINT		m_Resolution;	// ���� ������ �ػ�
	HDC			m_hDC;			// Main DC(Device Context) �׸��� ���� ������, �׸��� ���� ����ü


	UINT		m_FrameCount;


public:
	HWND GetMainWndHwnd() { return m_hWnd; }

public:
	int Init(HINSTANCE _Inst, POINT _Resolution);
	void Progress();
};
