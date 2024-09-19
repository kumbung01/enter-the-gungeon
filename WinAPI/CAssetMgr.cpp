#include "pch.h"
#include "CAssetMgr.h"

#include "CTexture.h"
#include "CSprite.h"

CAssetMgr::CAssetMgr()
{

}

CAssetMgr::~CAssetMgr()
{

}

void CAssetMgr::Init()
{
    // AtlasTexture
    CTexture* pAtlas = LoadTexture(L"Link", L"Texture\\link_32.bmp");

    // Sprite 생성하기
    CSprite* pSprite = new CSprite;
    pSprite->Create(pAtlas, Vec2(0.f, 0.f), Vec2(120.f, 130.f));
    AddSprite(L"Link_0", pSprite);


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

    // 이미 로딩한 적이 있는 Texture 라면
    if (nullptr != pTex)
    {
        // 로딩한 텍스쳐를 반환
        return (CTexture*)pTex;
    }

    pTex = new CTexture;
    pTex->Load(_RelativePath);

    // 에셋에, 자신이 에셋매니저에 등록될때 사용된 키값과 로딩할 때 사용한 경로를 세팅해준다.
    pTex->SetKey(_Key);
    pTex->SetRelativePath(_RelativePath);

    // 컨테이너에 텍스쳐 등록
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
    CAsset* pSprite = FindTexture(_Key);

    // 이미 로딩한 적이 있는 Texture 라면
    if (nullptr != pSprite)
    {
        // 로딩한 텍스쳐를 반환
        return (CSprite*)pSprite;
    }

    pSprite = new CSprite;
    pSprite->Load(_RelativePath);

    // 에셋에, 자신이 에셋매니저에 등록될때 사용된 키값과 로딩할 때 사용한 경로를 세팅해준다.
    pSprite->SetKey(_Key);
    pSprite->SetRelativePath(_RelativePath);

    // 컨테이너에 텍스쳐 등록
    m_mapSprite.insert(make_pair(_Key, (CSprite*)pSprite));

    return (CSprite*)pSprite;
}

void CAssetMgr::AddSprite(const wstring& _Key, CSprite* _Sprite)
{
    assert(!FindSprite(_Key));

    _Sprite->SetKey(_Key);
    m_mapSprite.insert(make_pair(_Key, _Sprite));
}
