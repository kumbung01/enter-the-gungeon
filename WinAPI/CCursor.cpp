#include "pch.h"
#include "CCursor.h"
#include "CCamera.h"
#include "CDbgRender.h"
#include "CKeyMgr.h"

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
}