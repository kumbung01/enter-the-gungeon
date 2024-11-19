#pragma once
#include "CObj.h"

class CCollider;
class CFSM;
class CGun;
class CFlipbookPlayer;
class CRigidBody;

class CMonster :
    public CObj
{
private:
    tMonInfo    m_Info;
    Vec2        m_InitPos;
    float       m_Dist;
    Vec2        m_normal;

    CFlipbookPlayer* m_flipbookPlayer;
    CCollider*  m_Collider;
    CFSM*       m_FSM;
    CGun*       m_gun;
    CRigidBody* m_rigidBody;

public:
    void SetVelocity(Vec2 _velocity);
    Vec2 getNormal() { return m_normal; }

    void SetGun(CGun* _gun) { m_gun = _gun; }
    CGun* GetGun() { return m_gun; }

    const bool IsDead() { return m_Info.CurHP <= 0.f; }

    tMonInfo& GetMonInfo() { return m_Info; }

    CRigidBody* GetRigidBody() { return m_rigidBody; }
public:
    virtual void Begin() override;
    virtual void Tick() override;            
    virtual void Render() override;
    virtual void BeginOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider) override;
    virtual void Overlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider) override;
    virtual void EndOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider) override;
private:
    virtual void CreateFlipbook();

public:
    CMonster();
    ~CMonster();
};

