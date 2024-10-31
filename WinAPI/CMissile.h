#pragma once
#include "CObj.h"



class CMissile :
    public CObj
{
private:
    Vec2        m_Velocity;
    float       m_VelocityScale;

    CCollider*  m_Collider;
    float       m_Mass;     // ����

    Vec2        m_Force;    // ũ��, ����

    float       m_damage;

public:
    void SetVelocity(Vec2 _Velocity) { m_Velocity = _Velocity; }
    Vec2 GetVelocity() { return m_Velocity; }

    float GetVelocityScale() { return m_VelocityScale; }
    void SetVelocityScale(float _Scale) { m_VelocityScale = _Scale; }

    CCollider* GetCollider() { return m_Collider; }

    void SetMass(float _Mass) { m_Mass = _Mass; }
    float GetMass() { return m_Mass; }

    void AddForce(Vec2 _Force) { m_Force += _Force; }
    Vec2 GetForce() { return m_Force; }

    float GetDamage() { return m_damage; }
    void  SetDamage(float _damage) { m_damage = _damage; }

public:
    virtual void Tick() override;
    virtual void Render() override;

public:
    CMissile();
    ~CMissile();
};

