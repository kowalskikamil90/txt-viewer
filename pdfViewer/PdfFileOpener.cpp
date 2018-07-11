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