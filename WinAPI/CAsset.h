#pragma once
#include "CBase.h"


class CAsset :
    public CBase
{
private:
    wstring             m_Key;          // ������ ������ �̸�(���¸Ŵ������� �ش� ������ ã�ƿö� ���)
    wstring             m_RelativePath; // ������ ���
    const ASSET_TYPE    m_Type;

public:
    const wstring& GetKey() { return m_Key; }
    const wstring& GetRelativePath() { return m_RelativePath; }

public:
    virtual int Load(const wstring& _FilePath) = 0;

public:
    CAsset(ASSET_TYPE _Type);
    ~CAsset();
};

