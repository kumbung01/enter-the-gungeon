#pragma once
#include "CComponent.h"

class CRigidBody :
    public CComponent
{
private:
    Vec2        m_Force;        // 방향, 힘의 크기
    Vec2        m_Velocity;     // 방향, 속력
    float       m_Mass;         // F = M x A
    float       m_InitialSpeed; // 초기 이동속력
    float       m_MaxSpeed;     // 최대 속력 제한치
    bool        m_bGround;      // 땅위에 서있는지

    bool        m_bPrevMove;    // 이전에 이동중인지 아닌지
    bool        m_bMove;        // 이동중인지 아닌지

public:
    Vec2 GetForce() { return m_Force; }
    void AddForce(Vec2 _Force) { m_Force += _Force; }
    
    float GetMass() { return m_Mass; }
    void SetMass(float _Mass) { m_Mass = _Mass; }

    float GetMaxSpeed() { return m_MaxSpeed; }
    void SetMasSpeed(float _Speed) { m_MaxSpeed = _Speed; }

    float GetInitialSpeed() { return m_InitialSpeed; }
    void SetInitialSpeed(float _Init) { m_InitialSpeed = _Init; }

    void SetVelocity(Vec2 _Velocity) { m_Velocity = _Velocity; }
    void AddVelocity(Vec2 _Velocity) { m_Velocity += _Velocity; }

    bool IsGround() { return m_bGround; }
    void SetGround(bool _Ground) { m_bGround = _Ground; }

public:
    virtual void FinalTick() override;

public:
    CRigidBody();
    ~CRigidBody();
};

