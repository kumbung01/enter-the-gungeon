#pragma once


// ���α׷��� �ֻ��� ������
class CEngine
{
	SINGLE(CEngine);
private:
	HINSTANCE	m_hInst;		// ���μ��� �ּ�
	HWND		m_hWnd;			// ���� ������ �ڵ�
	POINT		m_Resolution;	// ���� ������ �ػ�
	
	UINT		m_FrameCount;


public:
	int Init(HINSTANCE _Inst, POINT _Resolution);
	void Progress();
};
