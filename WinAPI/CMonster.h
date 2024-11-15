#pragma once
#include "CObj.h"

class CCollider;
class CTexture;
class CFSM;
class CGun;
class CFlipbookPlayer;

class CMonster :
    public CObj
{
private:
    tMonInfo    m_Info;

    int         m_Dir;
    float       m_Speed;
    Vec2        m_InitPos;
    float       m_Dist;

    CFlipbookPlayer* m_flipbookPlayer;
    CTexture*   m_Tex;
    CCollider*  m_Collider;
    
    CFSM*       m_FSM;

    CGun*       m_gun;

public:
    void SetSpeed(float _Speed) { m_Speed = _Speed; }
    void SetDistance(float _Dist) { m_Dist = _Dist; }

    void SetGun(CGun* _gun) { m_gun = _gun; }
    CGun* GetGun() { return m_gun; }

    tMonInfo& GetMonInfo() { return m_Info; }

    void Play(tAnimState _state, float _duration, bool _repeat);

public:
    virtual void Begin() override;
    virtual void Tick() override;            
    virtual void Render() override;
    virtual void BeginOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider) override;
private:
    virtual void CreateFlipbook();

public:
    CMonster();
    ~CMonster();
};

