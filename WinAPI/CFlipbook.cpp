#include "pch.h"
#include "CFlipbook.h"

CFlipbook::CFlipbook()
    : CAsset(ASSET_TYPE::FLIPBOOK)
{
}

CFlipbook::~CFlipbook()
{
}

int CFlipbook::Save(const wstring& _RelativePath)
{
    // Sprite �� Key, RelativePath �� ����


    return 0;
}

int CFlipbook::Load(const wstring& _RelativePath)
{
    return 0;
}
