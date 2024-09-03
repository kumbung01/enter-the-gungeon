#include "pch.h"
#include "CObj.h"

#include "CEngine.h"
#include "CComponent.h"

CObj::CObj()
	: m_Pos{}
	, m_Scale{}
{	
}

CObj::~CObj()
{
}

void CObj::Begin()
{

}

void CObj::FinalTick()
{
	for (size_t i = 0; i < m_Component.size(); ++i)
	{
		m_Component[i]->FinalTick();
	}
}

void CObj::Render()
{
	HDC dc = CEngine::GetInst()->GetSecondDC();

	Rectangle(dc
		, m_Pos.x - m_Scale.x / 2
		, m_Pos.y - m_Scale.y / 2
		, m_Pos.x + m_Scale.x / 2
		, m_Pos.y + m_Scale.y / 2);
}

CComponent* CObj::AddComponent(CComponent* _Component)
{
	m_Component.push_back(_Component);

	_Component->m_Owner = this;

	return _Component;
}
