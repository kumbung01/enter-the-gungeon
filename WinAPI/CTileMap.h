#pragma once
#include "CComponent.h"

class CTexture;

class CTileMap :
    public CComponent
{
private:
    int         m_Col;              // Ÿ�� �� ����
    int         m_Row;              // Ÿ�� �� ����    

    CTexture*   m_Atlas;
    int         m_AtlasTileCol;     // ��Ʋ�� �ؽ��� �ȿ� �ִ� Ÿ�� �� ����
    int         m_AtlasTileRow;     // ��Ʋ�� �ؽ��� �ȿ� �ִ� Ÿ�� �� ����
    Vec2        m_AtlasResolution;  // ��Ʋ�� �ػ�

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

