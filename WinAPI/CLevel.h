#pragma once
#include "CBase.h"

class CObj;

class CLevel :
    public CBase
{
private:
    vector<CObj*>   m_vecObjects[(UINT)LAYER_TYPE::END];

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
    void AddObject(CObj* _Object, LAYER_TYPE _Type) { m_vecObjects[(UINT)_Type].push_back(_Object); }

public:
    CLevel();
    ~CLevel();
};

