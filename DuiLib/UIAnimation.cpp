#include "StdAfx.h"
#include "UIAnimation.h"

namespace DuiLib
{
	CAnimationUI::CAnimationUI(void) : m_dwFrameInterval(0)
	{
	}

	CAnimationUI::~CAnimationUI(void)
	{
	}


	LPCTSTR CAnimationUI::GetClass() const
	{
		return _T("AnimationUI");
	}

	LPVOID CAnimationUI::GetInterface(LPCTSTR pstrName)
	{
		if( _tcscmp(pstrName, _T("Animation")) == 0 ) return static_cast<CAnimationUI*>(this);
		return CControlUI::GetInterface(pstrName);
	}

	void CAnimationUI::SetFrameInterval(DWORD interval)
	{
		m_dwFrameInterval = interval;
	}

	void CAnimationUI::SetFrameSize(CSize frameSize)
	{
		m_sizeFrame = frameSize;
	}

	void CAnimationUI::StartAnimation()
	{

	}

	void CAnimationUI::StopAnimation()
	{

	}

	void CAnimationUI::SetAnimationImg(LPCTSTR pStrImage)
	{
		if( m_sAnimationImage == pStrImage ) return;

		m_sAnimationImage = pStrImage;
	}

	void CAnimationUI::SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue)
	{
		if( _tcscmp(pstrName, _T("frameinterval")) == 0 ) {
			LPTSTR pstr = NULL;
			DWORD interval = _tcstoul(pstrValue, &pstr, 10);
			SetFrameInterval(interval);
		}    
		else if( _tcscmp(pstrName, _T("framesize")) == 0 ) {
			LPTSTR pstr = NULL;
			CSize frame;
			frame.cx = _tcstol(pstrValue, &pstr, 10);  ASSERT(pstr);    
			frame.cy = _tcstol(pstr + 1, &pstr, 10);    ASSERT(pstr);    
			SetFrameSize(frame);
		}
		else if( _tcscmp(pstrName, _T("animationimg")) == 0 ) {
			SetAnimationImg(pstrValue);
		} 
		else CControlUI::SetAttribute(pstrName, pstrValue);
	}
}