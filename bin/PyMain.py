__author__ = 'huqinghua'
# coding=gbk

import string, os, commands, time
import threading
from distutils import dir_util
from shutil import make_archive
import win32api

from PyUI import *
from MsgBox import *
from PyFrameBase import *
import UICommon

def execute_dos_cmd(cmd):
    output = os.popen(cmd)
    for line in output:
        PyLog().LogText(line)

def PyThreadEncrypt(PyClassInstance, solution_path):
    try:
        PyClassInstance.EncryptAndPack(solution_path)
    except Exception, e:
        PyLog().LogText(str(e))

    PyLog().LogText('PyThreadEncrypt exit')

class MainFrame(PyFrameBase):
    def __init__(self):
        super(MainFrame, self).__init__()
        #PyFrameBase.__init__(self)
        self.msg = 'msg origer'

    #virtual LPCSTR GetSkinFile();
    def GetSkinFile(self):
        return 'main.xml'

    #virtual LPCSTR GetWindowClassName() const;
    def GetWindowClassName(self):
        return 'MainFrame'

    #virtual void OnPrepare(LPCSTR sendor, WPARAM wParam, LPARAM lParam);
    def OnPrepare(self, sendor, wParam, lParam):
        self.funcTabLayout = self.PyFindTabLayout("FunctionTabs")
        self.edtRomPath = self.PyFindControl("edtRomPath")
        self.txtDiagnose = self.PyFindControl("txtDiagnose")
        self.txtInstallLog = self.PyFindControl("txtInstallLog")
        self.LblStatus = self.PyFindControl("LblStatus")
        self.btnPyTest = self.PyFindControl("btnPyTest")
        self.LblStatus.SetText('辅助工具')
        #self.btnPyTest.SetVisible(False)
        self.btnPyTest.SetText('手机信息')
        PyWinUtils().SetTimer(self.GetHWnd(), 1, 10)

    #virtual LPCSTR GetWindowClassName() const;
    def TestObj(self, msg):
        self.msg = msg

    #virtual void OnNotify(LPCSTR sendor, LPCSTR sType, WPARAM wParam, LPARAM lParam);
    def OnNotify(self, sendor, sType, wParam, lParam):
        if sType == "click":
            if sendor == "BtnClose":
                #execute_dos_cmd('adb kill-server')
                self.ExitApp()

#            elif sendor == "btnPyTest":
#                self.funcTabLayout.SelectItem(0)
#                #UICommon.ShowMessageBox(self.GetHWnd(), '对话框标题', '你点击了对话框按钮')
#                infPath = PyWinUtils().SelectFile(self.GetHWnd(), "py(*.py)\0*.py\0")
#                if len(infPath) > 0:
#                    dirs = infPath.split('\\')
#                    dirname = dirs[-1]
#                    module = dirname.split('.')
#                    PyScript().RunPy(module[0], 'test')

            elif sendor == "btnPyTest":
                self.funcTabLayout.SelectItem(0)

            elif sendor == "btnEncrypt":
                self.funcTabLayout.SelectItem(3)

                solPath = PyWinUtils().SelectFolder(self.GetHWnd(), "请选择解决方案包:", "solutionpath")
                if len(solPath):
#                    PyWinUtils().SetWaitCursor()
#                    self.EncryptAndPack(solPath)
#                    PyWinUtils().SetArrowCursor()
                    t = threading.Thread(target=PyThreadEncrypt,args=(self,solPath))
                    t.start()
                    #t.join(1)

            elif sendor == "btnDriverDiagnose":
                self.funcTabLayout.SelectItem(3)
                self.diagnose()

            elif sendor == 'btnOpenLog':
                if os.path.isfile(PyWinUtils().GetExeDirectory() + '\\applog.ini'):
                    PyWinUtils().ShellExcute(0, 'open', PyWinUtils().GetExeDirectory() + '\\applog.ini', '', '', 1)
                else:
                    UICommon.ShowMessageBox(self.GetHWnd(), '错误', '日志文件不存在')
                #win32api.ShellExecute(0, 'open', 'e:\\applog.ini', None, "", 1)

            elif sendor == 'btnClearLog':
                self.txtDiagnose.SetText('')
                if os.path.isfile(PyWinUtils().GetExeDirectory() + '\\applog.ini'):
                    os.remove(PyWinUtils().GetExeDirectory() + '\\applog.ini')
                #win32api.ShellExecute(0, 'open', 'e:\\applog.ini', None, "", 1)

            elif sendor == 'btnDriverInstall':
                self.funcTabLayout.SelectItem(1)
                self.txtInstallLog.SetText('')

            elif sendor == 'btnChooseInf':
                infPath = PyWinUtils().SelectFile(self.GetHWnd(), "inf(*.inf)\0*.inf\0")
                if len(infPath) > 0:
                    self.edtRomPath.SetText(infPath)

            elif sendor == 'btnInstallDriver':
                msg = self.edtRomPath.GetText()
                if len(msg) > 0:
                    PyWinUtils().SetWaitCursor()
                    DriverInstaller().InstallDriverFromInf(msg)
                    PyWinUtils().SetArrowCursor()
                    self.txtInstallLog.SetText('安装完成. 请重新检测驱动状态.')
                else:
                    mbox1 = PyFrameCreator()
                    UICommon.ShowMessageBox(self.GetHWnd(), '错误', '没有选择inf文件')

    def AppendAndLog(self, line):
        PyLog().LogText( line)
        msg = self.txtDiagnose.GetText()
        self.txtDiagnose.SetText(msg + '\n' + line)

    def ShowAndLog(self, line):
        PyLog().LogText( line)
        self.txtDiagnose.SetText(line)

    def diagnose(self):
        PyWinUtils().SetCurrentDirectoryToExePath()
        os.system('adb devices')
        #pid = subprocess.Popen(["adb", "devices"]).pid
        #subprocess.Popen("adb devices")
        #self.ShowAndLog( "\n")
        ISOTIMEFORMAT='%Y-%m-%d %X'
        self.ShowAndLog(time.strftime( ISOTIMEFORMAT, time.localtime() ))
        self.AppendAndLog( "----------------------------------------------驱动检测----------------------------------------------")
        self.AppendAndLog(DriverStatus().DriverDiagnose())
        self.AppendAndLog( "----------------------------------------------手机模式检测----------------------------------------------")
        self.AppendAndLog( 'adb devices 输出:')
        output = os.popen('adb devices')
        for line in output:
            self.AppendAndLog( line)

        self.AppendAndLog( 'fastboot devices 输出:')
        output = os.popen('fastboot devices')
        for line in output:
            self.AppendAndLog( line)

        self.AppendAndLog( "----------------------------------------------手机设备检测----------------------------------------------")
        output = os.popen(r'devcon find usb\*')
        for line in output:
            if line.find('VID_04E8') != -1:
                line = line.replace('\n', '')
                self.AppendAndLog(line)
                self.AppendAndLog('三星')
            elif line.find('VID_19D2') != -1:
                line = line.replace('\n', '')
                self.AppendAndLog( line)
                self.AppendAndLog( '中兴')
            elif line.find('VID_19D2') != -1:
                line = line.replace('\n', '')
                self.AppendAndLog( line)
                self.AppendAndLog( '中兴')
            elif line.find('VID_12D1') != -1:
                line = line.replace('\n', '')
                self.AppendAndLog( line)
                self.AppendAndLog( '华为')
            else:
                line = line.replace('\n', '')
                self.AppendAndLog( line)

            if line.find('ADB') != -1:
                self.AppendAndLog( "***********************")

        return True

    def generateConfig(self, solutionPath):
        flag = ''
        commonFile=file(solutionPath + '\\common.lua','r')
        shuajiFile=file(solutionPath + '\\shuaji.lua','r+')

        temp=file(solutionPath + '\\tmp.lua','w+')
        for line in commonFile:
            temp.write(line)
        temp.write('\n')
        for line in shuajiFile:
            temp.write(line)
        temp.write('\n')
        temp.flush()
        temp.close()

        shuajiFile.close()
        os.remove(solutionPath + '\\shuaji.lua')
        if os.path.isfile(solutionPath + '\\config.lua'):
            os.remove(solutionPath + '\\config.lua')
        os.rename(solutionPath + '\\tmp.lua', solutionPath + '\\config.lua')

    def generatebackup(self, solutionPath):
        flag = ''
        commonFile=file(solutionPath + '\\common.lua','r')
        shuajiFile=file(solutionPath + '\\systembackup.lua','r+')

        temp=file(solutionPath + '\\tmp.lua','w+')
        for line in commonFile:
            temp.write(line)
        temp.write('\n')
        for line in shuajiFile:
            temp.write(line)
        temp.write('\n')
        temp.flush()
        temp.close()

        shuajiFile.close()
        os.remove(solutionPath + '\\systembackup.lua')
        os.rename(solutionPath + '\\tmp.lua', solutionPath + '\\systembackup.lua')

    def generaterecovery(self, solutionPath):
        flag = ''
        commonFile=file(solutionPath + '\\common.lua','r')
        shuajiFile=file(solutionPath + '\\systemrestore.lua','r+')

        temp=file(solutionPath + '\\tmp.lua','w+')
        for line in commonFile:
            temp.write(line)
        temp.write('\n')
        for line in shuajiFile:
            temp.write(line)
        temp.write('\n')
        temp.flush()
        temp.close()

        shuajiFile.close()
        os.remove(solutionPath + '\\systemrestore.lua')
        os.rename(solutionPath + '\\tmp.lua', solutionPath + '\\systemrestore.lua')

    def EncryptAndPack(self, solutionPath):
        PyWinUtils().SetCurrentDirectoryToExePath()
        ISOTIMEFORMAT='%Y-%m-%d %X'
        self.ShowAndLog(time.strftime( ISOTIMEFORMAT, time.localtime() ))
        self.AppendAndLog('打包目录 = %s' % solutionPath )

        if not os.path.isfile(solutionPath + '\\shuaji.lua'):
            self.AppendAndLog('%s 不是解决方案目录' % solutionPath )
            return

        dirs = solutionPath.split('\\')
        dirname = dirs[-1]
        self.AppendAndLog( dirname)
        tmpdir = solutionPath + '_tmp'
        PyLog().LogText( '1')
        if os.path.isdir(tmpdir):
            dir_util.remove_tree(tmpdir)
        PyLog().LogText( '2')
        PyWinUtils().CreateDirectory(tmpdir)
        #dir_util.mkpath(tmpdir)
        PyLog().LogText( '3')
#        time.sleep(10)
        PyLog().LogText( '3.5')
#        i = 0
#        while i<100:
#            i = i + 1
#            self.AppendAndLog('%d' % i )
#            time.sleep(1)

        dir_util.copy_tree(solutionPath, tmpdir)

        PyLog().LogText( '4')
        if os.path.isfile(tmpdir + '\\shuaji.lua'):
            self.AppendAndLog('合成刷机方案')
            self.generateConfig(tmpdir)
        if os.path.isfile(tmpdir + '\\systembackup.lua'):
            self.AppendAndLog('合成备份方案')
            self.generatebackup(tmpdir)
        if os.path.isfile(tmpdir + '\\systemrestore.lua'):
            self.AppendAndLog('合成恢复方案')
            self.generaterecovery(tmpdir)

        PyLog().LogText( '5')
        os.remove(tmpdir + '\\common.lua')

        self.AppendAndLog('打包')
        if os.path.isfile(tmpdir + '.zip'):
            os.remove(tmpdir + '.zip')
        os.chdir(tmpdir)
        make_archive(tmpdir, 'zip', '.', '.')

        if os.path.isfile(solutionPath + '.zip'):
            os.remove(solutionPath + '.zip')
        os.rename(tmpdir + '.zip', solutionPath + '.zip')
        os.chdir(solutionPath)
        dir_util.remove_tree(tmpdir)

        self.AppendAndLog('成功')

def PyAppInit():
    pyFrameObj = PyFrameCreator()
    obj = pyFrameObj.CreateForm(0, 'PyMain', 'MainFrame')
    obj.TestObj('msg changed')
    pyFrameObj.ShowModal()


