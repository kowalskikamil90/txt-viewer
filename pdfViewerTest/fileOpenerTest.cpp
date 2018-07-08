#include "gtest/gtest.h"
#include "../pdfViewer/FileOpener.h"
#include "../pdfViewer/PdfFileOpener.h"

#include <tchar.h>

TEST(FileOpenerTests, pathSetterGetterTest)
{
	PdfFileOpener& pdfOpener = PdfFileOpener::getInstance();
	PCTSTR pathToSet = L"D://someDirectory/someFile.asd";
	pdfOpener.setFilePath(pathToSet);
	PTCHAR gotPath = pdfOpener.getFilePath();

	ASSERT_EQ(_tcscmp(pathToSet, gotPath), 0);
}