#include "pch.h"
#include "CRevolver.h"
#include "CFlipbookPlayer.h"
#include "CAssetMgr.h"
#include "CKeyMgr.h"




bool CRevolver::IsTriggered()
{
	return KEY_PRESSED(KEY::LBTN);
}

void CRevolver::CreateFlipbook()
{
	CGun::CreateFlipbook();

	m_flipbookPlayer->AddFlipbook(GUN_IDLE,   CAssetMgr::GetInst()->LoadFlipbook(L"38special2_idle",   L"Flipbook\\Weapon\\38_special2_idle.flip"));
	m_flipbookPlayer->AddFlipbook(GUN_FIRE,   CAssetMgr::GetInst()->LoadFlipbook(L"38special2_fire",   L"Flipbook\\Weapon\\38_special2_fire.flip"));
	m_flipbookPlayer->AddFlipbook(GUN_RELOAD, CAssetMgr::GetInst()->LoadFlipbook(L"38special2_reload", L"Flipbook\\Weapon\\38_special2_reload.flip"));

	m_flipbookPlayer->SetAxis(Vec2(-6.f, 4.f));
}

CRevolver::CRevolver()
{
	m_bulletSpread = 0.5f;
	m_magnification = 2.f;
	
	CreateFlipbook();
}

CRevolver::~CRevolver()
{
}
