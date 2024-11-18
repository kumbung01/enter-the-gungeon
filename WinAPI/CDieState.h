#pragma once
#include "CState.h"
class CDieState :
    public CState
{
private:
    tAnimState ProcessAnimState(Vec2 dir);
public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;

public:
    CDieState();
    ~CDieState();
};

