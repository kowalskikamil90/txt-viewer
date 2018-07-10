#pragma once
#include "FileOpener.h"

class TxtFileOpener :
	public FileOpener
{
private:
	//Private constructor in order to achive singleton pattern
	TxtFileOpener();

public:

	static TxtFileOpener& getInstance();

	virtual OpResult validateFilePath() override;
};

