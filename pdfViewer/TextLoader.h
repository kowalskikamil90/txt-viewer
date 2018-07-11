#pragma once

#include <Esent.h>
#include <vector>
#include <string>

// Auxiliary struct for storing loaded text information
struct TextInfo
{
	int numOfPages;
	// Stores ASCII characters
	std::vector<std::string> lines;
};

// Interface for text loaders for different file formats
class TextLoader
{
protected:
	TextInfo textInfo;
	bool AsciiToUnicode(const char * szAscii, wchar_t * szUnicode);
	bool UnicodeToAscii(const wchar_t * szUnicode, char * szAscii);

public:
	TextLoader() {};
	virtual ~TextLoader() {};
	virtual TextInfo* loadText(WCHAR *path) = 0;
};