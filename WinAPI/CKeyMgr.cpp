#include "pch.h"
#include "CKeyMgr.h"



UINT KeyValue[KEY::KEY_END] =
{
	'Q', 'W', 'E', 'R', 'T', 'Y',
	'A', 'S', 'D', 'F', 'G', 'H',
	'Z', 'X', 'C',  'V',  'B',  'N', 'M',

	VK_RETURN,
	VK_ESCAPE,
	VK_LSHIFT,
	VK_MENU,
	VK_CONTROL,
	VK_SPACE,

	VK_UP, VK_DOWN, VK_LEFT, VK_RIGHT,
};




CKeyMgr::CKeyMgr()
{

}

CKeyMgr::~CKeyMgr()
{

}

void CKeyMgr::Init()
{
	for (size_t i = 0; i < KEY_END; ++i)
	{
		m_vecKeyInfo.push_back(KeyInfo{ KEY_STATE::NONE, false});
	}	
}

void CKeyMgr::Tick()
{
	for (size_t i = 0; i < m_vecKeyInfo.size(); ++i)
	{
		// ���� �ش� Ű�� �����ִ�.
		if (GetAsyncKeyState(KeyValue[i]) & 0x8001)
		{
			// �������� �����־���.
			if (m_vecKeyInfo[i].bPrevPressed)
			{
				m_vecKeyInfo[i].State = KEY_STATE::PRESSED;
			}

			// ������ �������� �ʾҴ�.
			else
			{
				m_vecKeyInfo[i].State = KEY_STATE::TAP;
			}

			m_vecKeyInfo[i].bPrevPressed = true;
		}		

		// ���� �ش�Ű�� �ȴ����ִ�.
		else
		{
			// �������� �����־���.
			if (m_vecKeyInfo[i].bPrevPressed)
			{
				m_vecKeyInfo[i].State = KEY_STATE::RELEASED;
			}

			else
			{
				m_vecKeyInfo[i].State = KEY_STATE::NONE;
			}

			m_vecKeyInfo[i].bPrevPressed = false;
		}
	}
}