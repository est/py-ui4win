__author__ = 'huqinghua'
# coding=gbk

import string, os, commands, time
import threading
import shutil
from distutils import dir_util
from shutil import make_archive
from ftplib import FTP
import zipfile
import ctypes

from CommonUtil import CommonUtils
import xml.etree.cElementTree as ET

codeTemplate ="""
__author__ = 'generated by py-ui4win'
# coding=gbk
import string, os, time

from PyUI import *
from MsgBox import *
from PyFrameBase import *
import UICommon
from CommonUtil import CommonUtils

class %s(PyFrameBase):
    def __init__(self):
        super(%s, self).__init__()
        self.clsName = self.__class__.__name__
        self.skinFileName = self.__class__.__name__ + '.xml'

    def GetSkinFile(self):
        return self.skinFileName

    def GetWindowClassName(self):
        return self.clsName

    def OnPrepare(self, sendor, wParam, lParam):
%s
    def OnNotify(self, sendor, sType, wParam, lParam):
        if sType == DUI_MSGTYPE_CLICK:
%s
        if sType == DUI_MSGTYPE_ITEMSELECT:
%s
"""

class GenerateCode():
    def __init__(self):
        self.code = ''

    def GenerateCode(self, skinXmlPath):
        self.skinXmlPath = skinXmlPath
        if not os.path.isfile(skinXmlPath):
            return -2

        tree = ET.ElementTree(file=skinXmlPath)
        initcode = ''
        clickcode = ''
        itemselectcode = ''
        for ctltag in ['Control', 'Label', 'Button', 'Option', 'CheckBox', 'Progress', 'Animation', 'HorizontalLayout', 'VerticalLayout', 'TabLayout', 'List']:
            for elem in tree.iter(tag=ctltag):
                if elem.attrib.has_key('name'):
                    #print elem.tag, elem.attrib
                    initcode += '        self.%s = self.PyFind%s("%s")'%(elem.attrib['name'], ctltag, elem.attrib['name']) + os.linesep
                    if ctltag in ['Button', 'Option', 'CheckBox']:
                        clickcode += '            if sendor == "%s":'%elem.attrib['name'] + os.linesep
                        clickcode += '                pass' + os.linesep
                    if ctltag in ['Combo', 'List']:
                        itemselectcode += '            if sendor == "%s":'%elem.attrib['name'] + os.linesep
                        itemselectcode += '                pass' + os.linesep
        self.code = codeTemplate % (os.path.basename(skinXmlPath).split('.')[0], \
                                    os.path.basename(skinXmlPath).split('.')[0], initcode, \
                                    clickcode if clickcode != '' else '            pass', \
                                    itemselectcode if itemselectcode != '' else '            pass')
        outfile = open(skinXmlPath.replace('.xml','.py'), 'wb')
        outfile.write(self.code)
        outfile.close()
        return 0

def GeneratePythonCode( skinXmlPath):
    return GenerateCode().GenerateCode(skinXmlPath)

if __name__ == '__main__':
    GeneratePythonCode(r'.\skin\test.xml')