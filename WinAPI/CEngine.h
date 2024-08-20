#pragma once

// 프로그램의 최상위 관리자

// 싱글턴
//  - 객체 생성 개수를 1개로 제한

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

	// CEngine 객체를 만들어서 반환하는 함수를 제공
	// 맴버함수 안에서는 private 에 접근이 가능
	// 맴버함수를 호출하려면 객체가 필요. 따라서, 정적 맴버함수로 만든다.

	// 정적 맴버함수
	//  - 객체 없이 호출 가능한 맴버함수 --> this 가 없다
	//  - private 에 접근 가능

	// 하나의 객체만 생성, 생성된 유일 객체를 반환
	// 1. 객체를 Data 영역에 생성(전역변수, 정적변수 등)
	//  - 구현이 간단하다.
	//  - 객체의 소멸을 신경쓰지 않아도 된다.
	//  - 프로그램 실행 도중 해제가 불가능
	static CEngine* GetInst() 
	{
		// 정적변수는 Data 영역에 저장
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
	// 정적 맴버변수
	//  - 객체 안에 들어있지 않다.
	//  - 유일한 전역변수
	//  - 선언된 클래스 전용
	static CEngine*		m_Inst; 

public:
	// 하나의 객체만 생성, 생성된 유일 객체를 반환
	// 2. 객체를 동적할당
	//  - 구현이 복잡하다
	//  - 객체의 소멸을 관리해야한다.
	//  - 런타임 도중에 생성, 삭제가 유연하다.
	static CEngine* GetInst()
	{
		// 정적변수는 Data 영역에 저장
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
