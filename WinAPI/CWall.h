#pragma once
#include "CObj.h"

class CTileMap;
class CWall :
    public CObj
{
private:
    CTileMap* m_TileMap;

public:
    void LoadTileMap(wstring _FullPath);
    void SaveTileMap(wstring _FullPath);
    void SetTileImgIdx(int row, int col, int idx);
public:
    virtual void Tick() override;
    virtual void Render() override;
public:
    CWall(int row, int col);
    ~CWall();
};

