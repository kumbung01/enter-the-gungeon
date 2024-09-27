#pragma once
#include "CComponent.h"


class CTileMap :
    public CComponent
{
private:

public:
    virtual void FinalTick() override;

public:
    CTileMap();
    ~CTileMap();
};

