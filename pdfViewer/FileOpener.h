#pragma once

#include "misc.h"

#include <Windows.h>
#include <tchar.h>

class FileOpener
{
protected:
	TCHAR filePath[MAX_PATH];

public:
	FileOpener() {};
	virtual ~FileOpener() {};
	virtual bool openFile(OPENFILENAME *ofn) = 0;
	virtual OpResult validateFilePath() = 0;

	/*
	* Getter for filePath
	*/
	PTCHAR getFilePath()
	{
		return filePath;
	}

	/*
	* Setter for filePath
	*/
	void setFilePath(PCTSTR path)
	{
		auto pathLen = _tcslen(path);
		_tcsncpy_s(filePath, path, pathLen);
	}
};