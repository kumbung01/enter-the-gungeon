#pragma once
#include "CObj.h"



class CMissile :
    public CObj
{
private:
    Vec2        m_Velocity;
    CCollider*  m_Collider;
    float       m_Mass;     // ����

    Vec2        m_Force;    // ũ��, ����



public:
    void SetVelocity(Vec2 _Velocity) { m_Velocity = _Velocity; }
    Vec2 GetVelocity() { return m_Velocity; }
    CCollider* GetCollider() { return m_Collider; }

    void SetMass(float _Mass) { m_Mass = _Mass; }
    float GetMass() { return m_Mass; }

    void AddForce(Vec2 _Force) { m_Force += _Force; }
    Vec2 GetForce() { return m_Force; }


public:
    virtual void Tick() override;
    virtual void Render() override;

public:
    CMissile();
    ~CMissile();
};

