#include "pch.h"
#include "CPathMgr.h"

wchar_t CPathMgr::g_ContentPath[255]	= {};
wchar_t CPathMgr::g_BinPath[255]		= {};
wchar_t CPathMgr::g_SolutionPath[255]	= {};


void CPathMgr::Init()
{
	wchar_t szBuff[255] = {};

	// ���� ���μ����� ���(����� ���� ������ ��� ����ó�� �ʿ�, ������Ʈ ����->Debug->�۾����͸� ����
	GetCurrentDirectory(255, szBuff);

	for (int i = wcslen(szBuff); 0 <= i; --i)
	{
		if (L'\\' == szBuff[i])
		{
			szBuff[i] = L'\0';
			break;
		}
	}

	wcscat_s(szBuff, 255, L"\\Content\\");
	wcscpy_s(g_ContentPath, 255, szBuff);
}