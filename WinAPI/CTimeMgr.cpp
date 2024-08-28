#include "pch.h"
#include "CTimeMgr.h"

CTimeMgr::CTimeMgr()
	: m_Frequency{}
	, m_PrevCount{}
	, m_CurCount{}
	, m_FPS(0)
	, m_DT(0.f)
	, m_Time(0.f)
{
}

CTimeMgr::~CTimeMgr()
{

}

void CTimeMgr::Init()
{
	// 1�ʿ� 1000 ī���� -> �ʴ� ī���� ���� �ʹ� ����
	//GetTickCount();

	// �����Ӱ� ������ ������ �ð�
	QueryPerformanceFrequency(&m_Frequency); // �ʴ� ī���� �� (õ��)
	QueryPerformanceCounter(&m_PrevCount);
}

void CTimeMgr::Tick()
{	
	// ������� Count ��
	QueryPerformanceCounter(&m_CurCount);

	m_DT = (float)(m_CurCount.QuadPart - m_PrevCount.QuadPart) / (float)m_Frequency.QuadPart;

	m_PrevCount = m_CurCount;


	++m_FPS;
	m_Time += m_DT;

	if (1.f <= m_Time)
	{
		m_Time -= 1.f;		
	}
}
