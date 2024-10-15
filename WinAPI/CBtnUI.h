#pragma once
#include "CUI.h"

class CBtnUI :
    public CUI
{
private:

public:
    virtual void Tick_UI() override;
    virtual void Render_UI() override;

    // Mouse Click
    virtual void MouseLBtnClikced() override;

public:
    CBtnUI();
    ~CBtnUI();
};

