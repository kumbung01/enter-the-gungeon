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
    // Sprite 의 Key, RelativePath 를 저장


    return 0;
}

int CFlipbook::Load(const wstring& _RelativePath)
{
    return 0;
}
