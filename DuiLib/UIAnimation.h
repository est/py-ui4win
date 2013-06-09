#pragma once

namespace DuiLib
{
	class UILIB_API CAnimationUI : public CControlUI
	{
	public:
		CAnimationUI(void);
		~CAnimationUI(void);

		LPCTSTR GetClass() const;
		LPVOID GetInterface(LPCTSTR pstrName);

		void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

		void SetFrameInterval(DWORD interval);
		void SetFrameSize(CSize frameSize);
		void StartAnimation();
		void StopAnimation();
		void SetAnimationImg(LPCTSTR pStrImage);

		void GetAnimationImage();
		CSize GetAnimationFrameWindow(); // 获取每帧大小
		int  GetAnimationFrameCount();    // 帧总数

	private:
		DWORD m_dwFrameInterval;
		CSize m_sizeFrame;
		BOOL  m_bEnable;
		CDuiString m_sAnimationImage;
	};

}	// namespace DuiLib