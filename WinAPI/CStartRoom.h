#pragma once
#include "CMap.h"


class CStartRoom
	: public CMap
{
private:
	virtual void CreateMap(int row, int col) override;
public:
	CStartRoom();
	CStartRoom(float x, float y);
	~CStartRoom();
};

