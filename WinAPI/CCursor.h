#pragma once
#include "CObj.h"

class CTexture;

class CCursor :
    public CObj
{
    CTexture* m_Tex;


public:
    virtual void Begin() override;
    virtual void Tick() override;
    virtual void Render() override;

public:
    CCursor();
    ~CCursor();
};

