#pragma once
#include "CObj.h"

class CPlayer :
    public CObj
{
private:
    float   m_Speed;
    float   m_AttSpeed; // 초당 발사 속도
    float   m_AccTime;  // 시간 누적


public:     
    virtual void Begin() override;
    virtual void Tick() override;

public:
    CPlayer();
    ~CPlayer();    
};

