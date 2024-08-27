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

	HPEN		m_Pen[(UINT)PEN_TYPE::END];
	HBRUSH		m_Brush[(UINT)BRUSH_TYPE::END];

	class CLevel* m_Level;


public:
	HWND GetMainWndHwnd() { return m_hWnd; }
	HPEN GetPen(PEN_TYPE _Type) { return m_Pen[(UINT)_Type]; }
	HBRUSH GetBrush(BRUSH_TYPE _Type) { return m_Brush[(UINT)_Type]; }
	HDC GetMainDC() { return m_hDC; }


public:
	int Init(HINSTANCE _Inst, POINT _Resolution);
	void Progress();

private:
	void CreateGDIObject();
};
