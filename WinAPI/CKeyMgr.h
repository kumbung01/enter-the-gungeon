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

public:
	KEY_STATE GetKeyState(KEY _key) { return m_vecKeyInfo[_key].State; }

public:
	void Init();
	void Tick();
};

