#include "pch.h"
#include "CPlayer.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CTaskMgr.h"

#include "CMissile.h"
#include "CLevelMgr.h"
#include "CLevel.h"


CPlayer::CPlayer()
	: m_Speed(200.f)
	, m_AttSpeed(10.f)
	, m_AccTime(0.f)
{
}

CPlayer::~CPlayer()
{
}

void CPlayer::Begin()
{
	m_AccTime = 1.f / m_AttSpeed;
}

void CPlayer::Tick()
{
	Vec2 vPos = GetPos();

	if (KEY_PRESSED(LEFT))
		vPos.x -= DT * m_Speed;
	if (KEY_PRESSED(RIGHT))
		vPos.x += DT * m_Speed;
	if (KEY_PRESSED(UP))
		vPos.y -= DT * m_Speed;
	if (KEY_PRESSED(DOWN))
		vPos.y += DT * m_Speed;

	
	// 미사일 발사
	if (KEY_PRESSED(SPACE))
	{
		// 시간체크
		m_AccTime += DT;

		if (1.f / m_AttSpeed <= m_AccTime)
		{
			m_AccTime -= 1.f / m_AttSpeed;

			// 미사일 생성
			for (int i = 0; i < 3; ++i)
			{
				CMissile* pMissile = new CMissile;
				pMissile->SetPos(vPos + Vec2(-20.f + i * 20.f, -GetScale().y / 2.f));
				pMissile->SetScale(20.f, 20.f);
				
				tTask task = {};
				task.Type = TASK_TYPE::CREATE_OBJECT;
				task.Param0 = (DWORD_PTR)pMissile;

				CTaskMgr::GetInst()->AddTask(task);
			}
		}
	}

	else if (KEY_RELEASED(SPACE))
	{
		m_AccTime = 1.f / m_AttSpeed;
	}


	SetPos(vPos);
}