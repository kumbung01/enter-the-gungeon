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
    float               m_moveSpeed;
    float               m_rollSpeed; // 회피속도, px 단위
    float               m_rollAccTime; // 회피 누적시간 
    float               m_rollTime;  // 회피지속시간
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
    float               m_invincibleTime;
    CRigidBody*         m_RigidBody;
    Vec2                m_normal; // for collision

    



public:     
    virtual void Begin() override;
    virtual void Tick() override;    
    virtual void Render() override;

    virtual void BeginOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider);
    virtual void Overlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider);
    virtual void EndOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider);

    void SetGun(CGun* _gun) { m_gun = _gun; }
    void SetReloadBar(CReloadBar* _bar) { m_reloadBar = _bar; }
    
    int GetKeyCnt() { return m_keyCnt; }
    void SetKeyCnt(int _key) { m_keyCnt = _key; }


private:
    void CreatePlayerFlipbook();
    void CreateFlipbook(const wstring& _FlipbookName, CTexture* _Atlas, Vec2 _LeftTop, Vec2 _Slice, int MaxFrame);
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

