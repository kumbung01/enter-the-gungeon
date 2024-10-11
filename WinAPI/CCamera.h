#pragma once

class CTexture;

enum POST_PROCESS
{
	FADE_IN,
	FADE_OUT,
	HEART,
};

struct tCamEffect
{	
	POST_PROCESS	Effect;		// �������� ȿ�� ����	
	float			Time;		// ȿ�� ����ð� ���
	float			Duration;	// ȿ�� �ִ� ���� �ð�
};

class CCamera
{
	SINGLE(CCamera);
private:
	Vec2				m_LookAt;	// ī�޶� �ٶ󺸰� �ִ� ��
	Vec2				m_Diff;		// ī�޶� ���� ������ �ػ� �߾��� ��ġ ���̰�
	Vec2				m_Offset;	// ī�޶� �ٶ󺸴� ��ġ���� �߰����� Offset

	CObj*				m_Target;	// ī�޶� Ÿ�� ������Ʈ

	float				m_Duration;    // ���� �����ð�
	float				m_Amplitude;   // ����
	float				m_Frequency;   // �ʴ� ����Ƚ��
	float				m_Time;		   // �����ð�
	float				m_Dir;		   // ���� ����
	bool				m_bOscillation;// ���� On / Off

	CTexture*			m_CamTex;
	CTexture*			m_CamTex1;

	list<tCamEffect>	m_CamEffectList;
	
	


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
		m_CamEffectList.push_back(tCamEffect{ _Type , 0.f, _Duration });
	}
};

