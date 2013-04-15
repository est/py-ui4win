__author__ = 'hqh'
# coding=gbk

import string, time
from PyUI import *

class PyFrameBase(PyUIBase):
    def __init__(self):
        super(PyFrameBase, self).__init__()
        #PyUIBase.__init__(self)

    def PyFindControl(self, controlName):
        return PyControlUI(self.FindControl(controlName))

    #virtual void OnFinalMessage(HWND hWnd);
    def OnFinalMessage(self, hWnd):
        pass

    #virtual void InitWindow();
    def InitWindow(self):
        pass

    #virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
    def HandleMessage(self, uMsg, wParam, lParam):
        return 0

    #virtual LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
    def HandleCustomMessage(self, uMsg, wParam, lParam):
        return 0

    #virtual void OnPrepare(LPCSTR sendor, WPARAM wParam, LPARAM lParam);
    def OnPrepare(self, sendor, wParam, lParam):
        pass

    #virtual void OnExit(LPCSTR sendor, WPARAM wParam, LPARAM lParam);
    def OnExit(self, sendor, wParam, lParam):
        pass

    #virtual void OnTimer(LPCSTR sendor, WPARAM wParam, LPARAM lParam);
    def OnTimer(self, sendor, wParam, lParam):
        pass
