#pragma once
#include "CObj.h"



class CMissile :
    public CObj
{
private:
    Vec2        m_Velocity;
    CCollider*  m_Collider;

public:
    void SetVelocity(Vec2 _Velocity) { m_Velocity = _Velocity; }
    Vec2 GetVelocity() { return m_Velocity; }
    CCollider* GetCollider() { return m_Collider; }



public:
    virtual void Tick() override;
    virtual void Render() override;

public:
    CMissile();
    ~CMissile();
};

