#pragma once
#include "CObj.h"


class CSprite;

class CMissile :
    public CObj
{
private:
    Vec2        m_Velocity;
    float       m_VelocityScale;

    CCollider*  m_Collider;
    float       m_Mass;     // 질량
    Vec2        m_Force;    // 크기, 방향

    float       m_damage;
    float       m_knockBack;

protected:
    CSprite*    m_sprite;
    float       m_magnification;

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

    float GetKnockBack() { return m_knockBack; }
    void  GetKnockBack(float _knockBack) { m_knockBack = _knockBack; }

private:
    virtual void CreateSprite();

public:
    virtual void Begin() override;
    virtual void Tick() override;
    virtual void Render() override;

    virtual void BeginOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider) override;

public:
    CMissile();
    ~CMissile();
};

