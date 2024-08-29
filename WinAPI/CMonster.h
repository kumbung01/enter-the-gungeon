#pragma once
#include "CObj.h"


class CMonster :
    public CObj
{
private:
    int         m_Dir;
    float       m_Speed;

public:
    virtual void Tick() override;            
    virtual void Render() override;

public:
    CMonster();
    ~CMonster();
};

