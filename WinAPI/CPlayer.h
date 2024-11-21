#pragma once
#include "CObj.h"

class CCollider;
class CTexture;
class CFlipbookPlayer;
class CGun;
class CReloadBar;
class CRigidBody;



class CPlayer :
    public CObj
{
private:
    int                 m_curHP;
    int                 m_maxHP;
    int                 m_blankCnt;
    int                 m_keyCnt;
    const float         m_moveSpeed;
    const float         m_rollSpeed; // 회피속도, px 단위
    float               m_rollAccTime; // 회피 누적시간 
    const float         m_rollTime;  // 회피지속시간
    CCollider*          m_HitBox;
    CFlipbookPlayer*    m_FlipbookPlayer;

    CGun*               m_gun;
    CReloadBar*         m_reloadBar;

    Vec2                m_moveDir;
    Vec2                m_gunDir;
    tAnimState          m_animState;
    PLAYER_STATE        m_state;

    bool                m_isInvincible;
    float               m_invincibleAccTime;
    const float         m_invincibleTime;
    int                 m_invincibleVisibleTime;
    CRigidBody*         m_RigidBody;
    Vec2                m_normal; // for collision
    bool                m_visible;

    



public:     
    virtual void Begin() override;
    virtual void Tick() override;    
    virtual void Render() override;

    virtual void BeginOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider);
    virtual void Overlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider);
    virtual void EndOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider);

    void SetGun(CGun* _gun) { m_gun = _gun; }
    CGun* GetGun() { return m_gun; }
    void SetReloadBar(CReloadBar* _bar) { m_reloadBar = _bar; }
    
    int GetKeyCnt() { return m_keyCnt; }
    void SetKeyCnt(int _key) { m_keyCnt = _key; }

    int GetCurHP() { return m_curHP; }
private:
    void CreatePlayerFlipbook();
    void CreateFlipbook(const wstring& _FlipbookName, CTexture* _Atlas, Vec2 _LeftTop, Vec2 _Slice, int MaxFrame);
    tAnimState ProcessAnimState(const Vec2& _dir, const PLAYER_STATE _state);
    void IdleState();
    void MoveState();
    void RollState();
    void DeadState();    
private:
    void Reload(float _duration);


public:
    CPlayer();
    ~CPlayer();    
};

