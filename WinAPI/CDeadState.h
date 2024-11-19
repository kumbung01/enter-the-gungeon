#pragma once
#include "CState.h"

class CFlipbookPlayer;

class CDeadState :
    public CState
{
private:
    CFlipbookPlayer* m_flipbookPlayer;
    float            m_deadTime;
    float            m_deadAccTime;

private:
    tAnimState ProcessAnimState(Vec2 dir);
public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;

public:
    CDeadState();
    ~CDeadState();
};

