#pragma once
#include "CBase.h"

class CObj;
class CCollider;

class CLevel :
    public CBase
{
private:
    vector<CObj*>       m_vecObjects[(UINT)LAYER_TYPE::END];
    vector<CCollider*>  m_vecCollider[(UINT)LAYER_TYPE::END];


public:
    // �����Լ� 
    //  Begin       : ������ ���۵� ��, Object �鿡�� ȣ��
    //  Tcik        : �� �����Ӹ��� Object ���� ������ �۾�
    //  FinalTick   : �� �����Ӹ��� Object �� Component ���� ������ �۾�
    //  Render      : �� �����Ӹ��� Object �� ȭ�鿡 �׷��� ��
    void Begin();
    void Tick();
    void FinalTick();
    void Render();    

public:
    void AddObject(CObj* _Object, LAYER_TYPE _Type) 
    { 
        m_vecObjects[(UINT)_Type].push_back(_Object); 
        _Object->m_LayerType = _Type; // ������Ʈ�� �Ҽ� ���̾ �˷���
    }

    // Collider �� ���̾� ��ȣ�� �´� ���� ���
    void RegisterCollider(CCollider* _Collider, LAYER_TYPE _Type) { m_vecCollider[(UINT)_Type].push_back(_Collider); }
    const vector<CCollider*>& GetColliders(LAYER_TYPE _Type) { return m_vecCollider[(UINT)_Type]; }



public:
    CLevel();
    ~CLevel();
};

