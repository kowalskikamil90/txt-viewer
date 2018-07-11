#pragma once
#include "TextLoader.h"

class TextLoaderTxt :
	public TextLoader
{
private:
	// Private constructor to achive Singleton behaviour
	TextLoaderTxt();

	static bool spaceOrNewLine(wchar_t c);
	int findNextSpaceOrNewLine(std::wstring  entiretext, int currentCharIndex);

public:
	static TextLoaderTxt& getInstance();
	virtual TextInfo* loadText(WCHAR *path);
	virtual TextInfo* divideTextIntoPages();
};