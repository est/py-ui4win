
#ifndef PYFRAME_HPP
#define PYFRAME_HPP

#include<boost/python.hpp>
#include "PyFrameUI.hpp"

using namespace boost::python;


class PyControlUI
{
public:
	PyControlUI(ULONG pControlUI) {m_pyControlUI = (CControlUI*)pControlUI;}
	~PyControlUI() {}

	void SetText(LPCSTR caption) { m_pyControlUI->SetText(caption); }
	std::string GetText() { return std::string(m_pyControlUI->GetText().GetData()); }
	bool IsVisible() {return m_pyControlUI->IsVisible();}
	void SetVisible(bool bVisible = true){m_pyControlUI->SetVisible(bVisible);}
	bool IsEnabled() {return m_pyControlUI->IsEnabled();}
	void SetEnabled(bool bEnable = true){m_pyControlUI->SetEnabled(bEnable);}
	bool IsFocused() {return m_pyControlUI->IsFocused();}
	void SetFocus(){m_pyControlUI->SetFocus();}

protected:
	CControlUI* m_pyControlUI;   // dui中实现的ui对象
};

class PyTabLayoutUI
{
public:
	PyTabLayoutUI(ULONG pControlUI) {m_pyControlUI = (CTabLayoutUI*)pControlUI;}
	~PyTabLayoutUI() {}

	void SetText(LPCSTR caption) { m_pyControlUI->SetText(caption); }
	std::string GetText() { return std::string(m_pyControlUI->GetText().GetData()); }
	bool IsVisible() {return m_pyControlUI->IsVisible();}
	void SetVisible(bool bVisible = true){m_pyControlUI->SetVisible(bVisible);}
	bool IsEnabled() {return m_pyControlUI->IsEnabled();}
	void SetEnabled(bool bEnable = true){m_pyControlUI->SetEnabled(bEnable);}
	bool IsFocused() {return m_pyControlUI->IsFocused();}
	void SetFocus(){m_pyControlUI->SetFocus();}

	bool SelectItem(int iIndex) { return m_pyControlUI->SelectItem(iIndex); }

protected:
	CTabLayoutUI* m_pyControlUI;   // dui中实现的ui对象
};

class PyAnimationUI
{
public:
	PyAnimationUI(ULONG pControlUI) {m_pyAnimationlUI = (CAnimationUI*)pControlUI;}
	~PyAnimationUI() {}

	bool IsVisible() {return m_pyAnimationlUI->IsVisible();}
	void SetVisible(bool bVisible = true){m_pyAnimationlUI->SetVisible(bVisible);}
	bool IsEnabled() {return m_pyAnimationlUI->IsEnabled();}
	void SetEnabled(bool bEnable = true){m_pyAnimationlUI->SetEnabled(bEnable);}
	void StartAnimation(){m_pyAnimationlUI->StartAnimation();}
	void StopAnimation(){m_pyAnimationlUI->StopAnimation();}

protected:
	CAnimationUI* m_pyAnimationlUI;   // dui中实现的ui对象
};

// An abstract base class
class PyUIBase : public boost::noncopyable
{
public:
	virtual ~PyUIBase() {};
	virtual LPCSTR GetSkinFile(){return NULL;};
	virtual LPCSTR GetWindowClassName(){return NULL;};	

	virtual void OnFinalMessage(ULONG hWnd){};
	virtual void InitWindow(){};;
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam){return 0;};
	virtual LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam){return 0;};
	virtual void OnNotify(LPCSTR sendor, LPCSTR sType, WPARAM wParam, LPARAM lParam){};
	virtual void OnPrepare(LPCSTR sendor, WPARAM wParam, LPARAM lParam){};
	virtual void OnExit(LPCSTR sendor, WPARAM wParam, LPARAM lParam){};
	virtual void OnTimer(LPCSTR sendor, WPARAM wParam, LPARAM lParam){};

	virtual void Show() {m_pyFrameUI->ShowWindow();};
	virtual UINT ShowModal() {return m_pyFrameUI->ShowModal();};

	virtual void SetHWnd(ULONG hWnd) { m_hWnd = hWnd;};
	virtual ULONG GetHWnd() { return m_hWnd;};
	virtual void CloseWindow() { ::PostMessage((HWND)m_hWnd, WM_CLOSE, 0L, 0L); }
	virtual void HideWindow() { ::ShowWindow((HWND)m_hWnd, SW_HIDE); }
	virtual void ExitApp() { PostQuitMessage(0); }
	ULONG DelphiProcessMessage() { return m_pyFrameUI->DelphiProcessMessage();}

	ULONG FindControl(LPCSTR ControlName)
	{
		CControlUI* pControl = m_pyFrameUI->FindControl(ControlName);
		return (ULONG)pControl;
	}
	// 为方便使用加入
	virtual void SetText(LPCSTR ControlName, LPCSTR caption)
	{
		CControlUI* pControl = m_pyFrameUI->FindControl(ControlName);
		pControl->SetText(caption);
	}
	// 接口增加方法:
	// 增加方法后需要在PyUIBaseWrap增加2个接口封装, 还要再app的模块定义里头加入对应的函数定义

	virtual void SetPyFrameUI(PyFrameUI *PyFrameUI) { m_pyFrameUI = PyFrameUI;};

protected:
	ULONG	m_hWnd;
	PyFrameUI* m_pyFrameUI;   // dui中实现的ui对象
};

// Familiar Boost.Python wrapper class for Base
struct PyUIBaseWrap : PyUIBase, wrapper<PyUIBase>
{
	virtual ULONG FindControl(LPCSTR ControlName) { return this->PyUIBase::FindControl(ControlName); }
	virtual ULONG DelphiProcessMessage() { return this->PyUIBase::DelphiProcessMessage(); }
	virtual UINT ShowModal() { return this->PyUIBase::ShowModal(); }
	UINT default_ShowModal() { return this->PyUIBase::ShowModal(); }
	virtual void Show() { this->PyUIBase::Show(); }
	void default_Show() { this->PyUIBase::Show(); }
	virtual void ExitApp()
	{
		if (override oSetHWnd = this->get_override("ExitApp"))
			oSetHWnd(); 
		else
			this->PyUIBase::ExitApp();
	}
	void default_ExitApp() { this->PyUIBase::ExitApp(); }
	virtual void HideWindow()
	{
		if (override oSetHWnd = this->get_override("HideWindow"))
			oSetHWnd(); 
		else
			this->PyUIBase::HideWindow();
	}
	void default_HideWindow() { this->PyUIBase::HideWindow(); }
	virtual void CloseWindow()
	{
		if (override oSetHWnd = this->get_override("CloseWindow"))
			oSetHWnd(); 
		else
			this->PyUIBase::CloseWindow();
	}
	void default_CloseWindow() { this->PyUIBase::CloseWindow(); }

	virtual void SetText(LPCSTR ControlName, LPCSTR caption)
	{
		if (override oSetHWnd = this->get_override("SetText"))
			oSetHWnd(ControlName, caption); 
		else
			this->PyUIBase::SetText(ControlName, caption);
	}
	virtual void default_SetText(LPCSTR ControlName, LPCSTR caption) { this->PyUIBase::SetText(ControlName, caption); }
	virtual void SetHWnd(ULONG hWnd)
	{
		if (override oSetHWnd = this->get_override("SetHWnd"))
			oSetHWnd(hWnd); 
		else
			this->PyUIBase::SetHWnd(hWnd);
	}
	void default_SetHWnd(ULONG hWnd) { this->PyUIBase::SetHWnd(hWnd); }
	virtual ULONG GetHWnd()
	{
		if (override oGetHWnd = this->get_override("GetHWnd"))
			return oGetHWnd(); 
		else
			return this->PyUIBase::GetHWnd();
	}
	ULONG default_GetHWnd() { return this->PyUIBase::GetHWnd(); }

	virtual LPCSTR GetSkinFile() { return this->get_override("GetSkinFile")(); }
	LPCSTR default_GetSkinFile() { return this->get_override("GetSkinFile")(); }
	virtual LPCSTR GetWindowClassName() { return this->get_override("GetWindowClassName")(); }
	LPCSTR default_GetWindowClassName() { return this->get_override("GetWindowClassName")(); }
	virtual void OnFinalMessage(ULONG hWnd) { this->get_override("OnFinalMessage")(hWnd); }
	void default_OnFinalMessage(ULONG hWnd) { this->get_override("OnFinalMessage")(hWnd); }
	virtual void InitWindow() { this->get_override("InitWindow")(); }
	void default_InitWindow() { this->get_override("InitWindow")(); }
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) { return this->get_override("HandleMessage")(uMsg, wParam, lParam); }
	LRESULT default_HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) { return this->PyUIBase::HandleMessage(uMsg, wParam, lParam); }
	virtual LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) { return this->get_override("HandleCustomMessage")(uMsg, wParam, lParam); }
	LRESULT default_HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) { return this->PyUIBase::HandleCustomMessage(uMsg, wParam, lParam); }
	virtual void OnNotify(LPCSTR sendor, LPCSTR sType, WPARAM wParam, LPARAM lParam) { this->get_override("OnNotify")(sendor, sType, wParam, lParam); }
	void default_OnNotify(LPCSTR sendor, LPCSTR sType, WPARAM wParam, LPARAM lParam) { this->PyUIBase::OnNotify(sendor, sType, wParam, lParam); }
	virtual void OnPrepare(LPCSTR sendor, WPARAM wParam, LPARAM lParam) { this->get_override("OnPrepare")(sendor, wParam, lParam); }
	void default_OnPrepare(LPCSTR sendor, WPARAM wParam, LPARAM lParam) { this->PyUIBase::OnPrepare(sendor, wParam, lParam); }
	virtual void OnExit(LPCSTR sendor, WPARAM wParam, LPARAM lParam) { this->get_override("OnExit")(sendor, wParam, lParam); }
	void default_OnExit(LPCSTR sendor, WPARAM wParam, LPARAM lParam) { this->PyUIBase::OnExit(sendor, wParam, lParam); }
	virtual void OnTimer(LPCSTR sendor, WPARAM wParam, LPARAM lParam) { this->get_override("OnTimer")(sendor, wParam, lParam); }
	void default_OnTimer(LPCSTR sendor, WPARAM wParam, LPARAM lParam) { this->PyUIBase::OnTimer(sendor, wParam, lParam); }
};

// 该类是python和ui的桥梁, python用createform接口通过PyFrameUI创建窗口，
// 而界面通过PyUIBase来调用python的业务逻辑
class PyFrameCreator
{
public:

	PyFrameCreator();
	~PyFrameCreator();

public:
	object CreateForm(ULONG hParent, LPCSTR pyModule, LPCSTR pyClassName);
	void Show();
	UINT ShowModal();

protected:
	CDuiString m_xmlSkinFile;
	CDuiString m_pyModule; 
	CDuiString m_pyClassName;
	PyFrameUI* m_pyFrameUI;   // dui中实现的ui对象
	object m_Module;
	object m_ClassUI; 
	object m_InstanceUI;

	PyUIBase* m_pyBaseUI;  // 在python里实现的的业务对象
};

#endif // PYFRAME_HPP