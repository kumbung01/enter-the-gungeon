#pragma once
#include "CComponent.h"

class CTexture;

class CTileMap :
    public CComponent
{
private:
    int             m_Col;              // Ÿ�� �� ����
    int             m_Row;              // Ÿ�� �� ����    

    CTexture*       m_Atlas;
    int             m_AtlasTileCol;     // ��Ʋ�� �ؽ��� �ȿ� �ִ� Ÿ�� �� ����
    int             m_AtlasTileRow;     // ��Ʋ�� �ؽ��� �ȿ� �ִ� Ÿ�� �� ����
    Vec2            m_AtlasResolution;  // ��Ʋ�� �ػ�

    // �� Ÿ�ϸ��� �ڽ��� ���ϴ� �̹����� �� �� �־����
    vector<tTile>   m_vecTileInfo;

public:
    void SetRowCol(int Row, int Col);
    void SetAtlasTexture(CTexture* _Atlas);    
    tTile* GetTileInfo(Vec2 _MousePos);

public:
    bool SaveTileMap(wstring _FullPath);
    bool LoadTileMap(wstring _FullPath);


public:
    virtual void FinalTick() override;
    void Render();

public:
    CTileMap();
    ~CTileMap();
};

