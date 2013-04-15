__author__ = 'huqinghua'
# coding=gbk

import string, os, commands, time
from PyUI import *
from PyFrameBase import *

class MsgBox(PyFrameBase):
    def __init__(self):
        #PyFrameBase.__init__(self)
        super(MsgBox, self).__init__()

    #virtual LPCSTR GetSkinFile();
    def GetSkinFile(self):
        return 'msgbox.xml'

    #virtual LPCSTR GetWindowClassName() const;
    def GetWindowClassName(self):
        return 'MsgBox'

    #virtual void OnNotify(LPCSTR sendor, LPCSTR sType, WPARAM wParam, LPARAM lParam);
    def OnNotify(self, sendor, sType, wParam, lParam):
        if sType == "click":
            if sendor == "btnOK":
                msg = "%d" % self.GetHWnd()
                PyLog().LogText(msg)
                self.CloseWindow()
            elif sendor == "BtnClose":
                self.CloseWindow()
