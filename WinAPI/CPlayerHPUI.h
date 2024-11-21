#pragma once
#include "CObj.h"

class CPlayer;

class CPlayerHPUI 
	:public CObj
{
private:
	int m_HP;
	CPlayer* m_Player;
public:
	void Begin() override;
	void Tick() override;
	void Render() override;
public:
	CPlayerHPUI();
	~CPlayerHPUI();
};

