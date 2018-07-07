#pragma once

#include <Windows.h>

#include "misc.h"

class FileOpener
{
protected:
	TCHAR filePath[MAX_PATH];

public:
	FileOpener() {};
	virtual ~FileOpener() {};
	virtual bool openFile(OPENFILENAME *ofn) = 0;
	virtual OpResult validateFilePath() = 0;
	virtual PTCHAR getFilePath() = 0;
};