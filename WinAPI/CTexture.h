#pragma once
#include "CAsset.h"
#include <string>

class CTexture :
    public CAsset
{
private:
    HBITMAP     m_hBit;         // ��Ʈ�� �ڵ�
    HDC         m_DC;           // ��Ʈ���� �������� �����ϴ� DC
    BITMAP      m_BitmapInfo;   // ��Ʈ�� ����

    Image*      m_Image;

public:
    HDC GetDC() { return m_DC; }
    UINT GetWidth() { return m_BitmapInfo.bmWidth; }
    UINT GetHeight() { return m_BitmapInfo.bmHeight; }

private:
    virtual int Load(const wstring& _FilePath) override;
    void Create(UINT _Width, UINT _Height);

public:
    CTexture();
    ~CTexture();

    friend class CAssetMgr;
};

