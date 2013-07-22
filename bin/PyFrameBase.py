__author__ = 'hqh'
# coding=gbk

import string, time
from PyUI import *

DUI_MSGTYPE_MENU = "menu"
DUI_MSGTYPE_LINK = "link"

DUI_MSGTYPE_TIMER = "timer"
DUI_MSGTYPE_CLICK = "click"

DUI_MSGTYPE_RETURN = "return"
DUI_MSGTYPE_SCROLL = "scroll"

DUI_MSGTYPE_DROPDOWN = "dropdown"
DUI_MSGTYPE_SETFOCUS = "setfocus"

DUI_MSGTYPE_KILLFOCUS = "killfocus"
DUI_MSGTYPE_ITEMCLICK = "itemclick"
DUI_MSGTYPE_TABSELECT = "tabselect"

DUI_MSGTYPE_ITEMSELECT = "itemselect"
DUI_MSGTYPE_ITEMEXPAND = "itemexpand"
DUI_MSGTYPE_WINDOWINIT = "windowinit"
DUI_MSGTYPE_BUTTONDOWN = "buttondown"
DUI_MSGTYPE_MOUSEENTER = "mouseenter"
DUI_MSGTYPE_MOUSELEAVE = "mouseleave"

DUI_MSGTYPE_TEXTCHANGED = "textchanged"
DUI_MSGTYPE_HEADERCLICK = "headerclick"
DUI_MSGTYPE_ITEMDBCLICK = "itemdbclick"
DUI_MSGTYPE_SHOWACTIVEX = "showactivex"

DUI_MSGTYPE_ITEMCOLLAPSE = "itemcollapse"
DUI_MSGTYPE_ITEMACTIVATE = "itemactivate"
DUI_MSGTYPE_VALUECHANGED = "valuechanged"

DUI_MSGTYPE_SELECTCHANGED = "selectchanged"

class PyFrameBase(PyUIBase):
    def __init__(self):
        super(PyFrameBase, self).__init__()
        #PyUIBase.__init__(self)
    def PyCreateControl(self):
        return PyControlUI(PyUIFactory().CreateControlUI())
    def PyCreateLabel(self):
        return PyLabelUI(PyUIFactory().CreateLabelUI())
    def PyCreateButton(self):
        return PyButtonUI(PyUIFactory().CreateButtonUI())
    def PyCreateOption(self):
        return PyOptionUI(PyUIFactory().CreateOptionUI())
    def PyCreateCheckBox(self):
        return PyCheckBoxUI(PyUIFactory().CreateCheckBoxUI())
    def PyCreateProgress(self):
        return PyProgressUI(PyUIFactory().CreatProgressUI())
    def PyCreateAnimation(self):
        return PyAnimationUI(PyUIFactory().CreateAnimationUI())
    def PyCreateHorizontalLayout(self):
        return PyHorizontalLayoutUI(PyUIFactory().CreateHorizontalLayoutUI())
    def PyCreateVerticalLayout(self):
        return PyVerticalLayoutUI(PyUIFactory().CreateVerticalLayoutUI())
    def PyCreateTabLayout(self):
        return PyTabLayoutUI(PyUIFactory().CreateTabLayoutUI())
    def PyCreateList(self):
        return PyListUI(PyUIFactory().CreateListUI())
    def PyCreateListContainerElement(self):
        return PyListContainerElementUI(PyUIFactory().CreateListContainerElementUI())

    def PyFindControl(self, controlName):
        return PyControlUI(self.FindControl(controlName))
    def PyFindLabel(self, controlName):
        return PyLabelUI(self.FindControl(controlName))
    def PyFindButton(self, controlName):
        return PyButtonUI(self.FindControl(controlName))
    def PyFindOption(self, controlName):
        return PyOptionUI(self.FindControl(controlName))
    def PyFindCheckBox(self, controlName):
        return PyCheckBoxUI(self.FindControl(controlName))
    def PyFindProgress(self, controlName):
        return PyProgressUI(self.FindControl(controlName))
    def PyFindAnimation(self, controlName):
        return PyAnimationUI(self.FindControl(controlName))
    def PyFindHorizontalLayout(self, controlName):
        return PyHorizontalLayoutUI(self.FindControl(controlName))
    def PyFindVerticalLayout(self, controlName):
        return PyVerticalLayoutUI(self.FindControl(controlName))
    def PyFindTabLayout(self, controlName):
        return PyTabLayoutUI(self.FindControl(controlName))
    def PyFindList(self, controlName):
        return PyListUI(self.FindControl(controlName))
    def PyFindListContainerElement(self, controlName):
        return PyListContainerElementUI(self.FindControl(controlName))

    #virtual void OnFinalMessage(HWND hWnd);
    def OnFinalMessage(self, hWnd):
#        PyLog().LogText( 'OnFinalMessage()')
        pass

    #virtual void InitWindow();
    def InitWindow(self):
#        PyLog().LogText( 'InitWindow()')
        pass

    #virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
    def HandleMessage(self, uMsg, wParam, lParam):
#        PyLog().LogText( 'HandleMessage()')
        return 0

    #virtual LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
    def HandleCustomMessage(self, uMsg, wParam, lParam):
#        PyLog().LogText( 'HandleCustomMessage()')
        if uMsg == 0x0113:
            self.OnCustomTimer(wParam, lParam)
#            pass
#            PyLog().LogText( 'HandleCustomMessage(WM_TIMER)')
        return 0

    #virtual void OnPrepare(LPCSTR sendor, WPARAM wParam, LPARAM lParam);
    def OnPrepare(self, sendor, wParam, lParam):
#        PyLog().LogText( 'OnPrepare()')
        pass

    #virtual void OnExit(LPCSTR sendor, WPARAM wParam, LPARAM lParam);
    def OnExit(self, sendor, wParam, lParam):
#        PyLog().LogText( 'OnExit()')
        pass

    #virtual void OnTimer(LPCSTR sendor, WPARAM wParam, LPARAM lParam);
    def OnTimer(self, sendor, wParam, lParam):
#        PyLog().LogText( 'OnTimer()')
        pass

    def OnCustomTimer(self, wParam, lParam):
        if wParam == 1:
            time.sleep(0)
            #PyLog().LogText( 'OnCustomTimer()')
        pass

def GiveUp():
    #PyLog().LogText( "GiveUp")
    time.sleep(0)
