#pragma once


class CCollisionMgr
{
	SINGLE(CCollisionMgr);
private:
	UINT	m_Matrix[(UINT)LAYER_TYPE::END];

public:
	void CollisionCheck(LAYER_TYPE _Left, LAYER_TYPE _Right);
	void CollisionCheckClear() { memset(m_Matrix, 0, sizeof(UINT) * (UINT)LAYER_TYPE::END); }

private:
	void CollisionBtwLayer(LAYER_TYPE _Left, LAYER_TYPE _Right);


public:
	void Tick();
};

