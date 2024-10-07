#pragma once

class CCamera
{
	SINGLE(CCamera);
private:
	Vec2	m_LookAt;	// 카메라가 바라보고 있는 곳
	Vec2	m_Diff;		// 카메라가 보는 지점과 해상도 중앙의 위치 차이값
	Vec2	m_Offset;	// 카메라가 바라보는 위치에서 추가적인 Offset

	CObj*	m_Target;	// 카메라 타겟 오브젝트

	float	m_Duration;    // 진동 유지시간
	float	m_Amplitude;   // 진촉
	float	m_Frequency;   // 초당 진동횟수
	float	m_Time;		   // 누적시간
	float   m_Dir;		   // 진동 방향
	bool	m_bOscillation;// 진동 On / Off

public:
	void Init();
	void Tick();
	void Render();

private:
	void Oscillation();

public:
	Vec2 GetRenderPos(Vec2 _RealPos)  {  return _RealPos - m_Diff;  }
	Vec2 GetRealPos(Vec2 _RenderPos) { return _RenderPos + m_Diff; }

	Vec2 GetLookAt() { return m_LookAt + m_Offset; }
	void SetTarget(CObj* _Target) { m_Target = _Target; }
	void Oscillation(float _Duration, float _Amplitude, float _Frequency)
	{
		m_Duration = _Duration;
		m_Amplitude = _Amplitude;
		m_Frequency = _Frequency;
		m_Time = 0.f;
		m_bOscillation = true;
		m_Dir = 1.f;
	}
};

