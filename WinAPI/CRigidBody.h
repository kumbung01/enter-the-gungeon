#pragma once
#include "CComponent.h"

class CRigidBody :
    public CComponent
{
private:
    Vec2        m_Force;    // ����, ���� ũ��
    Vec2        m_Velocity; // ����, �ӷ�
    float       m_Mass;     // F = M x A
    float       m_MaxSpeed; // �ִ� �ӷ� ����ġ
    bool        m_bGround;  // ������ ���ִ���

public:
    virtual void FinalTick() override;

public:
    CRigidBody();
    ~CRigidBody();
};

