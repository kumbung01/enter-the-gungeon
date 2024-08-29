#pragma once
#include "CObj.h"

class CPlayer :
    public CObj
{
private:
    float   m_Speed;

public:     
    virtual void Tick() override;

public:
    CPlayer();
    ~CPlayer();    
};

