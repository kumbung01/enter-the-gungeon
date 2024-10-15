#include "pch.h"
#include "CPanelUI.h"

#include "CKeyMgr.h"


CPanelUI::CPanelUI()
{
}

CPanelUI::~CPanelUI()
{
}


void CPanelUI::Tick_UI()
{
	if (IsLBtnDown())
	{
		Vec2 vMousePos = CKeyMgr::GetInst()->GetMousePos();
		Vec2 vDiff = vMousePos - m_DownPos;

		Vec2 vPos = GetPos();
		vPos += vDiff;
		SetPos(vPos);

		m_DownPos = vMousePos;
	}
}

void CPanelUI::MouseLBtnDown()
{
	m_DownPos = CKeyMgr::GetInst()->GetMousePos();
}