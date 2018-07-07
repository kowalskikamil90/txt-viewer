#include "stdafx.h"
#include "PdfFileOpener.h"

PdfFileOpener* PdfFileOpener::instance = nullptr;

PdfFileOpener::PdfFileOpener()
{
}

PdfFileOpener::~PdfFileOpener()
{
	// Leads to endless recursion problem
	// delete PdfFileOpener::instance;
}

/*
 * Get instance of the PdfFileOpener, Singleton style
 */
PdfFileOpener* PdfFileOpener::getInstance()
{
	if (PdfFileOpener::instance != nullptr)
	{
		return PdfFileOpener::instance;
	}
	else return new PdfFileOpener();
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
		_tcscpy_s(filePath, ofn->lpstrFile);
	}

	return ret;
}

/*
 * Validates if the file path ends with ".pdf"
 */
OpResult PdfFileOpener::validateFilePath()
{
	PCTSTR pdfEnding = L".pdf";
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
 * Getter for filePath
 */
PTCHAR PdfFileOpener::getFilePath()
{
	return filePath;
}

/*
 * Check if string ends with some other sting
 */
bool PdfFileOpener::hasEnding
  (PTCHAR fullString, PCTSTR ending) {

	// fullstring starts with NULL character
	auto fsLen = _tcslen(fullString+1);
	auto endLen = _tcslen(ending);
	auto diff = fsLen - endLen;
	if (fsLen >= endLen)
	{
		if (0 == _tcsncmp(fullString + 1 + diff, ending, fsLen - endLen))
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
