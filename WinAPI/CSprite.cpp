#include "pch.h"
#include "CSprite.h"

#include "CPathMgr.h"
#include "CTexture.h"

CSprite::CSprite()
	: CAsset(ASSET_TYPE::SPRITE)
	, m_Atlas(nullptr)
{
}

CSprite::~CSprite()
{
}

void CSprite::Create(CTexture* _Atlas, Vec2 _LeftTop, Vec2 _Slice)
{
	m_Atlas = _Atlas;
	m_LeftTop = _LeftTop;
	m_Slice = _Slice;
}

int CSprite::Save(const wstring& _RelativePath)
{
	wstring strFilePath = CPathMgr::GetContentPath() + _RelativePath + L".sprite";

	FILE* File = nullptr;
	_wfopen_s(&File, strFilePath.c_str(), L"wb");

	// 가리키던 Atlas 텍스쳐의 키, 경로를 저장한다.
	m_Atlas->GetKey();
	m_Atlas->GetRelativePath();



	m_LeftTop;
	m_Slice;
	m_Offset;




	fclose(File);

	return S_OK;
}

int CSprite::Load(const wstring& _FilePath)
{
	return S_OK;
}