#pragma once
#include "CObj.h"


typedef void (*PARAM_0)(void);
typedef void (*PARAM_1)(DWORD_PTR);


typedef void(CBase::* DELEGATE_0)(void);
typedef void(CBase::* DELEGATE_1)(DWORD_PTR);
typedef void(CBase::* DELEGATE_2)(DWORD_PTR, DWORD_PTR);


class CUI :
    public CObj
{
private:
    CUI*         m_ParentUI;    // �ڽ��� ������ �θ�UI �� ����Ű�� ������, nullptr �� ��� ������ �ֻ��� �θ� UI ��� ��
    vector<CUI*> m_vecChildUI;  // �����ϰ� �ִ� �ڽ� UI �� ������

    Vec2         m_FinalPos;    // ���� ���� ��ġ

    bool         m_MouseHover;  // UI ���� ���콺�� �ö�Դ��� üũ
    bool         m_LBtnDown;    // UI ������ ���콺 ���� ��ư�� ���ȴ��� üũ


public:
    bool IsMouseHover() { return m_MouseHover; }
    bool IsLBtnDown() { return m_LBtnDown; }

    Vec2 GetFinalPos() { return m_FinalPos; }

    void AddChildUI(CUI* _ChildUI)
    {
        m_vecChildUI.push_back(_ChildUI);
        _ChildUI->m_ParentUI = this;
    }


public:
    virtual void Tick() override;
    virtual void Tick_UI() = 0;

    virtual void Render() override;
    virtual void Render_UI();

protected:
    virtual void MouseHoverCheck();

    // ���콺 ���� ��ư�� ������ ��
    virtual void MouseLBtnDown() {}
    
    // �ش� UI �� ���Ȱ�, �ٽ� UI ������ ��ư�� ������ �� Ŭ������ �����Ѵ�.
    virtual void MouseLBtnClikced() {}

    // �ش� UI �� ������ �ʾ�����, UI ������ ��ư�� ������ ��, Drag Drop �� �� Ȱ��
    virtual void MouseReleased() {}

public:
    CUI();
    ~CUI();

    friend class CUIMgr;
};