#pragma once
#include "CObj.h"

class CCollider;

class CPlayer :
    public CObj
{
private:
    float       m_Speed;
    float       m_AttSpeed; // �ʴ� �߻� �ӵ�
    float       m_AccTime;  // �ð� ����
    CCollider*  m_HitBox;


public:     
    virtual void Begin() override;
    virtual void Tick() override;    

public:
    CPlayer();
    ~CPlayer();    
};

