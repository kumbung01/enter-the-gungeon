#pragma once
#include "CBase.h"

class CComponent;
class CCollider;

class CObj :
    public CBase
{
private:
    Vec2                m_Pos;
    Vec2                m_Scale;
    vector<CComponent*> m_Component;
    LAYER_TYPE          m_LayerType;

    bool                m_Dead;         // ���� ����

public:
    virtual void Begin();               // ���� ������ ��
    virtual void Tick() = 0;            // ������Ʈ�� �� ��
    virtual void FinalTick() final;     // ������Ʈ�� ������ Component �� �� ��
    virtual void Render();              // ������Ʈ�� �׸���

    virtual void BeginOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider) {}
    virtual void Overlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider) {}
    virtual void EndOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider) {}



public:
    void SetPos(Vec2 _Pos) { m_Pos = _Pos; }
    void SetPos(float _x, float _y) { m_Pos = Vec2(_x, _y); }
    void SetScale(Vec2 _Scale) { m_Scale = _Scale; }
    void SetScale(float _x, float _y) { m_Scale = Vec2(_x, _y); }

    Vec2 GetPos() { return m_Pos; }
    Vec2 GetScale() { return m_Scale; }
    LAYER_TYPE GetLayerType() { return m_LayerType; }

    bool IsDead() { return m_Dead; }

    CComponent* AddComponent(CComponent* _Component);
    CComponent* GetComponent(const wstring& _Name);
    CComponent* GetComponent(COMPONENT_TYPE _Type);

    template<typename T>
    T* GetComponent();

public:
    CObj();
    ~CObj();

    friend class CLevel;
    friend class CTaskMgr;
};

template<typename T>
T* CObj::GetComponent()
{
    for (size_t i = 0; i < m_Component.size(); ++i)
    {
        if (dynamic_cast<T*>(m_Component[i]))
            return (T*)m_Component[i];
    }

    return nullptr;
}
