#pragma once

// ���α׷��� �ֻ��� ������

// �̱���
//  - ��ü ���� ������ 1���� ����

/*
class CEngine
{
private:
	int		m_Data;
		
public:
	void NormalMemberFunc()
	{
		m_Data = 100;
	}

	// CEngine ��ü�� ���� ��ȯ�ϴ� �Լ��� ����
	// �ɹ��Լ� �ȿ����� private �� ������ ����
	// �ɹ��Լ��� ȣ���Ϸ��� ��ü�� �ʿ�. ����, ���� �ɹ��Լ��� �����.

	// ���� �ɹ��Լ�
	//  - ��ü ���� ȣ�� ������ �ɹ��Լ� --> this �� ����
	//  - private �� ���� ����

	// �ϳ��� ��ü�� ����, ������ ���� ��ü�� ��ȯ
	// 1. ��ü�� Data ������ ����(��������, �������� ��)
	//  - ������ �����ϴ�.
	//  - ��ü�� �Ҹ��� �Ű澲�� �ʾƵ� �ȴ�.
	//  - ���α׷� ���� ���� ������ �Ұ���
	static CEngine* GetInst() 
	{
		// ���������� Data ������ ����
		static CEngine engine;
		return &engine;
	}

private:
	CEngine();
	
public:
	~CEngine();
};

*/

class CEngine
{
private:
	// ���� �ɹ�����
	//  - ��ü �ȿ� ������� �ʴ�.
	//  - ������ ��������
	//  - ����� Ŭ���� ����
	static CEngine*		m_Inst; 

public:
	// �ϳ��� ��ü�� ����, ������ ���� ��ü�� ��ȯ
	// 2. ��ü�� �����Ҵ�
	//  - ������ �����ϴ�
	//  - ��ü�� �Ҹ��� �����ؾ��Ѵ�.
	//  - ��Ÿ�� ���߿� ����, ������ �����ϴ�.
	static CEngine* GetInst()
	{
		// ���������� Data ������ ����
		if (nullptr == m_Inst)
		{
			m_Inst = new CEngine;
		}

		return m_Inst;
	}

	static void Destroy()
	{
		if (nullptr != m_Inst)
		{
			delete m_Inst;
			m_Inst = nullptr;
		}
	}


private:
	CEngine();

public:
	~CEngine();
};
