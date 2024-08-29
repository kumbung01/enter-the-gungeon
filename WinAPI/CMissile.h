#pragma once
#include "CObj.h"



class CMissile :
    public CObj
{
private:
    float m_Speed;
    float m_Angle;

public:
    void SetSpeed(float _Speed) { m_Speed = _Speed; }

public:
    virtual void Tick() override;
    virtual void Render() override;


public:
    CMissile();
    ~CMissile();
};

