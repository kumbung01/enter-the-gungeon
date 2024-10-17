#pragma once
#include "CState.h"

class CIdleState :
    public CState
{

public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;

public:
    CIdleState();
    ~CIdleState();
};

