#pragma once

typedef enum UsbDevState {udsNotAndroid, udsAndroidNoDriver, udsAndroidOtherMode, udsAndroidNormal};

typedef struct tagUsbDev {
	WORD wVid, wPid;
	UsbDevState eState;
	WCHAR szSerial[64];
	WCHAR szPath[20];
	WCHAR szProduct[32];
}UsbDev, *PUsbDev;


typedef struct tagVidPid {
	WORD wVid, wPid;
} VidPid;

class CDriverStatus
{
public:
	CDriverStatus(void);
	~CDriverStatus(void);

	void GetActiveUsbDevs(CSimpleArray<UsbDev>& listUsbDevs);
	BOOL GetStringProp(HANDLE hHub, UINT nPort, UINT nIndex, LPWSTR szVal, WORD wSize);
	void GetInstalledAndroidDevs(CSimpleArray<VidPid>& listAndroidVidPids, BOOL bActive);
	BOOL IsDriverInstalled(WORD wVid, WORD wPid);
	UsbDevState GetUsbDevState(WORD wVid, WORD wPid);
	BOOL IsMobile(WORD wVid, WORD wPid);
	void GetUsbDevFromHub(LPCWSTR szHubName, LPCWSTR szTreePath, CSimpleArray<UsbDev>& listUsbDevs);
	BOOL CheckDrvStatus(CString strInstanceId);
	int CheckDrvProblem(CString strInstanceId);
	void GetAllInstalledAndroil(CSimpleArray<CString>& listAndroidVidPids);
	BOOL GetAllHardWare(WORD wVid, WORD wPid, CSimpleArray<CString>& listAndroidVidPids);
	BOOL GetRootUsb(CSimpleArray<CString>& listAndroidVidPids);
	VOID GetUpdateIntanceID( LPCTSTR lpRootNode, CSimpleArray<CString>& vecNode );
	BOOL GetAllUsbInstanceID(CSimpleArray<CString>& listInstanceID);
	BOOL IsThereAdbAvailable();
	std::string DriverDiagnose();
};
