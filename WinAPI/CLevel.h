#pragma once
#include "CBase.h"

class CObj;

class CLevel :
    public CBase
{
private:
    vector<CObj*>   m_vecObjects[(UINT)LAYER_TYPE::END];

public:
    // 시점함수 
    //  Begin       : 레벨이 시작될 때, Object 들에게 호출
    //  Tcik        : 매 프레임마다 Object 들이 수행할 작업
    //  FinalTick   : 매 프레임마다 Object 의 Component 들이 수행할 작업
    //  Render      : 매 프레임마다 Object 가 화면에 그려질 때
    void Begin();
    void Tick();
    void FinalTick();
    void Render();    

public:
    void AddObject(CObj* _Object, LAYER_TYPE _Type) { m_vecObjects[(UINT)_Type].push_back(_Object); }

public:
    CLevel();
    ~CLevel();
};

