#include "stdafx.h"
#include "TextLoaderTxt.h"

#include <fstream>
#include <cassert>

TextLoaderTxt::TextLoaderTxt() {}

/*
 * Get instance of the TextLoaderTxt, Singleton style
 */
TextLoaderTxt& TextLoaderTxt::getInstance()
{
	static TextLoaderTxt instance;
	return instance;
}

/*
 * Loads the text from file and stores it
 */
TextInfo* TextLoaderTxt::loadText(WCHAR *path)
{
	// Decided to use native C++ library here

	// Need to translate path from UNICODE to ASCII
	char asciiPath[256];
	if (UnicodeToAscii(path, asciiPath))
	{
		// Open the file
		std::ifstream file(asciiPath);
		std::string line;
		while (std::getline(file, line))
		{
			textInfo.lines.push_back(line);
		}
	}
	else
	{
		// Should not end up herte. Crash the app for now.
		assert(false);
	}


	return &textInfo;
}
