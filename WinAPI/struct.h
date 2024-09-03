#pragma once

struct Vec2
{
public:
	float x;
	float y;

public:
	Vec2 operator + (Vec2 _Other)
	{
		return Vec2(x + _Other.x, y + _Other.y);
	}



public:
	Vec2()
		: x(0.f)
		, y(0.f)
	{}

	Vec2(float _x, float _y)
		: x(_x)
		, y(_y)
	{}

	Vec2(POINT _pt)
		: x((float)_pt.x)
		, y((float)_pt.y)
	{}

	Vec2(int _x, int _y)
		: x((float)_x)
		, y((float)_y)
	{}


	~Vec2()
	{}


};


struct tTask
{
	TASK_TYPE	Type;
	DWORD_PTR	Param0;
	DWORD_PTR	Param1;
};


struct tDbgRenderInfo
{
	DEBUG_SHAPE		Type;
	Vec2			Position0;
	Vec2			Position1;
	Vec2			Scale;
	UINT			Color;
	float			Duration;	// 표시 시간
	float			Time;		// 진행 시간
};