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
	// 경로로에 존재하는 이미지 파일을 비트맵 형태로 메모리에 로딩
	m_hBit = (HBITMAP)LoadImage(nullptr, _FilePath.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);

	// 비트맵을 타겟으로 지정할 DC 생성
	m_DC = CreateCompatibleDC(CEngine::GetInst()->GetMainDC());

	// 비트맵과 DC 연결
	DeleteObject(SelectObject(m_DC, m_hBit));

	// 비트맵의 정보를 받아온다.
	GetObject(m_hBit, sizeof(BITMAP), &m_BitmapInfo);

	return S_OK;
}