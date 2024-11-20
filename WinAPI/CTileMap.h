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
    float           m_Magnification;

    // �� Ÿ�ϸ��� �ڽ��� ���ϴ� �̹����� �� �� �־����
    vector<tTile>   m_vecTileInfo;

public:
    void SetRowCol(int Row, int Col);
    void SetAtlasTexture(CTexture* _Atlas);    
    tTile* GetTileInfo(Vec2 _MousePos);

    void SetMagnification(float _Magnification) { m_Magnification = _Magnification; }
    void SetTileImgIdx(int row, int col, int idx) { m_vecTileInfo[m_Col * row + col].ImgIdx = idx; }
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

