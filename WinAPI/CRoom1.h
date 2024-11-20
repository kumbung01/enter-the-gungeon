#pragma once
#include "CMap.h"

class CCollider;

class CRoom1 :
    public CMap
{
private:
    CCollider* m_SpawnZone;
    int        m_SpawnCount;
    float      m_SpawnDelay;
    float      m_SpawnAccTime;

private:
    virtual void CreateMap(int row, int col) override;
    void SpawnMonsters();
public:
    CRoom1();
    CRoom1(float x, float y);
    ~CRoom1();

public:
    virtual void Tick() override;

public:
    virtual void BeginOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider) override;
};

