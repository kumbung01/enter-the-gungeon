#pragma once
#include "CMap.h"

class CCorridor
	: public CMap
{
private:
	bool m_isVertical;
public:
	virtual void CreateMap(int row, int col) override;
public:
	CCorridor();
	CCorridor(float x, float y, int row, int col, bool vertical);
	~CCorridor();
};

