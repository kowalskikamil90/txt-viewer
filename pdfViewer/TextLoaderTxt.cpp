#include "stdafx.h"
#include "TextLoaderTxt.h"

TextLoaderTxt::TextLoaderTxt() {}

/*
 * Get instance of the TextLoaderTxt, Singleton style
 */
TextLoaderTxt& TextLoaderTxt::getInstance()
{
	static TextLoaderTxt instance;
	return instance;
}

TextInfo* TextLoaderTxt::loadText(WCHAR *path)
{
	textInfo.numOfPages = 100;
	return &textInfo;
}
