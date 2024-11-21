#pragma once
#include "CObj.h"

enum class UI_STATE
{
    IDLE,
    DRAWING,
};

enum class DRAW_TYPE
{
    RELOADING,
    EMPTY,
    NONE
};

class CFlipbookPlayer;

class CReloadBar :
    public CObj
{
private:
    CFlipbookPlayer* m_flipbookPlayer;
    CObj* m_owner;
    UI_STATE m_state;
    DRAW_TYPE m_type;

    int   m_frameCount;
    float m_duration;
    float m_currentTime;
public:
    void SetOwner(CObj* _owner) { m_owner = _owner; }
    void Draw(DRAW_TYPE _type, float _duration);

    void Tick() override;
    void Render() override;
public:
    CReloadBar();
    ~CReloadBar();
};

