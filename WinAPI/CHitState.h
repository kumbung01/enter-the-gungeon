#pragma once
#include "CState.h"

class CFlipbookPlayer;

class CHitState :
    public CState
{
private:
    CFlipbookPlayer* m_flipbookPlayer;
public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;
private:
    tAnimState ProcessAnimState(Vec2 dir);
public:
    CHitState();
    ~CHitState();
};

