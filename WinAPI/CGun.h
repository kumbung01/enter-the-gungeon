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
    CObj* m_owner;              // ���� ����(�÷��̾�, ����)
    Vec2  m_gunDir;
    GUN_STATE m_gunState;     // ���� �� ����

    float     m_fireDelay;      // �Ѿ� �߻� ������
    float     m_fireTime;       // ���� �Ѿ� �߻� �ð�
    float     m_reloadDelay;    // �Ѿ� ������ �ӵ�
    float     m_reloadTime;     // ���� �Ѿ� ������ �ð�
    int       m_magBullets;     // ���� �����Ǿ� �ִ� �Ѿ� ��
    int       m_maxMagBullets;  // �ִ� ���� ���� �Ѿ� ��
    int       m_bullets;        // ���� ź�෮
    int       m_maxBullets;     // �ִ� ź�෮

    bool      m_bIsInfiniteBullet;  //  ����źâ
    float     m_bulletSpread;   // ��ź��
    float     m_knockback;      // �˹�

    CFlipbookPlayer* m_flipbookPlayer;
    float     m_magnification;

    bool      m_isRightHand;
    Vec2      m_muzzle;
    Vec2      m_hand;
    CSprite*  m_handSprite;
    bool      m_visible;

public:
    virtual GUN_STATE Fire();      // �߻�, �Ķ����: ����, return type �߻� ����(����, ������ ��)
    virtual GUN_STATE Reload(bool isFired = false); // ������, �Ķ����: �Ѿ� ��
public:
    void SetOwner(CObj* _owner) { m_owner = _owner; }
    float GetReloadDelay() { return m_reloadDelay; }
    void SetVisible(bool _visible) { m_visible = _visible; }
    bool IsRightHand() { return m_isRightHand; }

    CSprite* GetHandSprite() { return m_handSprite; }
    void SetHandSprite(CSprite* _handSprite) { m_handSprite = _handSprite; }
protected:
    virtual bool IsTriggered();           // ��Ƽ� ���
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

