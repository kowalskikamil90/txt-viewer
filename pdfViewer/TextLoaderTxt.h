#pragma once
#include "TextLoader.h"

class TextLoaderTxt :
	public TextLoader
{
private:
	// Private constructor to achive Singleton behaviour
	TextLoaderTxt();

public:
	static TextLoaderTxt& getInstance();
	virtual TextInfo* loadText(WCHAR *path);
};