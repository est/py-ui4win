__author__ = 'huqinghua'
# coding=gbk

import string, os, commands, time
import threading
import shutil
import random
from distutils import dir_util
from shutil import make_archive
from ftplib import FTP

RED_BALL_LENGTH = 33
BLUE_BALL_LENGTH = 16
RESULT_LENGTH = 7

if __name__ == "__main__":
    shutil.copyfile(r"E:\360DesktopUIKernel\Src\Lib\Debug\UiAssistLib.lib" ,r"E:\360mobile_svn\360mobilemgr\branches\360MobileMgr_2.0.0.2160_2013.06.28_A_For_SHUAJIA_TEAM\lib\share\UiAssistLib.lib")
#    chdir(r"C:\Program Files\Microsoft SDKs\Windows\v7.0\Bin")
#    os.system(r'makecert -sv dsoframer.pvk -n "CN=Beijing Goyoo" -ss My -r -b 01/01/1900 -e 01/01/9999')
