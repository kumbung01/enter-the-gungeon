#pragma once
#include "CObj.h"

enum FIRE_TYPE
{
    SEMIAUTO,
    FULLAUTO,
    CHARGE,
    END
};

enum FIRE_RESULT
{
    FIRED,
    WAIT,
    RELOAD,
};

class CGun :
    public CObj
{
private:  
    CObj* m_owner;              // 총의 주인(플레이어, 몬스터)
    Vec2  m_fireDir;

    float     m_fireDelay;      // 총알 발사 딜레이
    float     m_fireTime;       // 현재 총알 발사 시간
    float     m_reloadDelay;    // 총알 재장전 속도
    float     m_reloadTime;     // 현재 총알 재장전 시간
    int       m_magBullets;     // 현재 장전되어 있는 총알 수
    int       m_maxMagBullets;  // 최대 장전 가능 총알 수
    int       m_bullets;        // 현재 탄약량
    int       m_maxBullets;     // 최대 탄약량

    float     m_bulletSpread;   // 산탄도
    float     m_knockback;      // 넉백

    //FIRE_TYPE m_fireType;     // 총알 발사 방법

public:
    FIRE_RESULT  Fire();      // 발사, 파라미터: 방향, return type 발사 여부(고장, 재장전 등)
    float Reload(); // 재장전, 파라미터: 총알 수
    void SetOwner(CObj* _owner) { m_owner = _owner; }
    

public:
    void Tick() override;
    void Render() override;
public:
    CGun();
    ~CGun();
};

