#include "pch.h"
#include "CCollisionMgr.h"

#include "CLevelMgr.h"
#include "CLevel.h"
#include "CObj.h"
#include "CCollider.h"

CCollisionMgr::CCollisionMgr()
	: m_Matrix{}
{
}

CCollisionMgr::~CCollisionMgr()
{

}

void CCollisionMgr::CollisionCheck(LAYER_TYPE _Left, LAYER_TYPE _Right)
{
	// 입력으로 들어온 레이어 번호중에서 더 작은값을 Matrix 의 행으로, 더 큰값을 열로 사용한다.
	UINT Row = (UINT)_Left;
	UINT Col = (UINT)_Right;

	if (Col < Row)
	{
		Row = (UINT)_Right;
		Col = (UINT)_Left;
	}

	// 이미 체크가 되어있으면
	if (m_Matrix[Row] & (1 << Col))
	{
		// 비트를 뺀다.
		m_Matrix[Row] &= ~(1 << Col);
	}

	// 체크가 안되어있으면
	else
	{
		// 체크한다.
		m_Matrix[Row] |= (1 << Col);
	}
}

void CCollisionMgr::Tick()
{
	for (UINT Row = 0; Row < (UINT)LAYER_TYPE::END; ++Row)
	{
		for (UINT Col = Row; Col < (UINT)LAYER_TYPE::END; ++Col)
		{
			if (!(m_Matrix[Row] & (1 << Col)))
				continue;

			CollisionBtwLayer((LAYER_TYPE)Row, (LAYER_TYPE)Col);
		}
	}
}


void CCollisionMgr::CollisionBtwLayer(LAYER_TYPE _Left, LAYER_TYPE _Right)
{
	const vector<CCollider*>& vecLeft = CLevelMgr::GetInst()->GetCurrentLevel()->GetColliders(_Left);
	const vector<CCollider*>& vecRight = CLevelMgr::GetInst()->GetCurrentLevel()->GetColliders(_Right);

	// 서로 다른 레이어간의 충돌 검사
	if (_Left != _Right)
	{
		for (size_t i = 0; i < vecLeft.size(); ++i)
		{
			for (size_t j = 0; j < vecRight.size(); ++j)
			{

			}
		}
	}

	// 동일 레이어간의 충돌 검사
	else
	{
		// 중복 검사 or 자기자신과의 검사를 피하기 위해서 j 는 i + 1 부터 시작한다.
		for (size_t i = 0; i < vecLeft.size(); ++i)
		{
			for (size_t j = i + 1; j < vecRight.size(); ++j)
			{

			}
		}
	}
}