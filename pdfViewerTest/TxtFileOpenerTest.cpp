#include "gtest/gtest.h"
#include "../pdfViewer/TxtFileOpener.h"
#include "../pdfViewer/misc.h"

TEST(TxtFileOpenerTests, singletonTest)
{
	// Need to be references, otherwise copy constructor gets called
	TxtFileOpener& pfo1 = TxtFileOpener::getInstance();
	TxtFileOpener& pfo2 = TxtFileOpener::getInstance();

	EXPECT_EQ(&pfo1, &pfo2);
}

TEST(TxtFileOpenerTests, validatePathSuccessTest)
{
	FileOpener& txtOpener = TxtFileOpener::getInstance();

	txtOpener.setFilePath(L"D://someDir/someFile.txt");
	EXPECT_EQ(txtOpener.validateFilePath(), OpResult::SUCCESS);

	txtOpener.setFilePath(L"C://someDir/someOtherDir/pdfPdfpdf.txt");
	EXPECT_EQ(txtOpener.validateFilePath(), OpResult::SUCCESS);

	txtOpener.setFilePath(L"/pdfPdfpdf.txt");
	EXPECT_EQ(txtOpener.validateFilePath(), OpResult::SUCCESS);

	txtOpener.setFilePath(L"asd.txt");
	EXPECT_EQ(txtOpener.validateFilePath(), OpResult::SUCCESS);
}

TEST(TxtFileOpenerTests, validatePathFailureTest)
{
	FileOpener& txtOpener = TxtFileOpener::getInstance();

	txtOpener.setFilePath(L".txt");
	EXPECT_EQ(txtOpener.validateFilePath(), OpResult::FAILURE);

	txtOpener.setFilePath(L"C://someDir/someOtherDir/txtTxttxt");
	EXPECT_EQ(txtOpener.validateFilePath(), OpResult::FAILURE);

	txtOpener.setFilePath(L"/aaaaaaa.txtt");
	EXPECT_EQ(txtOpener.validateFilePath(), OpResult::FAILURE);

	txtOpener.setFilePath(L"asd.txttxt");
	EXPECT_EQ(txtOpener.validateFilePath(), OpResult::FAILURE);
}