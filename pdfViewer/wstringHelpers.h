#pragma once

#include <string>

/*
 * Trims whitespaces from the beginning of the string
 */
static inline std::wstring& ltrim(std::wstring& str, const std::wstring& chars = L"\t\n\v\f\r ")
{
	str.erase(0, str.find_first_not_of(chars));
	return str;
}

/*
 * Trims whitespaces from the ending of the string
 */
static inline std::wstring& rtrim(std::wstring& str, const std::wstring& chars = L"\t\n\v\f\r ")
{
	str.erase(str.find_last_not_of(chars) + 1);
	return str;
}

/*
 * Trims whitespaces from the beginning and the ending of the string
 */
static inline std::wstring& trim(std::wstring& str, const std::wstring& chars = L"\t\n\v\f\r ")
{
	return ltrim(rtrim(str, chars), chars);
}