#pragma once
#include "FileOpener.h"

class PdfFileOpener :
	public FileOpener
{
private:
	//Private constructor in order to achive singleton pattern
	PdfFileOpener();

public:

	static PdfFileOpener& getInstance();

	virtual OpResult validateFilePath() override;
};

