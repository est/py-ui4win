#pragma once


class PyLog
{
public:
	void LogText(LPCSTR pstrText)
	{
		LOGA(pstrText);
	}
};

void PyExtentInit();
