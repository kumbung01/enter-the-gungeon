#pragma once
#include "CObj.h"


class CMonster :
    public CObj
{
private:
    int         m_Dir;
    float       m_Speed;
    Vec2        m_InitPos;
    float       m_Dist;

public:
    void SetSpeed(float _Speed) { m_Speed = _Speed; }
    void SetDistance(float _Dist) { m_Dist = _Dist; }

public:
    virtual void Begin() override;
    virtual void Tick() override;            
    virtual void Render() override;

public:
    CMonster();
    ~CMonster();
};

