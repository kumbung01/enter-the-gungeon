#pragma once
#include "CBase.h"
#include "CObj.h"

//class CObj;
class CCollider;

struct cmp {
    bool operator()(CObj* a, CObj* b)
    {
        if (a->GetLayerType() == b->GetLayerType()) {
            return a->GetPos().y > b->GetPos().y;
        }
        
        bool isAUi = (int)a->GetLayerType() > (int)LAYER_TYPE::UIS;
        bool isBUi = (int)b->GetLayerType() > (int)LAYER_TYPE::UIS;

        if (isAUi != isBUi)
            return isAUi;

        return a->GetPos().y > b->GetPos().y;
    }
};

class CLevel :
    public CBase
{
private:
    vector<CObj*>                                       m_vecObjects[(UINT)LAYER_TYPE::END];
    vector<CCollider*>                                  m_vecCollider[(UINT)LAYER_TYPE::END];
    std::priority_queue<CObj*, std::vector<CObj*>, cmp> m_renderQueue;
public:
    // �����Լ� 
    //  Begin       : ������ ���۵� ��, Object �鿡�� ȣ��
    //  Tcik        : �� �����Ӹ��� Object ���� ������ �۾�
    //  FinalTick   : �� �����Ӹ��� Object �� Component ���� ������ �۾�
    //  Render      : �� �����Ӹ��� Object �� ȭ�鿡 �׷��� ��    
    //  End         : ������ ����ɶ� ȣ��Ǵ� �Լ�
    virtual void Begin(); 
    virtual void Tick();
    virtual void FinalTick();
    virtual void Render();
    virtual void End() = 0; 

public:
    void AddObject(CObj* _Object, LAYER_TYPE _Type);
    const vector<CObj*>& GetObjects(LAYER_TYPE _Type) { return m_vecObjects[(UINT)_Type]; }

    // Collider �� ���̾� ��ȣ�� �´� ���� ���
    void RegisterCollider(CCollider* _Collider, LAYER_TYPE _Type) { m_vecCollider[(UINT)_Type].push_back(_Collider); }
    const vector<CCollider*>& GetColliders(LAYER_TYPE _Type) { return m_vecCollider[(UINT)_Type]; }

    CObj* FindObjectByName(LAYER_TYPE _Layer, const wstring& _Name);

protected:
    void DeleteObjects(int _LayerIdx);
    void DeleteAllObject();

public:
    CLevel();
    ~CLevel();

    friend class CUIMgr;
};

