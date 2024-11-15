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
	// Ŀ�� �ؽ��� ����
	m_Tex = CAssetMgr::GetInst()->LoadTexture(L"Cursor", L"Texture\\cursor.png");
}

void CCursor::Tick()
{
	// Ŀ�� ��ġ Ȯ���Ͽ� ��ġ ����
	auto camMousePos = CKeyMgr::GetInst()->GetMousePos();
	SetPos(CCamera::GetInst()->GetRealPos(camMousePos));
}

void CCursor::Render()
{
	// Ŀ�� ��ġ�� �ؽ��� ����
	// �켱 ����׿�����Ʈ ���
	DrawDebugCircle(PEN_TYPE::GREEN,
					GetRenderPos(),
					GetScale(), 
					0.f);

	HDC backDC = CEngine::GetInst()->GetSecondDC();
	Vec2 vPos = GetRenderPos();

	TransparentBlt(backDC,
		vPos.x - m_Tex->GetWidth() / 2.f,
		vPos.y - m_Tex->GetHeight() / 2.f,
		m_Tex->GetWidth(),
		m_Tex->GetHeight(),
		m_Tex->GetDC(),
		0, 0,
		m_Tex->GetWidth(),
		m_Tex->GetHeight(),
		RGB(255, 0, 255));
}