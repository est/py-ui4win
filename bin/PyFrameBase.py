__author__ = 'hqh'
# coding=gbk

import string, time
from PyUI import *
import win32api

class PyFrameBase(PyUIBase):
    def __init__(self):
        super(PyFrameBase, self).__init__()
        #PyUIBase.__init__(self)

    def PyFindControl(self, controlName):
        return PyControlUI(self.FindControl(controlName))

    def PyFindTabLayout(self, controlName):
        return PyTabLayoutUI(self.FindControl(controlName))

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