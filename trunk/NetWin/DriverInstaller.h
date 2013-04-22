#pragma once

class CDriverInstaller
{
public:
	CDriverInstaller(void);
	~CDriverInstaller(void);

	BOOL InstallDriverFromInf(std::string infPath);
};
