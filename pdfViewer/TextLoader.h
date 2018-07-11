#pragma once

#include <Esent.h>
#include <vector>
#include <string>

// Auxiliary struct for storing loaded text information
struct TextInfo
{
	int numOfPages;
	// Store UNICODE characters
	std::vector<std::wstring> lines;
	std::vector<std::wstring> pages;
};

// Interface for text loaders for different file formats
class TextLoader
{
protected:
	TextInfo textInfo;
	void initializeTextLoader();

public:
	TextLoader() {};
	virtual ~TextLoader() {};
	virtual TextInfo* loadText(WCHAR *path) = 0;
	virtual TextInfo* divideTextIntoPages() = 0;

	bool AsciiToUnicode(const char * szAscii, wchar_t * szUnicode);
	bool UnicodeToAscii(const wchar_t * szUnicode, char * szAscii);
};