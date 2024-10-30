#pragma once
#include "CState.h"
class CPlayerMovingState :
    public CState
{
public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;

public:
    CPlayerMovingState();
    ~CPlayerMovingState();

};

