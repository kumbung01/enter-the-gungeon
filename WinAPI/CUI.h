#pragma once
#include "CObj.h"

class CUI :
    public CObj
{
private:
    bool    m_MouseHover;   // UI ���� ���콺�� �ö�Դ��� üũ
    bool    m_LBtnDown;     // UI ������ ���콺 ���� ��ư�� ���ȴ��� üũ


public:
    bool IsMouseHover() { return m_MouseHover; }

public:
    virtual void Tick() override;
    virtual void Render() override;

protected:
    virtual void MouseHoverCheck();
    virtual void MouseLBtnDown() { m_LBtnDown = true; }
    
    // �ش� UI �� ���Ȱ�, �ٽ� UI ������ ��ư�� ������ �� Ŭ������ �����Ѵ�.
    virtual void MouseLBtnClikced() {}

public:
    CUI();
    ~CUI();

    friend class CUIMgr;
};