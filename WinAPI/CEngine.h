#pragma once

// ���α׷��� �ֻ��� ������
class CEngine
{
	SINGLE(CEngine);
private:
	HINSTANCE	m_hInst;		// ���μ��� �ּ�
	HWND		m_hWnd;			// ���� ������ �ڵ�
	Vec2		m_Resolution;	// ���� ������ �ػ�
	HDC			m_hDC;			// Main DC(Device Context) �׸��� ���� ������, �׸��� ���� ����ü

	HDC			m_hSecondDC;	// �ι�° ���ۿ� �׸��� �׸����� ������ ���ο� DC
	HBITMAP		m_hSecondBitmap;// ������۸��� ���� �ι�° ����

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
