#pragma once
#include "CAsset.h"

class CTexture;

class CSprite :
    public CAsset
{
private:
    CTexture*   m_Atlas;    // ��������Ʈ�� Ÿ������ ������ ��Ʋ�� �ؽ���
    Vec2        m_LeftTop;  // ��, ��� �ȼ� ��ġ
    Vec2        m_Slice;    // ���� ũ��

public:
    CTexture* GetAtlas() { return m_Atlas; }
    Vec2 GetLeftTop() { return m_LeftTop; }
    Vec2 GetSlice() { return m_Slice; }

public:
    virtual int Load(const wstring& _FilePath) override;
    void Create(CTexture* _Atlas, Vec2 _LeftTop, Vec2 _Slice);   

public:
    CSprite();
    ~CSprite();
};

