#pragma once
#include "CBase.h"
#include "CObj.h"

//class CObj;
class CCollider;

struct cmp {
    bool operator()(CObj* a, CObj* b)
    {
        if (a->GetLayerType() == b->GetLayerType()) {
            return a->GetPos().y + a->GetRenderOffset() > b->GetPos().y + b->GetRenderOffset();
        }
        
        bool isATile = (a->GetLayerType() > LAYER_TYPE::TILE);
        bool isBTile = (b->GetLayerType() > LAYER_TYPE::TILE);

        if (isATile != isBTile) {
            return isATile;
        }

        bool isAUi = (int)a->GetLayerType() > (int)LAYER_TYPE::UIS;
        bool isBUi = (int)b->GetLayerType() > (int)LAYER_TYPE::UIS;

        if (isAUi != isBUi)
            return isAUi;

        return a->GetPos().y + a->GetRenderOffset() > b->GetPos().y + b->GetRenderOffset();
    }
};

class CLevel :
    public CBase
{
private:
    vector<CObj*>                                       m_vecObjects[(UINT)LAYER_TYPE::END];
    vector<CCollider*>                                  m_vecCollider[(UINT)LAYER_TYPE::END];
    std::priority_queue<CObj*, std::vector<CObj*>, cmp> m_renderQueue;
protected:
    int m_renderCount;
public:
    // 시점함수 
    //  Begin       : 레벨이 시작될 때, Object 들에게 호출
    //  Tcik        : 매 프레임마다 Object 들이 수행할 작업
    //  FinalTick   : 매 프레임마다 Object 의 Component 들이 수행할 작업
    //  Render      : 매 프레임마다 Object 가 화면에 그려질 때    
    //  End         : 레벨이 종료될때 호출되는 함수
    virtual void Begin(); 
    virtual void Tick();
    virtual void FinalTick();
    virtual void Render();
    virtual void End() = 0; 

public:
    void AddObject(CObj* _Object, LAYER_TYPE _Type);
    const vector<CObj*>& GetObjects(LAYER_TYPE _Type) { return m_vecObjects[(UINT)_Type]; }

    // Collider 를 레이어 번호에 맞는 곳에 등록
    void RegisterCollider(CCollider* _Collider, LAYER_TYPE _Type) { m_vecCollider[(UINT)_Type].push_back(_Collider); }
    const vector<CCollider*>& GetColliders(LAYER_TYPE _Type) { return m_vecCollider[(UINT)_Type]; }

    CObj* FindObjectByName(LAYER_TYPE _Layer, const wstring& _Name);

    bool IsInCamera(CObj* obj);

    int  GetObjCount(LAYER_TYPE _layer);

protected:
    void DeleteObjects(int _LayerIdx);
    void DeleteAllObject();

public:
    CLevel();
    ~CLevel();

    friend class CUIMgr;
};

