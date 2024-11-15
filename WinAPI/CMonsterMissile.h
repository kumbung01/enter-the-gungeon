#pragma once
#include "CMissile.h"
class CMonsterMissile :
    public CMissile
{
public:
    CMonsterMissile();
    ~CMonsterMissile();

public:
    virtual void Begin() override;
    virtual void CreateSprite() override;
};

