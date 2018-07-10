#pragma once

#include <Esent.h>

// Auxiliary struct for storing loaded text information
struct TextInfo
{
	int numOfPages;
	/* Field For storing the actual text for each page.
	* Needs to be dynamically allocated. Double pointer. */
	WCHAR **pagesText;
};

// Interface for text loaders for different file formats
class TextLoader
{
protected:
	TextInfo textInfo;

public:
	TextLoader() {};
	virtual ~TextLoader() {};
	virtual TextInfo* loadText(WCHAR *path) = 0;
};