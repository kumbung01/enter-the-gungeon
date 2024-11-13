#pragma once
#include "CGun.h"
class CRevolver :
    public CGun
{
protected:
    virtual bool IsTriggered() override;
    //virtual void CreateBullet() override;
    //virtual void CalculateFireDirection() override;
    virtual void CreateFlipbook() override;
public:
    CRevolver();
    ~CRevolver();
};

