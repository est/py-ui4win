#include "stdafx.h"


#ifdef _DEBUG
#undef _DEBUG
#include <Python.h>
#define _DEBUG
#else
#include <Python.h>
#endif

#include<boost/python.hpp>
#include "PyFrameCreator.hpp"
#include "Win32Api.h"
#include "PyModuleImport.h"
#include "PyException.h"

#include "DriverStatus.h"
#include "DriverInstaller.h"

#include "DecEnc.h"

using namespace std;
using namespace boost::python;

typedef boost::shared_ptr < PyFrameCreator > PyFrame_ptr;  
typedef boost::shared_ptr < PyControlUI > PyControlUI_ptr;  
typedef boost::shared_ptr < PyCheckBoxUI > PyCheckBoxUI_ptr;  
typedef boost::shared_ptr < PyProgressUI > PyProgressUI_ptr;  
typedef boost::shared_ptr < PyTabLayoutUI > PyTabLayoutUI_ptr;  
BOOST_PYTHON_MODULE(PyUI)
{
	class_<PyControlUI>("PyControlUI", init<ULONG>())
		.def("SetText", &PyControlUI::SetText)
		.def("GetText", &PyControlUI::GetText)
		.def("IsVisible", &PyControlUI::IsVisible)
		.def("SetVisible", &PyControlUI::SetVisible)
		.def("IsEnabled", &PyControlUI::IsEnabled)
		.def("SetEnabled", &PyControlUI::SetEnabled)
		.def("IsFocused", &PyControlUI::IsFocused)
		.def("SetFocus", &PyControlUI::SetFocus)
		; 

	class_<PyCheckBoxUI>("PyCheckBoxUI", init<ULONG>())
		.def("SetCheck", &PyCheckBoxUI::SetCheck)
		.def("GetCheck", &PyCheckBoxUI::GetCheck)
		.def("IsVisible", &PyCheckBoxUI::IsVisible)
		.def("SetVisible", &PyCheckBoxUI::SetVisible)
		.def("IsEnabled", &PyCheckBoxUI::IsEnabled)
		.def("SetEnabled", &PyCheckBoxUI::SetEnabled)
		; 

	class_<PyProgressUI>("PyProgressUI", init<ULONG>())
		.def("SetValue", &PyProgressUI::SetValue)
		.def("GetValue", &PyProgressUI::GetValue)
		.def("IsVisible", &PyProgressUI::IsVisible)
		.def("SetVisible", &PyProgressUI::SetVisible)
		.def("IsEnabled", &PyProgressUI::IsEnabled)
		.def("SetEnabled", &PyProgressUI::SetEnabled)
		; 

	class_<PyAnimationUI>("PyAnimationUI", init<ULONG>())
		.def("IsVisible", &PyAnimationUI::IsVisible)
		.def("SetVisible", &PyAnimationUI::SetVisible)
		.def("IsEnabled", &PyAnimationUI::IsEnabled)
		.def("SetEnabled", &PyAnimationUI::SetEnabled)
		.def("StopAnimation", &PyAnimationUI::StopAnimation)
		.def("StartAnimation", &PyAnimationUI::StartAnimation)
		; 

	class_<PyTabLayoutUI>("PyTabLayoutUI", init<ULONG>())
		.def("SetText", &PyTabLayoutUI::SetText)
		.def("GetText", &PyTabLayoutUI::GetText)
		.def("IsVisible", &PyTabLayoutUI::IsVisible)
		.def("SetVisible", &PyTabLayoutUI::SetVisible)
		.def("IsEnabled", &PyTabLayoutUI::IsEnabled)
		.def("SetEnabled", &PyTabLayoutUI::SetEnabled)
		.def("IsFocused", &PyTabLayoutUI::IsFocused)
		.def("SetFocus", &PyTabLayoutUI::SetFocus)
		.def("SelectItem", &PyTabLayoutUI::SelectItem)
		; 

	//class_<PyUIBase, boost::noncopyable>("PyFrame")
	//	.def("SetHWnd", &PyUIBase::SetHWnd)
	//	.def("GetHWnd", &PyUIBase::GetHWnd)
	//	.def("SetCaption", &PyUIBase::SetCaption)
	//	.def("CloseWindow", &PyUIBase::CloseWindow)
	//	.def("HideWindow", &PyUIBase::HideWindow)
	//	.def("ExitApp", &PyUIBase::ExitApp)	

	//	//.def("Show", &PyUIBase::Show)
	//	//.def("ShowModal", &PyUIBase::ShowModal)

	//	.def("GetSkinFile", &PyUIBase::GetSkinFile)
	//	.def("GetWindowClassName", &PyUIBase::GetWindowClassName)
	//	.def("OnFinalMessage", &PyUIBase::OnFinalMessage)
	//	.def("InitWindow", &PyUIBase::InitWindow)
	//	.def("HandleMessage", &PyUIBase::HandleMessage)
	//	.def("HandleCustomMessage", &PyUIBase::HandleCustomMessage)
	//	.def("OnNotify", &PyUIBase::OnNotify)
	//	.def("OnPrepare", &PyUIBase::OnPrepare)
	//	.def("OnExit", &PyUIBase::OnExit)
	//	.def("OnTimer", &PyUIBase::OnTimer)
	//	;

	class_<PyUIBaseWrap, boost::noncopyable>("PyUIBase")
		// 方便使用的通用函数
		.def("SetHWnd", &PyUIBaseWrap::SetHWnd)
		.def("GetHWnd", &PyUIBaseWrap::GetHWnd)
		.def("CloseWindow", &PyUIBaseWrap::CloseWindow)
		.def("HideWindow", &PyUIBaseWrap::HideWindow)
		//.def("SetHWnd", &PyUIBaseWrap::SetHWnd, &PyUIBaseWrap::default_SetHWnd)
		//.def("GetHWnd", &PyUIBaseWrap::GetHWnd, &PyUIBaseWrap::default_GetHWnd)
		//.def("SetCaption", &PyUIBaseWrap::SetCaption, &PyUIBaseWrap::default_SetCaption)
		//.def("CloseWindow", &PyUIBaseWrap::CloseWindow, &PyUIBaseWrap::default_CloseWindow)
		//.def("HideWindow", &PyUIBaseWrap::HideWindow, &PyUIBaseWrap::default_HideWindow)
		.def("ExitApp", &PyUIBaseWrap::ExitApp, &PyUIBaseWrap::default_ExitApp)	
		.def("ProcessMessages", &PyUIBaseWrap::ProcessMessages)
		//.def("Show", &PyUIBaseWrap::Show, &PyUIBaseWrap::default_Show)
		//.def("ShowModal", &PyUIBaseWrap::ShowModal, &PyUIBaseWrap::default_ShowModal)

		// 界面皮肤
		.def("GetSkinFile", &PyUIBaseWrap::GetSkinFile, &PyUIBaseWrap::default_GetSkinFile)
		// 界面显示
		.def("SetText", &PyUIBaseWrap::SetText)
		.def("FindControl", &PyUIBaseWrap::FindControl)
		// 业务类
		.def("GetWindowClassName", &PyUIBaseWrap::GetWindowClassName, &PyUIBaseWrap::default_GetWindowClassName)
		// 消息处理
		.def("OnFinalMessage", &PyUIBaseWrap::OnFinalMessage, &PyUIBaseWrap::default_OnFinalMessage)
		.def("InitWindow", &PyUIBaseWrap::InitWindow, &PyUIBaseWrap::default_InitWindow)
		.def("HandleMessage", &PyUIBaseWrap::HandleMessage, &PyUIBaseWrap::default_HandleMessage)
		.def("HandleCustomMessage", &PyUIBaseWrap::HandleCustomMessage, &PyUIBaseWrap::default_HandleCustomMessage)
		.def("OnNotify", &PyUIBaseWrap::OnNotify, &PyUIBaseWrap::default_OnNotify)
		.def("OnPrepare", &PyUIBaseWrap::OnPrepare, &PyUIBaseWrap::default_OnPrepare)
		.def("OnExit", &PyUIBaseWrap::OnExit, &PyUIBaseWrap::default_OnExit)
		.def("OnTimer", &PyUIBaseWrap::OnTimer, &PyUIBaseWrap::default_OnTimer)
		;

	class_<PyLog>("PyLog")
		.def("LogText", &PyLog::LogText)
		;

	class_<PyScript>("PyScript")
		.def("RunPy", &PyScript::RunPy)
		;

	class_<CWin32Api>("PyWinUtils")
		.def("GetExeDirectory", &CWin32Api::GetExeDirectory)
		.def("SetCurrentDirectory", &CWin32Api::SetCurrentDirectory)
		.def("SetCurrentDirectoryToExePath", &CWin32Api::SetCurrentDirectoryToExePath)
		.def("SetWaitCursor", &CWin32Api::SetWaitCursor)
		.def("SetArrowCursor", &CWin32Api::SetArrowCursor)
		.def("ShellExcute", &CWin32Api::ShellExcute)
		.def("SelectFile", &CWin32Api::SelectFile)
		.def("MessageBox", &CWin32Api::MessageBox)
		.def("SelectFolder", &CWin32Api::SelectFolder)
		.def("CreateDirectory", &CWin32Api::CreateDirectory)
		.def("Sleep", &CWin32Api::Sleep)
		.def("SetTimer", &CWin32Api::SetTimer)
		;

	class_<PyFrameCreator>("PyFrameCreator")
		.def("CreateForm", &PyFrameCreator::CreateForm)
		//.def("Show", &PyFrameCreator::Show)
		.def("ShowModal", &PyFrameCreator::ShowModal)
		; 

	register_ptr_to_python <PyFrame_ptr>();  
	register_ptr_to_python <PyControlUI_ptr>();  
	register_ptr_to_python <PyCheckBoxUI_ptr>();  
	register_ptr_to_python <PyProgressUI_ptr>();  
	register_ptr_to_python <PyTabLayoutUI_ptr>();  
}

BOOST_PYTHON_MODULE(PyDriverBiz)
{
	class_<CDriverStatus>("DriverStatus")
		.def("DriverDiagnose", &CDriverStatus::DriverDiagnose)
		;
	class_<CDriverInstaller>("DriverInstaller")
		.def("InstallDriverFromInf", &CDriverInstaller::InstallDriverFromInf)
		;
}

BOOST_PYTHON_MODULE(PyEncBiz)
{
	class_<CDecEnc>("DecEnc")
		.def("AESDecodeStr", &CDecEnc::AESDecodeStr)
		;
}
void PyExtentInit()
{
	PyImport_AppendInittab("PyUI", initPyUI);
	PyImport_AppendInittab("PyDriverBiz", initPyDriverBiz);
	PyImport_AppendInittab("PyEncBiz", initPyEncBiz);
}

std::string PyScript::RunPy(std::string pyModule, std::string pyFunc)
{
	std::string ret = "";

	boost::python::handle<>* _module = NULL; // Module handle.

	try
	{
		_module = new boost::python::handle<>(
			PyImport_ImportModule( pyModule.c_str()));
		ret = boost::python::call_method<std::string>(_module->get(), pyFunc.c_str());
	}
	catch(boost::python::error_already_set const &){  
		ret = parse_python_exception();
		PyLog().LogText(ret.c_str());
		PyErr_Clear();
	}  
	catch (...)
	{
		if (PyErr_Occurred())
		{
			ret = parse_python_exception();
			PyLog().LogText(ret.c_str());
			PyErr_Clear();
		}
	}

	if (_module)
		delete _module;

	return ret;
}