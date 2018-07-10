#pragma once

#include "misc.h"

#include <Windows.h>
#include <wchar.h>

class FileOpener
{
protected:
	WCHAR filePath[MAX_PATH];
	bool hasEnding(PWCHAR fullString, PCWSTR ending);

public:
	FileOpener() {};
	virtual ~FileOpener() {};
	virtual OpResult openFile(OPENFILENAME *ofn);
	virtual OpResult validateFilePath() = 0;
	PWCHAR getFilePath();
	void setFilePath(PCWSTR path);
};