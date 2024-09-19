#include "pch.h"
#include "CSprite.h"

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

int CSprite::Load(const wstring& _FilePath)
{
	return S_OK;
}