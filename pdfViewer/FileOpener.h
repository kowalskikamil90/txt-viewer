#pragma once

#include "misc.h"

#include <Windows.h>
#include <wchar.h>

class FileOpener
{
protected:
	WCHAR filePath[MAX_PATH];

public:
	FileOpener() {};
	virtual ~FileOpener() {};
	virtual bool openFile(OPENFILENAME *ofn) = 0;
	virtual OpResult validateFilePath() = 0;

	/*
	* Getter for filePath
	*/
	PWCHAR getFilePath()
	{
		return filePath;
	}

	/*
	* Setter for filePath
	*/
	void setFilePath(PCWSTR path)
	{
		auto pathLen = wcslen(path);
		wcsncpy_s(filePath, path, pathLen);
	}
};