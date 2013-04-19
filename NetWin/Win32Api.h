#pragma once

class CWin32Api
{
public:
	CWin32Api(void);
	~CWin32Api(void);
	std::string GetExeDirectory();
	void SetCurrentDirectory(std::string dir);
	void SetCurrentDirectoryToExePath();
	void SetWaitCursor();
	void SetArrowCursor();
	void ShellExcute(int hwnd,
		std::string lpOperation,
		std::string lpFile,
		std::string lpParameters,
		std::string lpDirectory,
		int nShowCmd
		);
	std::string SelectFile(int hwnd, std::string filter);
	std::string SelectFolder(int hwnd, std::string title, std::string saveTag);
};
