#pragma once

class CTexture;

enum POST_PROCESS
{
	FADE_IN,
	FADE_OUT,
	HEART,
};

class CCamera
{
	SINGLE(CCamera);
private:
	Vec2		m_LookAt;	// ī�޶� �ٶ󺸰� �ִ� ��
	Vec2		m_Diff;		// ī�޶� ���� ������ �ػ� �߾��� ��ġ ���̰�
	Vec2		m_Offset;	// ī�޶� �ٶ󺸴� ��ġ���� �߰����� Offset

	CObj*		m_Target;	// ī�޶� Ÿ�� ������Ʈ

	float		m_Duration;    // ���� �����ð�
	float		m_Amplitude;   // ����
	float		m_Frequency;   // �ʴ� ����Ƚ��
	float		m_Time;		   // �����ð�
	float		m_Dir;		   // ���� ����
	bool		m_bOscillation;// ���� On / Off

	CTexture*	m_CamTex;


	// PostProcess( �� ó�� )
	POST_PROCESS	m_Effect;		// �������� ȿ�� ����
	bool			m_PostProcess;	// ȿ�� On / Off
	float			m_PPTime;		// ȿ�� ����ð� ���
	float			m_PPDuration;	// ȿ�� �ִ� ���� �ð�
	


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

	void PostProcessEffect(POST_PROCESS _Type, float _Duration)
	{
		m_Effect = _Type;
		m_PPDuration = _Duration;
		m_PPTime = 0.f;
		m_PostProcess = true;
	}
};

