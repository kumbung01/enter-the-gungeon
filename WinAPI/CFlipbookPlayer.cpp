#include "pch.h"
#include "CFlipbookPlayer.h"

#include "CTimeMgr.h"
#include "CFlipbook.h"

#include "CEngine.h"
#include "CSprite.h"
#include "CTexture.h"

CFlipbookPlayer::CFlipbookPlayer()
	: CComponent(COMPONENT_TYPE::FLIPBOOKPLAYER)
	, m_CurFlipbook(nullptr)
	, m_SpriteIdx(0)
	, m_FPS(0.f)
	, m_Time(0.f)
	, m_Repeat(false)
	, m_Finish(false)
	, m_mirror(false)
	, m_magnification(1.f)
{
}

CFlipbookPlayer::~CFlipbookPlayer()
{
}

void CFlipbookPlayer::FinalTick()
{
	// 현재 재생중인 Flipbook 이 없으면 끝
	if (nullptr == m_CurFlipbook)
	{
		return;
	}

	if (m_Finish)
	{	
		// 반복 재생하기로 했으면 다시 0 번 스프라이트로 인덱스를 변경한다.
		if (m_Repeat)
			Reset();

		// 한번 재생이 끝났고(m_Finish), 반복 재생모드가 아니라면
		// 마지막 프레임을 유지하도록 한다.
		else
			return;
	}	

	// FPS 에 따른 시간체크
	m_Time += DT;
	if (1.f / m_FPS <= m_Time)
	{
		m_Time -= 1.f / m_FPS;
		++m_SpriteIdx;

		// 마지막 Sprite 에 도달했다면
		if (m_CurFlipbook->GetMaxSpriteCount() <= m_SpriteIdx)
		{
			// Finish 상태 On
			m_Finish = true;
			--m_SpriteIdx;
		}
	}
}

void CFlipbookPlayer::Render()
{
	if (nullptr == m_CurFlipbook)
		return;

	CSprite* Sprite = m_CurFlipbook->GetSprite(m_SpriteIdx);

	switch (Sprite->GetRenderType())
	{
	case RENDER_BITBLT:
		RenderBitBlt(Sprite);
		break;
	case RENDER_GDIPLUS:
	default:
		RenderGdiPlus(Sprite);
		break;
	}
}

void CFlipbookPlayer::RenderBitBlt(CSprite* Sprite)
{
	HDC bufDC = CEngine::GetInst()->GetBufferDC();
	HDC backDC = CEngine::GetInst()->GetSecondDC();
	CTexture* tex = Sprite->GetAtlas();
	Vec2 sliceSrc = Sprite->GetSlice();
	Vec2 sliceDst = sliceSrc * m_magnification;
	Vec2 leftTop = Sprite->GetLeftTop();
	Vec2 vPos = GetOwner()->GetRenderPos() - sliceDst / 2.f;

	StretchBlt(bufDC,
		m_mirror ? sliceDst.x : 0, 
		0,
		m_mirror ? -sliceDst.x - 1: sliceDst.x,
		sliceDst.y,
		tex->GetDC(),
		leftTop.x,
		leftTop.y,
		sliceSrc.x,
		sliceSrc.y,
		SRCCOPY);

	TransparentBlt(backDC,
		vPos.x,
		vPos.y,
		sliceDst.x,
		sliceDst.y,
		bufDC,
		0, 0,
		sliceDst.x,
		sliceDst.y,
		RGB(255, 0, 255));
}

void CFlipbookPlayer::RenderGdiPlus(CSprite* Sprite)
{
	// Sprite 를 화면에 그린다.
	Gdiplus::Graphics* graphics = CEngine::GetInst()->GetBackGraphics();
	Vec2 vPos = GetOwner()->GetRenderPos();
	Vec2 center = Sprite->GetSlice() / 2.f;

	Matrix mat;
	mat.Translate(vPos.x + m_offset.x, vPos.y + m_offset.y);
	mat.Scale(m_magnification, m_magnification);
	if (m_mirror)
		mat.Scale(-1.f, 1.f);
	mat.RotateAt(m_angle, { m_axis.x, m_axis.y });
	mat.Translate(-center.x, -center.y);
	graphics->SetTransform(&mat);

	auto res = graphics->DrawImage(Sprite->GetAtlas()->GetImage(),
		0.f, 0.f,
		Sprite->GetLeftTop().x, Sprite->GetLeftTop().y,
		Sprite->GetSlice().x - (m_mirror ? 1 : 0), Sprite->GetSlice().y, UnitPixel);

	graphics->ResetTransform();
}
