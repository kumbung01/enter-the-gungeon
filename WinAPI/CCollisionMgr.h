#pragma once


class CCollisionMgr
{
	SINGLE(CCollisionMgr);
private:
	UINT	m_Matrix[(UINT)LAYER_TYPE::END];

public:
	void CollisionCheck(LAYER_TYPE _Left, LAYER_TYPE _Right);


public:
	void Tick();
};

