#include "stdafx.h"
#include "TextLoaderTxt.h"

#include <fstream>

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
	/* Decided to use native C++ library here */

	// Need to translate path from UNICODE to ASCII
	char asciiPath[MAX_PATH];
	if (UnicodeToAscii(path, asciiPath))
	{
		// Open the file
		std::ifstream file(asciiPath);
		std::string line;
		std::wstring wlineStr;
		// A line of total 400 characters may be stored here
		wchar_t wline[4000];

		// Currently this function supports only ASCII-encoded files
		// Will not work with UNICODE files - will read bushes.
		while (std::getline(file, line))
		{
			AsciiToUnicode(line.c_str(), wline);
			wlineStr = wline;
			textInfo.lines.push_back(wlineStr);
		}
	}

	return &textInfo;
}
