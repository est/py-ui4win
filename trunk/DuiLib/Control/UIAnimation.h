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
		void DoInit();

		virtual void DoEvent(TEventUI& event);
		virtual void PaintBkImage(HDC hDC);

	private:
		DWORD m_dwFrameInterval;
		CSize m_sizeFrame; // 获取每帧大小
		CDuiString m_sAnimationImage;
		DWORD m_dwTimerID;
		int m_nFrameIndex;
		int m_nFrameCount; // 帧总数
	};

}	// namespace DuiLib