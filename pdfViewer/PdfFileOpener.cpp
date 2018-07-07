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
		/* Get file path and store it as a string.
		 * The first element (i.e. [0]) is 0 so skip it.*/
		for (unsigned int i = 1; i < ofn->nMaxFile; i++)
		{
			TCHAR tc = ofn->lpstrFile[i];
			const wchar_t c = static_cast<const wchar_t> (tc);
			if (c != NULL)
			{
				filePath.append(&c);
			}
			else
			{
				break;
			}
		}
	}

	return ret;
}

/*
 * Validates if the file path ends with ".pdf"
 */
OpResult PdfFileOpener::validateFilePath()
{
	std::wstring pdfEnding(L".pdf");
	if (hasEnding(filePath, pdfEnding)) return OpResult::SUCCESS;
	else return OpResult::FAILURE;
}

/*
 * Getter for filePath
 */
std::wstring PdfFileOpener::getFilePath()
{
	return filePath;
}

/*
 * Check if string ends with some other sting
 */
bool PdfFileOpener::hasEnding
  (std::wstring const &fullString, std::wstring const &ending) {
	if (fullString.length() >= ending.length())
	{
		return (0 == fullString.compare(fullString.length()
			    - ending.length(), ending.length(), ending));
	}
	else
	{
		return false;
	}
  }
