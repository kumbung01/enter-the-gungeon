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
    CObj* m_owner;              // ���� ����(�÷��̾�, ����)
    Vec2  m_fireDir;

    float     m_fireDelay;      // �Ѿ� �߻� ������
    float     m_fireTime;       // ���� �Ѿ� �߻� �ð�
    float     m_reloadDelay;    // �Ѿ� ������ �ӵ�
    float     m_reloadTime;     // ���� �Ѿ� ������ �ð�
    int       m_magBullets;     // ���� �����Ǿ� �ִ� �Ѿ� ��
    int       m_maxMagBullets;  // �ִ� ���� ���� �Ѿ� ��
    int       m_bullets;        // ���� ź�෮
    int       m_maxBullets;     // �ִ� ź�෮

    float     m_bulletSpread;   // ��ź��
    float     m_knockback;      // �˹�

    //FIRE_TYPE m_fireType;     // �Ѿ� �߻� ���

public:
    FIRE_RESULT  Fire();      // �߻�, �Ķ����: ����, return type �߻� ����(����, ������ ��)
    float Reload(); // ������, �Ķ����: �Ѿ� ��
    void SetOwner(CObj* _owner) { m_owner = _owner; }
    

public:
    void Tick() override;
    void Render() override;
public:
    CGun();
    ~CGun();
};

