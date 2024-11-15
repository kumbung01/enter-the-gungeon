#pragma once
#include "CObj.h"

enum FIRE_TYPE
{
    SEMIAUTO,
    FULLAUTO,
    CHARGE,
    END
};

enum GUN_ANIM_STATE
{
    GUN_IDLE,
    GUN_CHARGE,
    GUN_FIRE,
    GUN_RELOAD
};

enum class GUN_STATE
{
    IDLE,
    FIRING,
    EMPTY,
    RELOAD,     // reload start
    RELOADING,  // reloading
    GROUND,
};

class CFlipbookPlayer;
class CSprite;

class CGun :
    public CObj
{
protected:  
    CObj* m_owner;              // 총의 주인(플레이어, 몬스터)
    Vec2  m_gunDir;
    GUN_STATE m_gunState;     // 현재 총 상태

    float     m_fireDelay;      // 총알 발사 딜레이
    float     m_fireTime;       // 현재 총알 발사 시간
    float     m_reloadDelay;    // 총알 재장전 속도
    float     m_reloadTime;     // 현재 총알 재장전 시간
    int       m_magBullets;     // 현재 장전되어 있는 총알 수
    int       m_maxMagBullets;  // 최대 장전 가능 총알 수
    int       m_bullets;        // 현재 탄약량
    int       m_maxBullets;     // 최대 탄약량

    bool      m_bIsInfiniteBullet;  //  무한탄창
    float     m_bulletSpread;   // 산탄도
    float     m_knockback;      // 넉백

    CFlipbookPlayer* m_flipbookPlayer;
    float     m_magnification;

    bool      m_isRightHand;
    Vec2      m_muzzle;
    Vec2      m_hand;
    CSprite*  m_handSprite;
    bool      m_visible;

public:
    virtual GUN_STATE Fire();      // 발사, 파라미터: 방향, return type 발사 여부(고장, 재장전 등)
    virtual GUN_STATE Reload(bool isFired = false); // 재장전, 파라미터: 총알 수
public:
    void SetOwner(CObj* _owner) { m_owner = _owner; }
    float GetReloadDelay() { return m_reloadDelay; }
    void SetVisible(bool _visible) { m_visible = _visible; }
    bool IsRightHand() { return m_isRightHand; }

    CSprite* GetHandSprite() { return m_handSprite; }
    void SetHandSprite(CSprite* _handSprite) { m_handSprite = _handSprite; }
protected:
    virtual bool IsTriggered();           // 방아쇠 당김
    virtual void CreateBullet();
    virtual Vec2 CalculateFireDirection();
    virtual void CreateFlipbook();
    virtual void SetGunPos();

public:
    void Begin() override;
    void Tick() override;
    void Render() override;
public:
    CGun();
    ~CGun();
};

