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
	// �Է����� ���� ���̾� ��ȣ�߿��� �� �������� Matrix �� ������, �� ū���� ���� ����Ѵ�.
	UINT Row = (UINT)_Left;
	UINT Col = (UINT)_Right;

	if (Col < Row)
	{
		Row = (UINT)_Right;
		Col = (UINT)_Left;
	}

	// �̹� üũ�� �Ǿ�������
	if (m_Matrix[Row] & (1 << Col))
	{
		// ��Ʈ�� ����.
		m_Matrix[Row] &= ~(1 << Col);
	}

	// üũ�� �ȵǾ�������
	else
	{
		// üũ�Ѵ�.
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

	// ���� �ٸ� ���̾�� �浹 �˻�
	if (_Left != _Right)
	{
		for (size_t i = 0; i < vecLeft.size(); ++i)
		{
			for (size_t j = 0; j < vecRight.size(); ++j)
			{

			}
		}
	}

	// ���� ���̾�� �浹 �˻�
	else
	{
		// �ߺ� �˻� or �ڱ��ڽŰ��� �˻縦 ���ϱ� ���ؼ� j �� i + 1 ���� �����Ѵ�.
		for (size_t i = 0; i < vecLeft.size(); ++i)
		{
			for (size_t j = i + 1; j < vecRight.size(); ++j)
			{

			}
		}
	}
}