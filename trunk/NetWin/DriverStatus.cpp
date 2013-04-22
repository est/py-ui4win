#include "StdAfx.h"

#include <strsafe.h>

#include <setupapi.h>
#pragma comment(lib, "setupapi.lib")

#include <cfgmgr32.h>

#include <WinIoCtl.h>
#include <usbdi.h>
#include <usb100.h>
#include <array>
#include "DriverStatus.h"

CDriverStatus::CDriverStatus(void)
{

}

CDriverStatus::~CDriverStatus(void)
{
}

std::string CDriverStatus::DriverDiagnose()
{
	std::string output;
	output += "没有发现手机设备\n";

	return output;
}