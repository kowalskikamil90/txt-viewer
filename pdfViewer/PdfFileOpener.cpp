#include "stdafx.h"
#include "PdfFileOpener.h"

PdfFileOpener::PdfFileOpener()
{
}

PdfFileOpener::~PdfFileOpener()
{
}

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
bool PdfFileOpener::openFile(OPENFILENAME *ofn)
{
	BOOL ret = GetOpenFileName(ofn);
	if (ret)
	{
		/* Get file path and store it as a PTCHAR.
		 * The first element (i.e. [0]) is 0 so skip it.
		 * lpstrFile is only valid if opening succedeed.*/
		wcscpy_s(filePath, ofn->lpstrFile);
	}

	return ret;
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
bool PdfFileOpener::hasEnding
  (PWCHAR fullString, PCWSTR ending) {

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
