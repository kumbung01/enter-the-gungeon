#pragma once
#include "CComponent.h"

class CFlipbook;

class CFlipbookPlayer :
    public CComponent
{
private:
    vector<CFlipbook*>  m_vecFlipbook;  // Flipbook ���
    CFlipbook*          m_CurFlipbook;  // ���� ������� Flipbook
    int                 m_SpriteIdx;    // ���� ������� Flipbook ����, ȭ�鿡 �������� Sprite �ε���

    float               m_FPS;          // Flipbook ����ӵ�
    float               m_Time;         // �����ð�
    bool                m_Repeat;       // �ݺ�������� �ƴ���
    bool                m_Finish;       // ����� �������� üũ
    bool                m_mirror;       // �¿� ���� Ȯ��
    float               m_angle;        // ȸ�� ����
    Vec2                m_axis;         // ȸ����
    Vec2                m_offset;       // ��ġ
    float               m_magnification; // Ȯ�� ����

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

