#pragma once
#include "CComponent.h"

class CCollider :
    public CComponent
{
private:


public:
    virtual void FinalTick() override;

public:
    CCollider();
    ~CCollider();
};

