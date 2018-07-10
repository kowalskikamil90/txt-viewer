#include "gtest/gtest.h"
#include "../pdfViewer/PdfFileOpener.h"

#include <wchar.h>

TEST(FileOpenerTests, pathSetterGetterTest)
{
	PdfFileOpener& pdfOpener = PdfFileOpener::getInstance();
	PCWSTR pathToSet = L"D://someDirectory/someFile.asd";
	pdfOpener.setFilePath(pathToSet);
	PWCHAR gotPath = pdfOpener.getFilePath();

	EXPECT_EQ(wcscmp(pathToSet, gotPath), 0);
}