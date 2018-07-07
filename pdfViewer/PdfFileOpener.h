#pragma once
#include "FileOpener.h"

class PdfFileOpener :
	public FileOpener
{
private:
	//Private constructor in order to achive singleton pattern
	PdfFileOpener();
	static PdfFileOpener *instance;
	bool hasEnding(PTCHAR fullString, PCTSTR ending);

public:

	static PdfFileOpener* getInstance();

	virtual ~PdfFileOpener();
	virtual bool openFile(OPENFILENAME *ofn) override;
	virtual OpResult validateFilePath() override;
	virtual PTCHAR getFilePath() override;
};

