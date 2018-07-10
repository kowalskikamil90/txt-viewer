#include "gtest/gtest.h"
#include "../pdfViewer/PdfFileOpener.h"
#include "../pdfViewer/misc.h"

TEST(PdfFileOpenerTests, singletonTest)
{
	// Need to be references, otherwise copy constructor gets called
	PdfFileOpener& pfo1 = PdfFileOpener::getInstance();
	PdfFileOpener& pfo2 = PdfFileOpener::getInstance();

	EXPECT_EQ(&pfo1, &pfo2);
}

TEST(PdfFileOpenerTests, validatePathSuccessTest)
{
	FileOpener& pdfOpener = PdfFileOpener::getInstance();

	pdfOpener.setFilePath(L"D://someDir/someFile.pdf");
	EXPECT_EQ(pdfOpener.validateFilePath(), OpResult::SUCCESS);

	pdfOpener.setFilePath(L"C://someDir/someOtherDir/pdfPdfpdf.pdf");
	EXPECT_EQ(pdfOpener.validateFilePath(), OpResult::SUCCESS);

	pdfOpener.setFilePath(L"/pdfPdfpdf.pdf");
	EXPECT_EQ(pdfOpener.validateFilePath(), OpResult::SUCCESS);

	pdfOpener.setFilePath(L"asd.pdf");
	EXPECT_EQ(pdfOpener.validateFilePath(), OpResult::SUCCESS);
}

TEST(PdfFileOpenerTests, validatePathFailureTest)
{
	FileOpener& pdfOpener = PdfFileOpener::getInstance();

	pdfOpener.setFilePath(L".pdf");
	EXPECT_EQ(pdfOpener.validateFilePath(), OpResult::FAILURE);

	pdfOpener.setFilePath(L"C://someDir/someOtherDir/pdfPdfpdf");
	EXPECT_EQ(pdfOpener.validateFilePath(), OpResult::FAILURE);

	pdfOpener.setFilePath(L"/pdfPdfpdf.pdff");
	EXPECT_EQ(pdfOpener.validateFilePath(), OpResult::FAILURE);

	pdfOpener.setFilePath(L"asd.pdfpdf");
	EXPECT_EQ(pdfOpener.validateFilePath(), OpResult::FAILURE);
}