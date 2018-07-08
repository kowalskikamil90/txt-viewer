#pragma once
#include "FileOpener.h"

class PdfFileOpener :
	public FileOpener
{
private:
	//Private constructor in order to achive singleton pattern
	PdfFileOpener();
	bool hasEnding(PWCHAR fullString, PCWSTR ending);

public:

	static PdfFileOpener& getInstance();

	virtual ~PdfFileOpener();
	virtual bool openFile(OPENFILENAME *ofn) override;
	virtual OpResult validateFilePath() override;
};

