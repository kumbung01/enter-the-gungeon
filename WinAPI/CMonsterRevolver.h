#pragma once
#include "CGun.h"
class CMonsterRevolver :
    public CGun
{
private:
    virtual Vec2 CalculateFireDirection() override;
    virtual void CreateFlipbook() override;
    virtual void CreateBullet() override;
public:
    virtual GUN_STATE Fire() override;
public:
    virtual void Begin() override;
    virtual void Tick() override;
public:
    CMonsterRevolver();
    ~CMonsterRevolver();
};

