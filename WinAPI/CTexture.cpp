#include "pch.h"
#include "CTexture.h"

#include "CEngine.h"

CTexture::CTexture()
	: CAsset(ASSET_TYPE::TEXTURE)
	, m_hBit(nullptr)
	, m_DC(nullptr)
	, m_BitmapInfo{}
{
}

CTexture::~CTexture()
{
	DeleteDC(m_DC);
	DeleteObject(m_hBit);
}


int CTexture::Load(const wstring& _FilePath)
{
	// ��ηο� �����ϴ� �̹��� ������ ��Ʈ�� ���·� �޸𸮿� �ε�
	m_hBit = (HBITMAP)LoadImage(nullptr, _FilePath.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);

	// ��Ʈ���� Ÿ������ ������ DC ����
	m_DC = CreateCompatibleDC(CEngine::GetInst()->GetMainDC());

	// ��Ʈ�ʰ� DC ����
	DeleteObject(SelectObject(m_DC, m_hBit));

	// ��Ʈ���� ������ �޾ƿ´�.
	GetObject(m_hBit, sizeof(BITMAP), &m_BitmapInfo);

	return S_OK;
}