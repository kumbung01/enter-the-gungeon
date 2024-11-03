#pragma once
#include "CObj.h"

class CTexture;

struct sprite
{
    Vec2 leftTop;
    Vec2 rightBottom;
};

class CAtlas :
    public CObj
{
private:
    CTexture*           m_tex;
    sprite              m_pos;
    Vec2                m_leftTop;
    float               m_magnification;
    std::vector<sprite> m_sprites;      // 현재 스프라이트 위치

private:
    void AddSprite();
    void RemoveSprite(int _idx);
public:
    virtual void Tick() override;
    virtual void Render() override;

    void LoadTexture(const wstring& _key, const wstring& _filePath);
    void AddMagnification(float _mag) { m_magnification += _mag; }
public:
    CAtlas();
    ~CAtlas();
};

