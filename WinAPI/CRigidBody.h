#pragma once
#include "CComponent.h"

enum class RIGIDBODY_MODE
{
    TOPVIEW,
    BELTSCROLL,
};

class CRigidBody :
    public CComponent
{
private:
    Vec2            m_Force;        // 방향, 힘의 크기
    Vec2            m_Velocity;     // 방향, 속력
    float           m_Mass;         // F = M x A
    float           m_InitialSpeed; // 초기 이동속력
    float           m_MaxSpeed;     // 최대 속력 제한
    float           m_Friction;     // 마찰력 크기
    
    bool            m_bPrevMove;    // 이전에 이동중인지 아닌지
    bool            m_bMove;        // 이동중인지 아닌지

    Vec2            m_VelocityX;    // 좌,우 방향 속도
    Vec2            m_VelocityY;    // 위,아래 방향 속도
    float           m_MaxGravitySpeed;  // 중력에 의한 최대속도 제한
    bool            m_bGround;      // 땅위에 서있는지
    RIGIDBODY_MODE  m_Mode;     // 동작 모드

public:
    Vec2 GetForce() { return m_Force; }
    void AddForce(Vec2 _Force) { m_Force += _Force; }
    
    float GetMass() { return m_Mass; }
    void SetMass(float _Mass) { m_Mass = _Mass; }

    float GetMaxSpeed() { return m_MaxSpeed; }
    void SetMaxSpeed(float _Speed) { m_MaxSpeed = _Speed; }

    float GetFriction() { return m_Friction; }
    void SetFriction(float _Friction) { m_Friction = _Friction; }

    float GetInitialSpeed() { return m_InitialSpeed; }
    void SetInitialSpeed(float _Init) { m_InitialSpeed = _Init; }

    void SetVelocity(Vec2 _Velocity) { m_Velocity = _Velocity; }
    void AddVelocity(Vec2 _Velocity) { m_Velocity += _Velocity; }

    bool IsGround() { return m_bGround; }
    void SetGround(bool _Ground) { m_bGround = _Ground; }

public:
    virtual void FinalTick() override;

private:
    void FinalTick_TopView();
    void FinalTick_BeltScroll();

    void CheckState();
    void CalcInitSpeed();
    void CalcFriction();
    void CalcMaxSpeed();

public:
    CRigidBody();
    ~CRigidBody();
};

