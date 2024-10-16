#include "pch.h"
#include "CSoundMgr.h"

#include "CEngine.h"
#include "CSound.h"

CSoundMgr::CSoundMgr()
    : m_SoundeDevice(nullptr)
    , m_pBGM(nullptr)
{

}

CSoundMgr::~CSoundMgr()
{

}

int CSoundMgr::Init()
{
	if (FAILED(DirectSoundCreate8(NULL, &m_SoundeDevice, NULL)))
	{
		MessageBox(NULL, L"���� ����̽� ���� ����", L"SYSTEM ERROR", MB_OK);
		return false;
	}

	// ���� �������� ����
	HWND hWnd = CEngine::GetInst()->GetMainWndHwnd();
	if (FAILED(m_SoundeDevice->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE)))
	{
		MessageBox(NULL, L"���� �Ŵ��� �ʱ�ȭ ����", L"SYSTEM ERROR", MB_OK);
		return false;
	}

	return true;
}

void CSoundMgr::RegisterToBGM(CSound* _pSound)
{
	if (m_pBGM != nullptr)
		m_pBGM->Stop(true);

	m_pBGM = _pSound;
}
