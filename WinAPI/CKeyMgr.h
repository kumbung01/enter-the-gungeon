#pragma once

enum KEY_STATE
{
	NONE,
	TAP,
	PRESSED,
	RELEASED,
};

enum KEY
{
	Q,W,E,R,T,Y,
	A,S,D,F,G,H,
	Z,X,C,V,B,N,M,

	ENTER,
	ESC,
	LSHIFT,
	ALT,
	CTRL,
	SPACE,

	UP, DOWN, LEFT, RIGHT,

	NUM0,
	NUM1,
	NUM2,
	NUM3,
	NUM4,
	NUM5,
	NUM6,
	NUM7,
	NUM8,
	NUM9,

	NUMPAD0,
	NUMPAD1,
	NUMPAD2,
	NUMPAD3,
	NUMPAD4,
	NUMPAD5,
	NUMPAD6,
	NUMPAD7,
	NUMPAD8,
	NUMPAD9,

	LBTN,
	RBTN,

	KEY_END,
};

struct KeyInfo
{	
	KEY_STATE	State;			// 현재 상태
	bool		bPrevPressed;	// 이전 프레임에 눌렸는지
};


class CKeyMgr
{
	SINGLE(CKeyMgr);
private:
	vector<KeyInfo>		m_vecKeyInfo;
	Vec2				m_MousePos;
	int					m_mouseScroll;

public:
	KEY_STATE GetKeyState(KEY _key) { return m_vecKeyInfo[_key].State; }
	Vec2 GetMousePos() { return m_MousePos; }	
	
	void SetMouseScroll(int _mouseScroll) { m_mouseScroll = _mouseScroll; }
	int  GetMouseScroll() { 
		int ret = m_mouseScroll;
		m_mouseScroll = 0;
		return ret;
	}

	bool IsMouseOffScreen();

public:
	void Init();
	void Tick();
};

