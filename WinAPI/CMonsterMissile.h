#pragma once
#include "CMissile.h"
class CMonsterMissile :
    public CMissile
{
public:
    CMonsterMissile();
    ~CMonsterMissile();

public:
    virtual void CreateSprite() override;
};

