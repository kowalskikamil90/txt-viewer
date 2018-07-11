#include "stdafx.h"
#include "TextLoaderTxt.h"

#include <fstream>
#include <algorithm>

#define CHARS_PER_PAGE 200

#define space L' '
#define newLine L'\n'

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
		// A line of total 4000 characters may be stored here
		wchar_t wline[4000];

		/* Currently this function supports only ASCII-encoded files
		 * Will not work with UNICODE files - will read bushes.
		 * However, internally, text is stored as a UNICODE.
		 * This is to make it easier to handle updating text area
		 * which currently works together with UNICODE characters.
		 */
		while (std::getline(file, line))
		{
			AsciiToUnicode(line.c_str(), wline);
			wlineStr = wline;
			textInfo.lines.push_back(wlineStr);
		}
	}

	return &textInfo;
}

/*
 * Lines of text, after being loaded, need to be divided into pages.
 */
TextInfo* TextLoaderTxt::divideTextIntoPages()
{
	// Concatenate all lines into one big string
	std::wstring entireText;
	std::wstring page;

	for (auto line : textInfo.lines)
	{
		entireText.append(line);
	}

	// Need to determine how much text goes into single page.
	// For now, constant is used. Look above for details.
	int currentCharIndex = 0;
	int currentCharDelta = 0;
	int length = 0;
	int entireLen = entireText.length();

	while (currentCharIndex < entireLen)
	{
		currentCharIndex += CHARS_PER_PAGE;
		if (currentCharIndex < entireLen)
		{
			// Look for character after current character that ends the page.
			// i.e space or newline
			currentCharDelta = findNextSpaceOrNewLine(entireText, currentCharIndex);
			length = CHARS_PER_PAGE + currentCharDelta;
			page = entireText.substr(currentCharIndex, length);
			textInfo.pages.push_back(page);
			// Move foreward the current character, by the value of delta
			currentCharIndex += currentCharDelta;
		}
		else
		{
			/* In this case we reached the end of file and need to
			 * make the last page out of whatever is left. */
			length = entireLen - currentCharIndex;
			page = entireText.substr(currentCharIndex, length);
			textInfo.pages.push_back(page);
		}
		textInfo.numOfPages++;
	}

	return &textInfo;
}

/*
 * Checks if a character is either space or new line
 */
bool TextLoaderTxt::spaceOrNewLine(wchar_t c)
{
	if (c == space || c == newLine)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*
 * Look for character after current character that ends the page.
 * i.e space, newline or end of string
 */
int TextLoaderTxt::findNextSpaceOrNewLine(std::wstring  entireText, int currentCharIndex)
{
	std::wstring::iterator currentIt = entireText.begin() + currentCharIndex;
	std::wstring::iterator foundIt = std::find_if(currentIt, entireText.end(), TextLoaderTxt::spaceOrNewLine);
	int foundIndex = foundIt - entireText.begin();
	return foundIndex;
}