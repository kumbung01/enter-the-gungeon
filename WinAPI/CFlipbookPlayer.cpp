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
	//, m_angle(0.f)
{
}

CFlipbookPlayer::~CFlipbookPlayer()
{
}

void CFlipbookPlayer::FinalTick()
{
	// ���� ������� Flipbook �� ������ ��
	if (nullptr == m_CurFlipbook)
	{
		return;
	}

	if (m_Finish)
	{	
		// �ݺ� ����ϱ�� ������ �ٽ� 0 �� ��������Ʈ�� �ε����� �����Ѵ�.
		if (m_Repeat)
			Reset();

		// �ѹ� ����� ������(m_Finish), �ݺ� �����尡 �ƴ϶��
		// ������ �������� �����ϵ��� �Ѵ�.
		else
			return;
	}	

	// FPS �� ���� �ð�üũ
	m_Time += DT;
	if (1.f / m_FPS <= m_Time)
	{
		m_Time -= 1.f / m_FPS;
		++m_SpriteIdx;

		// ������ Sprite �� �����ߴٸ�
		if (m_CurFlipbook->GetMaxSpriteCount() <= m_SpriteIdx)
		{
			// Finish ���� On
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

	if (GetOwner()->GetName() == L"Revolver") {
		wprintf(L"%s\n", Sprite->GetKey().c_str());
	}

	// Sprite �� ȭ�鿡 �׸���.
	Gdiplus::Graphics* graphics = CEngine::GetInst()->GetBackGraphics();
	Vec2 vPos = GetOwner()->GetRenderPos();
	Vec2 center = Sprite->GetSlice() / 2.f;

	Matrix mat;
	mat.Translate(vPos.x + m_offset.x, vPos.y + m_offset.y);
	mat.Scale(m_magnification, m_magnification);
	if (m_mirror)
		mat.Scale(-1.f, 1.f);
	mat.RotateAt(m_angle, {m_axis.x, m_axis.y});
	mat.Translate(-center.x, -center.y);
	graphics->SetTransform(&mat);

	auto res = graphics->DrawImage(Sprite->GetAtlas()->GetImage(),
		0.f, 0.f,
		Sprite->GetLeftTop().x, Sprite->GetLeftTop().y,
		Sprite->GetSlice().x, Sprite->GetSlice().y, UnitPixel);

	graphics->ResetTransform();

}