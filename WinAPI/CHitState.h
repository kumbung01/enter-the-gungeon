#pragma once
#include "CState.h"

class CFlipbookPlayer;

class CHitState :
    public CState
{
private:
    CObj* m_targetObject;
    CFlipbookPlayer* m_flipbookPlayer;
    Vec2             m_hitDir;
    float            m_knockBack;
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

