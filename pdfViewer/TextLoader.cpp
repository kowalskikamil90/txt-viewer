#include "stdafx.h"

#include "TextLoader.h"

bool TextLoader::AsciiToUnicode(const char * szAscii, wchar_t * szUnicode)
{
	int len, i;
	if ((szUnicode == NULL) || (szAscii == NULL))
		return false;
	len = strlen(szAscii);
	for (i = 0; i<len + 1; i++)
		*szUnicode++ = static_cast<wchar_t>(*szAscii++);
	return true;
}

bool TextLoader::UnicodeToAscii(const wchar_t * szUnicode, char * szAscii)
{
	int len, i;
	if ((szUnicode == NULL) || (szAscii == NULL))
		return false;
	len = wcslen(szUnicode);
	for (i = 0; i<len + 1; i++)
		*szAscii++ = static_cast<char>(*szUnicode++);
	return true;
}

void TextLoader::initializeTextLoader()
{
	textInfo.numOfPages = 0;
	textInfo.lines.clear();
	textInfo.pages.clear();
}