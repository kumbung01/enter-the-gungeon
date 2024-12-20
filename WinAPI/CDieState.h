#pragma once
#include "CState.h"

class CFlipbookPlayer;

class CDieState :
    public CState
{
private:
    CFlipbookPlayer* m_flipbookPlayer;

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

