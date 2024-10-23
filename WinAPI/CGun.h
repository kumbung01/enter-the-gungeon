#pragma once
#include "CObj.h"

enum FIRE_TYPE
{
    SEMIAUTO,
    FULLAUTO,
    CHARGE,
    END
};

enum class GUN_STATE
{
    IDLE,
    FIRING,
    RELOADING,
};

class CGun :
    public CObj
{
private:  
    CObj* m_owner;              // ���� ����(�÷��̾�, ����)
    Vec2  m_fireDir;
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

    //FIRE_TYPE m_fireType;     // �Ѿ� �߻� ���

public:
    virtual bool Trigger();           // ��Ƽ� ���
    virtual void Fire();      // �߻�, �Ķ����: ����, return type �߻� ����(����, ������ ��)
    virtual void Reload(bool isFired = false); // ������, �Ķ����: �Ѿ� ��
    void SetOwner(CObj* _owner) { m_owner = _owner; }
private:
    void CreateBullet();
    void CalculateFireDirection();

public:
    void Tick() override;
    void Render() override;
public:
    CGun();
    ~CGun();
};
