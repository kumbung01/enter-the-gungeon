#pragma once
#include "CObj.h"

class CUI :
    public CObj
{
private:
    bool    m_MouseHover;   // UI 위에 마우스가 올라왔는지 체크
    bool    m_LBtnDown;     // UI 위에서 마우스 왼쪽 버튼이 눌렸는지 체크


public:
    bool IsMouseHover() { return m_MouseHover; }

public:
    virtual void Tick() override;
    virtual void Render() override;

protected:
    virtual void MouseHoverCheck();
    virtual void MouseLBtnDown() { m_LBtnDown = true; }
    
    // 해당 UI 가 눌렸고, 다시 UI 위에서 버튼이 떼졌을 때 클릭으로 판정한다.
    virtual void MouseLBtnClikced() {}

public:
    CUI();
    ~CUI();

    friend class CUIMgr;
};