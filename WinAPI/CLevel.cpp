#include "pch.h"
#include "CLevel.h"

#include "CObj.h"

CLevel::CLevel()
{
}

CLevel::~CLevel()
{
	Delete_Vector(m_vecObjects);
}

void CLevel::Begin()
{
	for (size_t i = 0; i < m_vecObjects.size(); ++i)
	{
		m_vecObjects[i]->Begin();
	}	
}

void CLevel::Tick()
{
	for (size_t i = 0; i < m_vecObjects.size(); ++i)
	{
		m_vecObjects[i]->Tick();
	}
}

void CLevel::FinalTick()
{
	for (size_t i = 0; i < m_vecObjects.size(); ++i)
	{
		m_vecObjects[i]->FinalTick();
	}
}

void CLevel::Render()
{
	for (size_t i = 0; i < m_vecObjects.size(); ++i)
	{
		m_vecObjects[i]->Render();
	}
}