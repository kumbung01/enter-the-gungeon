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
				CollisionBtwCollider(vecLeft[i], vecRight[j]);
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
				CollisionBtwCollider(vecLeft[i], vecRight[j]);
			}
		}
	}
}

void CCollisionMgr::CollisionBtwCollider(CCollider* _LeftCol, CCollider* _RightCol)
{
	COLLISION_ID ColID = {};
	ColID.Left = _LeftCol->GetID();
	ColID.Right = _RightCol->GetID();

	map<ULONGLONG, bool>::iterator iter = m_ColInfo.find(ColID.ID);

	// �� �浹ü ������ ��ϵ� ���� ����.
	if (iter == m_ColInfo.end())
	{
		// ����� ��Ų��.
		m_ColInfo.insert(make_pair(ColID.ID, false));
		iter = m_ColInfo.find(ColID.ID);
	}
	
	// ���� �����ִ�.
	if (IsCollision(_LeftCol, _RightCol))
	{
		// �������� �����־���.
		if (iter->second)
		{
			_LeftCol->Overlap(_RightCol);
			_RightCol->Overlap(_LeftCol);
		}

		// �������� �������� �ʾҴ�.
		else
		{
			_LeftCol->BeginOverlap(_RightCol);
			_RightCol->BeginOverlap(_LeftCol);
			iter->second = true; // �浹���� ����
		} 
	}

	// ���� ������ �ִ�.
	else
	{
		// �������� �����־���.
		if (iter->second)
		{
			_LeftCol->EndOverlap(_RightCol);
			_RightCol->EndOverlap(_LeftCol);
			iter->second = false;
		}
	}
}

bool CCollisionMgr::IsCollision(CCollider* _LeftCol, CCollider* _RightCol)
{
	Vec2 LeftPos = _LeftCol->GetFinalPos();
	Vec2 RightPos = _RightCol->GetFinalPos();

	Vec2 LeftScale = _LeftCol->GetScale();
	Vec2 RightScale = _RightCol->GetScale();
	Vec2 vDiff = LeftPos - RightPos;

	if (fabs(vDiff.x) < (LeftScale.x + RightScale.x) / 2.f
		&& fabs(vDiff.y) < (LeftScale.y + RightScale.y) / 2.f)
	{
		return true;
	}

	return false;
}