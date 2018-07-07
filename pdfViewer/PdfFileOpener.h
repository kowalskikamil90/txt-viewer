#pragma once
#include "FileOpener.h"

class PdfFileOpener :
	public FileOpener
{
private:
	//Private constructor in order to achive singleton pattern
	PdfFileOpener();
	static PdfFileOpener *instance;
	bool hasEnding(std::wstring const &fullString, std::wstring const &ending);

public:

	static PdfFileOpener* getInstance();

	virtual ~PdfFileOpener();
	virtual bool openFile(OPENFILENAME *ofn) override;
	virtual OpResult validateFilePath() override;
	virtual std::wstring getFilePath() override;
};

