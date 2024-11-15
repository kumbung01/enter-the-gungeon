#pragma once
#include "CComponent.h"

class CFlipbook;

class CFlipbookPlayer :
    public CComponent
{
private:
    vector<CFlipbook*>  m_vecFlipbook;  // Flipbook 목록
    CFlipbook*          m_CurFlipbook;  // 현재 재생중인 Flipbook
    int                 m_SpriteIdx;    // 현재 재생중인 Flipbook 에서, 화면에 노출중인 Sprite 인덱스

    float               m_FPS;          // Flipbook 재생속도
    float               m_Time;         // 누적시간
    bool                m_Repeat;       // 반복재생인지 아닌지
    bool                m_Finish;       // 재생이 끝났는지 체크
    bool                m_mirror;       // 좌우 반전 확인
    float               m_angle;        // 회전 각도
    Vec2                m_axis;         // 회전축
    Vec2                m_offset;       // 위치
    float               m_magnification; // 확대 정도

public:
    void AddFlipbook(CFlipbook* _Flipbook) { m_vecFlipbook.push_back(_Flipbook); }
    void AddFlipbook(int _idx, CFlipbook* _Flipbook)
    {
        if (m_vecFlipbook.size() <= _idx)
        {
            m_vecFlipbook.resize(_idx + 1);
        }

        m_vecFlipbook[_idx] = _Flipbook;
    }

    void Play(int _FlipbookIdx, float _FPS, bool _Repeat, bool _IsMirrored=false)
    {
        m_CurFlipbook = m_vecFlipbook[_FlipbookIdx];
        m_SpriteIdx = 0;
        m_FPS = _FPS;
        m_Repeat = _Repeat;
        m_Finish = false;
        m_Time = 0.f;
        m_mirror = _IsMirrored;
    }

    void Play(const tAnimState& state, float _FPS, bool _Repeat)
    {
        m_CurFlipbook = m_vecFlipbook[state.idx];
        m_SpriteIdx = 0;
        m_FPS = _FPS;
        m_Repeat = _Repeat;
        m_Finish = false;
        m_Time = 0.f;
        m_mirror = state.mirror;
    }

    bool IsFinish() { return m_Finish; }

    void Reset()
    {
        m_Finish = false;
        m_SpriteIdx = 0;        
    }

    bool IsFlipbookMatch(int _FlipbookIdx)
    {
        return m_CurFlipbook == m_vecFlipbook[_FlipbookIdx];
    }

    void SetAngle(float _angle) { m_angle = _angle; }
    void SetMirror(bool _mirror) { m_mirror = _mirror; };
    void SetMagnification(float _magnification) { m_magnification = _magnification; }
    void SetOffset(Vec2 _offset) { m_offset = _offset; }
    void SetAxis(Vec2 _axis) { m_axis = _axis; }

    Vec2 GetOffset() { return m_offset; }
    Vec2 GetAxis() { return m_axis; }
public:
    virtual void FinalTick() override;
    void Render(); 

public:
    CFlipbookPlayer();
    ~CFlipbookPlayer();
};

