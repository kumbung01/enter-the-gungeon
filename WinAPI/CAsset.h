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
    ASSET_TYPE GetAssetType() { return m_Type; }

protected:
    void CheckExt(const wstring& _Ext, wstring& _strFilePath);
    void SetKey(const wstring& _Key) { m_Key = _Key; }
    void SetRelativePath(const wstring& _RelativePath) { m_RelativePath = _RelativePath; }

private:
    virtual int Save(const wstring& _FilePath) { return S_OK; }
    virtual int Load(const wstring& _FilePath) = 0;

public:
    CAsset(ASSET_TYPE _Type);
    ~CAsset();
    friend class CAssetMgr;
};

