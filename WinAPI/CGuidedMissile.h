#pragma once
#include "CMissile.h"

class CGuidedMissile :
    public CMissile
{
private:
    CObj*   m_Target;       // ���� ���
    float   m_DetectRange;  // ���� ����




public:
    void SetDetectRange(float _Range) { m_DetectRange = _Range; }

public:
    virtual void Tick() override;
    virtual void BeginOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider) override;

private:
    void FindTarget();
    void TraceTarget_0();
    void TraceTarget_1();
    void TraceTarget_2();


public:
    CGuidedMissile();
    ~CGuidedMissile();
};

