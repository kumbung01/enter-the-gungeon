#include "pch.h"
#include "CKeyMgr.h"

#include "CEngine.h"

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

	VK_NUMPAD0,
	VK_NUMPAD1,
	VK_NUMPAD2,
	VK_NUMPAD3,
	VK_NUMPAD4,
	VK_NUMPAD5,
	VK_NUMPAD6,
	VK_NUMPAD7,
	VK_NUMPAD8,
	VK_NUMPAD9,	

	VK_LBUTTON,
	VK_RBUTTON,
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
	// ���� �����찡 ��Ŀ�� ���� ��
	if (GetFocus() == CEngine::GetInst()->GetMainWndHwnd())
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

		// ���콺 ��ǥ ����
		POINT ptPos = {};
		GetCursorPos(&ptPos);
		ScreenToClient(CEngine::GetInst()->GetMainWndHwnd(), &ptPos);

		m_MousePos = ptPos;
	}

	// ���� �����찡 ��Ȱ��ȭ �Ǿ� ���� ��
	else
	{
		for (size_t i = 0; i < m_vecKeyInfo.size(); ++i)
		{
			if (KEY_STATE::TAP == m_vecKeyInfo[i].State
				|| KEY_STATE::PRESSED == m_vecKeyInfo[i].State)
			{
				m_vecKeyInfo[i].State = KEY_STATE::RELEASED;
			}

			else if (KEY_STATE::RELEASED == m_vecKeyInfo[i].State)
			{
				m_vecKeyInfo[i].State = KEY_STATE::NONE;
			}

			m_vecKeyInfo[i].bPrevPressed = false;
		}

		// ���콺 ��ǥ ����
		*((int*)&m_MousePos.x) = 0xffffffff;
		*((int*)&m_MousePos.y) = 0xffffffff;
	}
}

bool CKeyMgr::IsMouseOffScreen()
{
	Vec2 vResolution = CEngine::GetInst()->GetResolution();

	if (vResolution.x <= m_MousePos.x || vResolution.y <= m_MousePos.y
		|| m_MousePos.x < 0 || m_MousePos.y < 0)
	{
		return true;
	}
	else
	{
		return false;
	}	
}