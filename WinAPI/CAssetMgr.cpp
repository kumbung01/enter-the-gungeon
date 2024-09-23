#include "pch.h"
#include "CAssetMgr.h"

#include "CTexture.h"
#include "CSprite.h"
#include "CFlipbook.h"

CAssetMgr::CAssetMgr()
{

}

CAssetMgr::~CAssetMgr()
{
    Delete_Map(m_mapTex);
    Delete_Map(m_mapSprite); 
    Delete_Map(m_mapFlipbook);
}

void CAssetMgr::Init()
{
   
}

CTexture* CAssetMgr::FindTexture(const wstring& _Key)
{
    map<wstring, CTexture*>::iterator iter = m_mapTex.find(_Key);

    if (iter == m_mapTex.end())
    {
        return nullptr;
    }

    return iter->second;
}

CTexture* CAssetMgr::LoadTexture(const wstring& _Key, const wstring& _RelativePath)
{
    CAsset* pTex = FindTexture(_Key);

    // �̹� �ε��� ���� �ִ� Texture ���
    if (nullptr != pTex)
    {
        // �ε��� �ؽ��ĸ� ��ȯ
        return (CTexture*)pTex;
    }

    pTex = new CTexture;
    pTex->Load(_RelativePath);

    // ���¿�, �ڽ��� ���¸Ŵ����� ��ϵɶ� ���� Ű���� �ε��� �� ����� ��θ� �������ش�.
    pTex->SetKey(_Key);
    pTex->SetRelativePath(_RelativePath);

    // �����̳ʿ� �ؽ��� ���
    m_mapTex.insert(make_pair(_Key, (CTexture*)pTex));

    return (CTexture*)pTex;
}

CSprite* CAssetMgr::FindSprite(const wstring& _Key)
{
    map<wstring, CSprite*>::iterator iter = m_mapSprite.find(_Key);

    if (iter == m_mapSprite.end())
    {
        return nullptr;
    }

    return iter->second;
}

CSprite* CAssetMgr::LoadSprite(const wstring& _Key, const wstring& _RelativePath)
{
    CAsset* pSprite = FindSprite(_Key);

    // �̹� �ε��� ���� �ִ� Texture ���
    if (nullptr != pSprite)
    {
        // �ε��� �ؽ��ĸ� ��ȯ
        return (CSprite*)pSprite;
    }

    pSprite = new CSprite;
    pSprite->Load(_RelativePath);

    // ���¿�, �ڽ��� ���¸Ŵ����� ��ϵɶ� ���� Ű���� �ε��� �� ����� ��θ� �������ش�.
    pSprite->SetKey(_Key);
    pSprite->SetRelativePath(_RelativePath);

    // �����̳ʿ� �ؽ��� ���
    m_mapSprite.insert(make_pair(_Key, (CSprite*)pSprite));

    return (CSprite*)pSprite;
}

void CAssetMgr::AddSprite(const wstring& _Key, CSprite* _Sprite)
{
    assert(!FindSprite(_Key));

    _Sprite->SetKey(_Key);
    m_mapSprite.insert(make_pair(_Key, _Sprite));
}



CFlipbook* CAssetMgr::FindFlipbook(const wstring& _Key)
{
    map<wstring, CFlipbook*>::iterator iter = m_mapFlipbook.find(_Key);

    if (iter == m_mapFlipbook.end())
    {
        return nullptr;
    }

    return iter->second;
}

CFlipbook* CAssetMgr::LoadFlipbook(const wstring& _Key, const wstring& _RelativePath)
{
    CAsset* pFlipbook = FindFlipbook(_Key);

    // �̹� �ε��� ���� �ִ� Texture ���
    if (nullptr != pFlipbook)
    {
        // �ε��� �ؽ��ĸ� ��ȯ
        return (CFlipbook*)pFlipbook;
    }

    pFlipbook = new CFlipbook;
    pFlipbook->Load(_RelativePath);

    // ���¿�, �ڽ��� ���¸Ŵ����� ��ϵɶ� ���� Ű���� �ε��� �� ����� ��θ� �������ش�.
    pFlipbook->SetKey(_Key);
    pFlipbook->SetRelativePath(_RelativePath);

    // �����̳ʿ� �ؽ��� ���
    m_mapFlipbook.insert(make_pair(_Key, (CFlipbook*)pFlipbook));

    return (CFlipbook*)pFlipbook;
}

void CAssetMgr::AddFlipbook(const wstring& _Key, CFlipbook* _Flipbook)
{
    assert(!FindFlipbook(_Key));

    _Flipbook->SetKey(_Key);
    m_mapFlipbook.insert(make_pair(_Key, _Flipbook));
}
