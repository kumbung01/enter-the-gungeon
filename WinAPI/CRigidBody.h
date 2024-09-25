#pragma once
#include "CComponent.h"

class CRigidBody :
    public CComponent
{
private:
    Vec2        m_Force;    // 방향, 힘의 크기
    Vec2        m_Velocity; // 방향, 속력
    float       m_Mass;     // F = M x A
    float       m_MaxSpeed; // 최대 속력 제한치
    bool        m_bGround;  // 땅위에 서있는지

public:
    virtual void FinalTick() override;

public:
    CRigidBody();
    ~CRigidBody();
};

