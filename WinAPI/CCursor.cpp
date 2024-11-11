#include "pch.h"
#include "CCursor.h"
#include "CCamera.h"
#include "CDbgRender.h"
#include "CKeyMgr.h"
#include "CEngine.h"
#include "CAssetMgr.h"

CCursor::CCursor()
	: m_Tex(nullptr)
{

}

CCursor::~CCursor()
{

}

void CCursor::Begin()
{
	// 커서 텍스쳐 렌더
	m_Tex = CAssetMgr::GetInst()->LoadTexture(L"Cursor", L"Texture\\cursor.png");
}

void CCursor::Tick()
{
	// 커서 위치 확인하여 위치 변경
	auto camMousePos = CKeyMgr::GetInst()->GetMousePos();
	SetPos(CCamera::GetInst()->GetRealPos(camMousePos));
}

void CCursor::Render()
{
	// 커서 위치에 텍스쳐 렌더
	// 우선 디버그오브젝트 출력
	DrawDebugCircle(PEN_TYPE::GREEN,
					GetRenderPos(),
					GetScale(), 
					0.f);

	auto graphics = CEngine::GetInst()->GetBackGraphics();
	Vec2 vPos = GetRenderPos();

	float centerX = vPos.x - m_Tex->GetWidth() / 2.f;
	float centerY = vPos.y - m_Tex->GetHeight() / 2.f;
	
	graphics->DrawImage(m_Tex->GetImage(),
		(int)centerX, (int)centerY,
		(int)0, (int)0,
		m_Tex->GetWidth(), m_Tex->GetHeight(), UnitPixel);
}