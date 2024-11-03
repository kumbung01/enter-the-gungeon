#include "pch.h"
#include "CAtlas.h"
#include "CTexture.h"
#include "CKeyMgr.h"
#include "CDbgRender.h"
#include "CCamera.h"
#include "CEngine.h"
#include "CAssetMgr.h"

void CAtlas::LoadTexture(const wstring& _key, const wstring& _filePath)
{
	m_tex = CAssetMgr::GetInst()->LoadTexture(_key, L"Texture/" + _filePath);
	//m_leftTop = GetPos() - Vec2((float)m_tex->GetWidth(), (float)m_tex->GetHeight());
	m_leftTop = GetPos();
}

void CAtlas::AddSprite()
{
	Vec2 startPos = m_pos.leftTop;
	Vec2 endPos = m_pos.rightBottom;

	KEY_STATE keyState = CKeyMgr::GetInst()->GetKeyState(KEY::Q);

	switch (keyState)
	{
	case KEY_STATE::TAP:
	{
		startPos = CCamera::GetInst()->GetRealPos(CKeyMgr::GetInst()->GetMousePos());
		break;
	}
	case KEY_STATE::PRESSED:
	{
		endPos = CCamera::GetInst()->GetRealPos(CKeyMgr::GetInst()->GetMousePos());
		Vec2 pos = (startPos + endPos) / 2.f;
		Vec2 scale = endPos - startPos;
		DrawDebugRect(PEN_TYPE::GREEN, CCamera::GetInst()->GetRenderPos(pos), scale, 0.f);
		break;
	}
	case KEY_STATE::RELEASED:
		// atlas 로부터의 상대적인 위치만을 저장하기 위함
		startPos -= GetPos();
		startPos /= m_magnification;
		startPos.Round();

		endPos = CCamera::GetInst()->GetRealPos(CKeyMgr::GetInst()->GetMousePos()) - GetPos();
		endPos /= m_magnification;
		endPos.Round();

		if ((endPos - startPos).Length() < 1.14f)
			break;

		m_sprites.push_back({ startPos, endPos});
		break;
	default:
		break;
	}

	for (auto m_sprite : m_sprites)
	{
		Vec2 pos = (m_sprite.leftTop * m_magnification + m_sprite.rightBottom * m_magnification) / 2.f + GetPos();
		Vec2 scale = (m_sprite.rightBottom - m_sprite.leftTop) * m_magnification;
		DrawDebugRect(PEN_TYPE::GREEN, CCamera::GetInst()->GetRenderPos(pos), scale, 0.f);
	}

	m_pos.leftTop = startPos;
	m_pos.rightBottom = endPos;
}

void CAtlas::Tick()
{
	if (m_tex == nullptr)
		return;

	AddSprite();

	if (KEY_TAP(KEY::CTRL))
	{
		if (m_sprites.size() > 0)
			m_sprites.pop_back();
	}
}

void CAtlas::Render()
{
	if (m_tex == nullptr)
		return;

	HDC hBackDC = CEngine::GetInst()->GetSecondDC();
	Vec2 vPos = GetRenderPos();
	float width = m_tex->GetWidth();
	float height = m_tex->GetHeight();


	StretchBlt(
		hBackDC
		, vPos.x, vPos.y
		, width * m_magnification, height * m_magnification
		, m_tex->GetDC()
		, 0, 0
		, width, height
		, SRCCOPY);

	DrawDebugCircle(PEN_TYPE::RED, CCamera::GetInst()->GetRenderPos(m_leftTop), Vec2(10.f, 10.f), 0.f);
}

CAtlas::CAtlas()
	: m_magnification(10.f)
	, m_tex(nullptr)
{
}

CAtlas::~CAtlas()
{
}
