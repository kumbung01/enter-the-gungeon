#pragma once
#include "CBase.h"

class CObj;

class CLevel :
    public CBase
{
private:
    vector<CObj*>   m_vecObjects;

public:
    // �����Լ� 
    //  Begin       : ������ ���۵� ��
    //  Tcik        : �� �����Ӹ��� Object ���� ������ �۾�
    //  FinalTick   : �� �����Ӹ��� Object �� Component ���� ������ �۾�
    //  Render      : �� �����Ӹ��� Object �� ȭ�鿡 �׷��� ��
    void Begin();
    void Tick();
    void FinalTick();
    void Render();    

public:
    void AddObject(CObj* _Object) { m_vecObjects.push_back(_Object); }

public:
    CLevel();
    ~CLevel();
};

