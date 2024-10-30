#pragma once
#include "CObj.h"

class CCollider;
class CTexture;
class CFlipbookPlayer;
class CGun;
class CReloadBar;
class CFSM;
//class CRigidBody;

enum class PLAYER_STATE
{
    IDLE,
    MOVING,
    EVADING,
};

class CPlayer :
    public CObj
{
private:
    float               m_Speed;
    float               m_AttSpeed; // �ʴ� �߻� �ӵ�
    float               m_AccTime;  // �ð� ����, accumulated time
    float               m_evadeSpeed; // ȸ�Ǽӵ�, px ����
    float               m_evadeAccTime; // ȸ�� �����ð� 
    float               m_evadeTime;  // ȸ�����ӽð�
    CCollider*          m_HitBox;
    CFlipbookPlayer*    m_FlipbookPlayer;

    CGun*               m_gun;
    CReloadBar*         m_reloadBar;

    Vec2                m_moveDir;
    Vec2                m_gunDir;
    PLAYER_STATE        m_state;

    CFSM*               m_fsm;
    //CRigidBody*         m_RigidBody;

    



public:     
    virtual void Begin() override;
    virtual void Tick() override;    
    virtual void Render() override;

    virtual void BeginOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider);
    virtual void Overlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider);
    virtual void EndOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider);

    void SetGun(CGun* _gun) { m_gun = _gun; }
    void SetReloadBar(CReloadBar* _bar) { m_reloadBar = _bar; }
    void Reload(float _duration);

private:
    void CreatePlayerFlipbook();
    void CreateFlipbook(const wstring& _FlipbookName, CTexture* _Atlas, Vec2 _LeftTop, Vec2 _Slice, int MaxFrame);
    void IdleState();
    void MoveState();
    void EvadeState();

public:
    CPlayer();
    ~CPlayer();    
};

