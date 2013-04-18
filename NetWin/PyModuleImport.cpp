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
#include "PyModuleImport.h"
using namespace std;
using namespace boost::python;

typedef boost::shared_ptr < PyFrameCreator > PyFrame_ptr;  
typedef boost::shared_ptr < PyControlUI > PyControlUI_ptr;  
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

	class_<PyFrameCreator>("PyFrameCreator")
		.def("CreateForm", &PyFrameCreator::CreateForm)
		//.def("Show", &PyFrameCreator::Show)
		.def("ShowModal", &PyFrameCreator::ShowModal)
		; 

	register_ptr_to_python <PyFrame_ptr>();  
	register_ptr_to_python <PyControlUI_ptr>();  
	register_ptr_to_python <PyTabLayoutUI_ptr>();  
}

void PyExtentInit()
{
	PyImport_AppendInittab("PyUI", initPyUI);
}
