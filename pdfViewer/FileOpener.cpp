#include "stdafx.h"

#include "FileOpener.h"

/*
 * Opens the 'open file' dialog
 */
OpResult FileOpener::openFile(OPENFILENAME *ofn)
{
	if (GetOpenFileName(ofn))
	{
		wcscpy_s(filePath, ofn->lpstrFile);
		return OpResult::SUCCESS;
	}
	else
	{
		DWORD ret = CommDlgExtendedError();
		if (ret == 0)
		{
			/* This is the case when user opened the dialog but clicked Cancel
			* or closed the dialog window.*/
			return OpResult::QUIT;
		}
		else
		{
			// GetOpenFileName() failed
			return OpResult::FAILURE;
		}
	}
}

/*
 * Getter for filePath
 */
PWCHAR FileOpener::getFilePath()
{
	return filePath;
}

/*
 * Setter for filePath
 */
void FileOpener::setFilePath(PCWSTR path)
{
	auto pathLen = wcslen(path);
	wcsncpy_s(filePath, path, pathLen);
}

/*
 * Check if string ends with some other sting
 */
bool FileOpener::hasEnding(PWCHAR fullString, PCWSTR ending)
{

	// fullstring starts with NULL character
	auto fsLen = wcslen(fullString + 1);
	auto endLen = wcslen(ending);
	auto diff = fsLen - endLen;
	if (fsLen >= endLen)
	{
		if (0 == wcsncmp(fullString + 1 + diff, ending, fsLen - endLen))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}
