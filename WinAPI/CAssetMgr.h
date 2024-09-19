#pragma once

class CTexture;
class CSprite;

class CAssetMgr
{
	SINGLE(CAssetMgr);
private:
	map<wstring, CTexture*>		m_mapTex;	
	map<wstring, CSprite*>		m_mapSprite;
	//map<wstring, CSound*>		m_mapFlipbook;
	//map<wstring, CSound*>		m_mapSound;

public:	
	void Init();



	CTexture* FindTexture(const wstring& _Key);
	CTexture* LoadTexture(const wstring& _Key, const wstring& _RelativePath);
	
	CSprite* FindSprite(const wstring& _Key);
	CSprite* LoadSprite(const wstring& _Key, const wstring& _RelativePath);
	void AddSprite(const wstring& _Key, CSprite* _Sprite);


	//CSound* LoadSound();
	//CSound* FindSound();
};

