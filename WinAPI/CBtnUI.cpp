#include "pch.h"
#include "CBtnUI.h"

#include "CEngine.h"
#include "CSelectGDI.h"

CBtnUI::CBtnUI()
{
}

CBtnUI::~CBtnUI()
{
}

void CBtnUI::Tick_UI()
{

}

void CBtnUI::Render_UI()
{
	Vec2 vPos = GetFinalPos();
	Vec2 vScale = GetScale();

	SELECT_PEN(PEN_TYPE::GREEN);

	HBRUSH hBrush = CreateSolidBrush(RGB(143, 36, 32));
	HDC dc = CEngine::GetInst()->GetSecondDC();

	HBRUSH hPrevBrush = (HBRUSH)SelectObject(dc, hBrush);

	Rectangle(dc
		, (int)vPos.x, (int)vPos.y
		, (int)(vPos.x + vScale.x)
		, (int)(vPos.y + vScale.y));

	SelectObject(dc, hPrevBrush);
	DeleteObject(hBrush);
}

void CBtnUI::MouseLBtnClikced()
{

}