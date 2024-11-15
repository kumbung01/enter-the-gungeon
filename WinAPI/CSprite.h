#pragma once
#include "CAsset.h"

class CTexture;

enum RENDER_TYPE
{
    RENDER_BITBLT,
    RENDER_GDIPLUS,
};

class CSprite :
    public CAsset
{
private:
    CTexture*   m_Atlas;    // ��������Ʈ�� Ÿ������ ������ ��Ʋ�� �ؽ���

    Vec2        m_LeftTop;  // ��, ��� �ȼ� ��ġ
    Vec2        m_Slice;    // ���� ũ��
    Vec2        m_Offset;   // �߰� �����̵�

    RENDER_TYPE m_renderType; // ���� ���

public:
    CTexture* GetAtlas() { return m_Atlas; }
    Vec2 GetLeftTop() { return m_LeftTop; }
    Vec2 GetSlice() { return m_Slice; }
    Vec2 GetOffset() { return m_Offset; }

    void SetOffset(Vec2 _Offset) { m_Offset = _Offset; }
    RENDER_TYPE GetRenderType() { return m_renderType; }
public:
    virtual int Save(const wstring& _RelativePath) override;
    virtual int Load(const wstring& _RelativePath) override;

    void Create(CTexture* _Atlas, Vec2 _LeftTop, Vec2 _Slice);   

public:
    CSprite();
    ~CSprite();
};

