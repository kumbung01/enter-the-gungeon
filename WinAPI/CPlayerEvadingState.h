#pragma once
#include "CState.h"
class CPlayerEvadingState :
    public CState
{
public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;

public:
    CPlayerEvadingState();
    ~CPlayerEvadingState();
};

