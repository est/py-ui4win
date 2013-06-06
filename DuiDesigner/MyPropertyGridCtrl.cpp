#include "StdAfx.h"
#include "MyPropertyGridCtrl.h"

CMyPropertyGridCtrl::CMyPropertyGridCtrl(void)
{
}

CMyPropertyGridCtrl::~CMyPropertyGridCtrl(void)
{
}

BOOL CMyPropertyGridCtrl::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_DELETE)
	{
		return TRUE;
	}

	return CMFCPropertyGridCtrl::PreTranslateMessage(pMsg);
}