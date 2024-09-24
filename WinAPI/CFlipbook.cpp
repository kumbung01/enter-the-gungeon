#include "pch.h"
#include "CFlipbook.h"

#include "CPathMgr.h"
#include "CSprite.h"

CFlipbook::CFlipbook()
    : CAsset(ASSET_TYPE::FLIPBOOK)
{
}

CFlipbook::~CFlipbook()
{
}

int CFlipbook::Save(const wstring& _RelativePath)
{
    wstring RelativePath = _RelativePath;
    CheckExt(L".flip", RelativePath);

    // ������ �ڽ��� ��� ����Ǵ����� �˰� ��
    SetRelativePath(RelativePath);

    // ���� ���� ���
    wstring strFilePath = CPathMgr::GetContentPath() + RelativePath;

    // Sprite �� Key, RelativePath �� ����
    FILE* File = nullptr;
    _wfopen_s(&File, strFilePath.c_str(), L"wb");

    size_t SpriteCount = m_Sprites.size();
    fwrite(&SpriteCount, sizeof(size_t), 1, File);

    for (size_t i = 0; i < m_Sprites.size(); ++i)
    {
        SaveAssetRef(m_Sprites[i], File);
    }

    fclose(File);

    return 0;
}

int CFlipbook::Load(const wstring& _RelativePath)
{
    wstring strFilePath = CPathMgr::GetContentPath();
    strFilePath += _RelativePath; 

    // Sprite �� Key, RelativePath �� ����
    FILE* File = nullptr;
    _wfopen_s(&File, strFilePath.c_str(), L"rb");

    size_t SpriteCount = 0;
    fread(&SpriteCount, sizeof(size_t), 1, File);

    for (size_t i = 0; i < SpriteCount; ++i)
    {
        CSprite* pSprite = (CSprite*)LoadAssetRef(File);
        m_Sprites.push_back(pSprite);
    }

    fclose(File);

    return S_OK;
}
