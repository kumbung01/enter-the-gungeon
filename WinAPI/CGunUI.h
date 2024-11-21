#pragma once
#include "CObj.h"

class CPlayer;
class CGun;

class CGunUI :
    public CObj
{
private:
	CPlayer* m_Player;
	Vec2     m_renderPos;
public:
	void Begin() override;
	void Tick() override;
	void Render() override;
public:
	CGunUI();
	~CGunUI();
};

