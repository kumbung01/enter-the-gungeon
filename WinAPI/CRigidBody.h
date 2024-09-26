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
    Vec2            m_Force;        // ����, ���� ũ��
    Vec2            m_Velocity;     // ����, �ӷ�
    float           m_Mass;         // F = M x A
    float           m_InitialSpeed; // �ʱ� �̵��ӷ�
    float           m_MaxSpeed;     // �ִ� �ӷ� ����
    float           m_Friction;     // ������ ũ��
    
    bool            m_bPrevMove;    // ������ �̵������� �ƴ���
    bool            m_bMove;        // �̵������� �ƴ���

    Vec2            m_VelocityX;    // ��,�� ���� �ӵ�
    Vec2            m_VelocityY;    // ��,�Ʒ� ���� �ӵ�
    float           m_MaxGravitySpeed;  // �߷¿� ���� �ִ�ӵ� ����
    bool            m_bGround;      // ������ ���ִ���
    RIGIDBODY_MODE  m_Mode;     // ���� ���

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

