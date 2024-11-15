#pragma once
#include "CState.h"
class CSurpriseState :
    public CState
{
public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;

public:
    CSurpriseState();
    ~CSurpriseState();
};

