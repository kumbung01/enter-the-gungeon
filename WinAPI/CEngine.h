#pragma once

// 프로그램의 최상위 관리자
class CEngine
{
	SINGLE(CEngine);
private:
	HINSTANCE	m_hInst;		// 프로세스 주소
	HWND		m_hWnd;			// 메인 윈도우 핸들
	Vec2		m_Resolution;	// 메인 윈도우 해상도
	HDC			m_hDC;			// Main DC(Device Context) 그리기 관련 관리자, 그리기 도구 집합체

	HDC			m_hSecondDC;	// 두번째 버퍼에 그림을 그리도록 설정한 새로운 DC
	HBITMAP		m_hSecondBitmap;// 더블버퍼링을 위한 두번째 버퍼

	HPEN		m_Pen[(UINT)PEN_TYPE::END];
	HBRUSH		m_Brush[(UINT)BRUSH_TYPE::END];

public:
	HWND GetMainWndHwnd() { return m_hWnd; }
	Vec2 GetResolution() { return m_Resolution; }
	HPEN GetPen(PEN_TYPE _Type) { return m_Pen[(UINT)_Type]; }
	HBRUSH GetBrush(BRUSH_TYPE _Type) { return m_Brush[(UINT)_Type]; }
	HDC GetMainDC() { return m_hDC; }
	HDC GetSecondDC() { return m_hSecondDC; }

	void ChangeWindowSize(Vec2 _vResolution);


public:
	int Init(HINSTANCE _Inst, POINT _Resolution);
	void Progress();

private:
	void CreateGDIObject();
	void CreateSecondBuffer();
};
