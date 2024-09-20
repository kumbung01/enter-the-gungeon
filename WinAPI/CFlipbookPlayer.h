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

    void Play(int _FlipbookIdx, float _FPS, bool _Repeat)
    {
        m_CurFlipbook = m_vecFlipbook[_FlipbookIdx];
        m_SpriteIdx = 0;
        m_FPS = _FPS;
        m_Repeat = _Repeat;
        m_Finish = false;
        m_Time = 0.f;
    }

    bool IsFinish() { return m_Finish; }

    void Reset()
    {
        m_Finish = false;
        m_SpriteIdx = 0;        
    }


public:
    virtual void FinalTick() override;
    void Render(); 

public:
    CFlipbookPlayer();
    ~CFlipbookPlayer();
};

