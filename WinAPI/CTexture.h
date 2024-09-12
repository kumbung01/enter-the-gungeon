#pragma once
#include "CAsset.h"
#include <string>

class CTexture :
    public CAsset
{
private:
    HBITMAP     m_hBit;         // 비트맵 핸들
    HDC         m_DC;           // 비트맵을 목적지로 지정하는 DC
    BITMAP      m_BitmapInfo;   // 비트맵 정보


public:
    HDC GetDC() { return m_DC; }
    UINT GetWidth() { return m_BitmapInfo.bmWidth; }
    UINT GetHeight() { return m_BitmapInfo.bmHeight; }

public:
    virtual int Load(const wstring& _FilePath) override;

public:
    CTexture();
    ~CTexture();
};

