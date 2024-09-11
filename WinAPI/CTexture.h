#pragma once
#include "CAsset.h"
#include <string>

class CTexture :
    public CAsset
{
private:
    HBITMAP     m_hBit;
    HDC         m_DC;
    BITMAP      m_BitmapInfo;

public:
    virtual int Load(const wstring& _FilePath) override;

public:
    CTexture();
    ~CTexture();
};

