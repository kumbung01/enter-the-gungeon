#pragma once
#include "CComponent.h"

class CTexture;

class CTileMap :
    public CComponent
{
private:
    int         m_Col;              // 타일 열 개수
    int         m_Row;              // 타일 행 개수    

    CTexture*   m_Atlas;
    int         m_AtlasTileCol;     // 아틀라스 텍스쳐 안에 있는 타일 열 개수
    int         m_AtlasTileRow;     // 아틀라스 텍스쳐 안에 있는 타일 행 개수
    Vec2        m_AtlasResolution;  // 아틀라스 해상도

public:
    void SetRowCol(int Row, int Col) { m_Row = Row, m_Col = Col; }
    void SetAtlasTexture(CTexture* _Atlas);
    
        
    
    

public:
    virtual void FinalTick() override;
    void Render();

public:
    CTileMap();
    ~CTileMap();
};

