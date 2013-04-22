#include "StdAfx.h"
#include "DriverInstaller.h"
#include <objbase.h>
#include <setupapi.h>
#include <strsafe.h>
#include "util.h"
#include "newDev.h"
// #pragma comment(lib,"newdev.lib")
#include "Cfgmgr32.h"
#include "Util.h"
#include "DriverStatus.h"
using namespace std;

#define SIZECHARS(x)         (sizeof((x))/sizeof(TCHAR))

CSimpleArray<WORD> g_phone;

CDriverInstaller::CDriverInstaller(void)
{
}

CDriverInstaller::~CDriverInstaller(void)
{
}

BOOL CDriverInstaller::InstallDriverFromInf(std::string infPath)
{
	return FALSE;
}
