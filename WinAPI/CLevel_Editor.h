#pragma once

#include "CLevel.h"

class CLevel_Editor :
    public CLevel
{
public:
    virtual void Begin() override;
    virtual void End() override;

public:
    CLevel_Editor();
    ~CLevel_Editor();
};

