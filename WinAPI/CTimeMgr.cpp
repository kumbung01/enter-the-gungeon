#include "pch.h"
#include "CTimeMgr.h"

CTimeMgr::CTimeMgr()
	: m_Frequency{}
	, m_PrevCount{}
	, m_CurCount{}
	, m_FPS(0)
	, m_DT(0.f)
{
}

CTimeMgr::~CTimeMgr()
{

}

void CTimeMgr::Init()
{
	//QueryPerformanceCounter();
	//QueryPerformanceFrequency();
}

void CTimeMgr::Tick()
{
	
}
