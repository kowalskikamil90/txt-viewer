#pragma once

#include <Windows.h>

#include "misc.h"

#include <string>

class FileOpener
{
protected:
	std::wstring filePath;

public:
	FileOpener() {};
	virtual ~FileOpener() {};
	virtual bool openFile(OPENFILENAME *ofn) = 0;
	virtual OpResult validateFilePath() = 0;
	virtual std::wstring getFilePath() = 0;
};

