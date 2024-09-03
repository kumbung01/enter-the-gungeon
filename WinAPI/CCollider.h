#pragma once
#include "CComponent.h"

class CCollider :
    public CComponent
{
private:
    Vec2        m_Scale;    // Å©±â

public:
    void SetScale(Vec2 _Scale) { m_Scale = _Scale; }
    Vec2 GetScale() { return m_Scale; }


public:
    virtual void FinalTick() override;

public:
    CCollider();
    ~CCollider();
};

