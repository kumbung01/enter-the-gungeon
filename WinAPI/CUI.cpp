#include "pch.h"
#include "CUI.h"

#include "CEngine.h"
#include "CSelectGDI.h"

#include "CKeyMgr.h"

CUI::CUI()
	: m_MouseHover(false)
{
}

CUI::~CUI()
{
}

void CUI::Tick()
{
	// ���� ��ǥ ����ϱ�
	m_FinalPos = GetPos();

	if (m_ParentUI)
	{
		m_FinalPos += m_ParentUI->GetFinalPos();
	}


	// ���콺�� UI ���� �ö�Դ��� üũ�ϱ�
	MouseHoverCheck();

	// �ڽ� UI Tick ȣ��
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->Tick();
	}
}

void CUI::Render()
{
	// GetPos() : �θ� UI �κ��� ��� ��ǥ, �θ� ���� UI ��� ���� ��ǥ
	// GetFinalPos() : ���� ��ǥ, �θ��� ��ġ�� �����ǰ� �ű⿡ �ڽ��� �����ǥ�� ���� ��

	Vec2 vPos = GetFinalPos();
	Vec2 vScale = GetScale();

	SELECT_PEN(PEN_TYPE::GREEN);
	SELECT_BRUSH(BRUSH_TYPE::HOLLOW);

	Rectangle( CEngine::GetInst()->GetSecondDC()
		, (int)vPos.x, (int)vPos.y
		, (int)(vPos.x + vScale.x)
		, (int)(vPos.y + vScale.y));
}

void CUI::MouseHoverCheck()
{
	Vec2 vMousePos = CKeyMgr::GetInst()->GetMousePos();

	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	if (vPos.x <= vMousePos.x && vMousePos.x <= vPos.x + vScale.x
		&& vPos.y <= vMousePos.y && vMousePos.y <= vPos.y + vScale.y)
	{
		m_MouseHover = true;
	}
	else
	{
		m_MouseHover = false;
	}
}
