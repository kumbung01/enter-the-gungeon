#pragma once

class CCamera
{
	SINGLE(CCamera);
private:
	Vec2	m_LookAt;	// ī�޶� �ٶ󺸰� �ִ� ��
	Vec2	m_Diff;		// ī�޶� ���� ������ �ػ� �߾��� ��ġ ���̰�
	CObj*	m_Target;	// ī�޶� Ÿ�� ������Ʈ

public:
	void Init();
	void Tick();
	void Render();

public:
	Vec2 GetRenderPos(Vec2 _RealPos) { return _RealPos - m_Diff; }
};

