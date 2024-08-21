#pragma once


// 프로그램의 최상위 관리자
class CEngine
{
	SINGLE(CEngine);
private:
	HINSTANCE	m_hInst;		// 프로세스 주소
	HWND		m_hWnd;			// 메인 윈도우 핸들
	POINT		m_Resolution;	// 메인 윈도우 해상도
	HDC			m_hDC;			// Main DC(Device Context) 그리기 관련 관리자, 그리기 도구 집합체


	UINT		m_FrameCount;


public:
	HWND GetMainWndHwnd() { return m_hWnd; }

public:
	int Init(HINSTANCE _Inst, POINT _Resolution);
	void Progress();
};
