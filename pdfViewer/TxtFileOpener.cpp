#include "stdafx.h"
#include "TxtFileOpener.h"

/*
* Get instance of the PdfFileOpener, Singleton style
*/
TxtFileOpener& TxtFileOpener::getInstance()
{
	static TxtFileOpener instance;
	return instance;
}

/*
* Validates if the file path ends with ".pdf"
*/
OpResult TxtFileOpener::validateFilePath()
{
	PCWSTR txtEnding = L".txt";
	if (hasEnding(filePath, txtEnding))
	{
		return OpResult::SUCCESS;
	}
	else
	{
		return OpResult::FAILURE;
	}
}
