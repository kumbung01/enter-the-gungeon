#pragma once
#include "CObj.h"

class CTileMap;

class CMap :
    public CObj
{
protected:
    CTileMap*   m_TileMap;
    virtual void CreateMap(int row, int col) = 0;
    virtual void CreateTileMap(int row, int col);

public:
    CTileMap* GetTileMap() { return m_TileMap; }
    virtual void Tick() override;
    virtual void Render() override;

public:
    CMap();
    ~CMap();
};

