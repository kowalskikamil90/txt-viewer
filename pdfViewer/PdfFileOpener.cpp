#include "stdafx.h"
#include "PdfFileOpener.h"

PdfFileOpener::PdfFileOpener() {}

/*
 * Get instance of the PdfFileOpener, Singleton style
 */
PdfFileOpener& PdfFileOpener::getInstance()
{
	static PdfFileOpener instance;
	return instance;
}

/*
 * Opens the 'open file' dialog
 */
OpResult PdfFileOpener::openFile(OPENFILENAME *ofn)
{
	if (GetOpenFileName(ofn))
	{
		//if (wcslen(ofn->lpstrFile) > 0)
		//{
			/* Get file path and store it as a PTCHAR.
			* The first element (i.e. [0]) is 0 so skip it.
			* lpstrFile is only valid if opening succedeed.
			* This is the case when user picked a file and clicked OK.*/
			wcscpy_s(filePath, ofn->lpstrFile);
			return OpResult::SUCCESS;
		//}
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
 * Validates if the file path ends with ".pdf"
 */
OpResult PdfFileOpener::validateFilePath()
{
	PCWSTR pdfEnding = L".pdf";
	if (hasEnding(filePath, pdfEnding))
	{
		return OpResult::SUCCESS;
	}
	else
	{
		return OpResult::FAILURE;
	}
}

/*
 * Check if string ends with some other sting
 */
bool PdfFileOpener::hasEnding(PWCHAR fullString, PCWSTR ending)
{

	// fullstring starts with NULL character
	auto fsLen = wcslen(fullString+1);
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
