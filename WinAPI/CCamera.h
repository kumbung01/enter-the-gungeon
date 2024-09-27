#pragma once

class CCamera
{
	SINGLE(CCamera);
private:
	Vec2	m_LookAt;	// 카메라가 바라보고 있는 곳
	Vec2	m_Diff;		// 카메라가 보는 지점과 해상도 중앙의 위치 차이값
	CObj*	m_Target;	// 카메라 타겟 오브젝트

public:
	void Init();
	void Tick();
	void Render();

public:
	Vec2 GetRenderPos(Vec2 _RealPos) { return _RealPos - m_Diff; }
};

