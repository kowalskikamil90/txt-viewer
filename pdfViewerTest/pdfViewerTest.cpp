#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "MockFileOpener.h"
#include "../pdfViewer/pdfViewer.h"
#include "../pdfViewer/misc.h"

using ::testing::_;
using ::testing::Return;

// Dummy test in order to setup and test the testing environment
TEST(PdfViewerTests, openDialogTestSuccess)
{
	MockFileOpener mockFileOpener;
	HWND hwnd;
	ZeroMemory(&hwnd, sizeof(HWND));

	// Setup expectations and return values
	EXPECT_CALL(mockFileOpener, openFile(_))
		.Times(1)
		.WillOnce(Return(true));
	EXPECT_CALL(mockFileOpener, validateFilePath())
		.Times(1)
		.WillOnce(Return(OpResult::SUCCESS));

	// Test the actual function
	EXPECT_TRUE(OpenDialog(hwnd, &mockFileOpener));
}

// Dummy test in order to setup and test the testing environment
TEST(PdfViewerTests, openDialogTestOpenFileFailure)
{
	MockFileOpener mockFileOpener;
	HWND hwnd;
	ZeroMemory(&hwnd, sizeof(HWND));

	// Setup expectations and return values
	EXPECT_CALL(mockFileOpener, openFile(_))
		.Times(1)
		.WillOnce(Return(false));
	EXPECT_CALL(mockFileOpener, validateFilePath())
		.Times(0);

	// Test the actual function
	EXPECT_FALSE(OpenDialog(hwnd, &mockFileOpener));
}

// Dummy test in order to setup and test the testing environment
TEST(PdfViewerTests, openDialogTestValidateFailure)
{
	MockFileOpener mockFileOpener;
	HWND hwnd;
	ZeroMemory(&hwnd, sizeof(HWND));

	// Setup expectations and return values
	EXPECT_CALL(mockFileOpener, openFile(_))
		.Times(1)
		.WillOnce(Return(true));
	EXPECT_CALL(mockFileOpener, validateFilePath())
		.Times(1)
		.WillOnce(Return(OpResult::FAILURE));

	// Test the actual function
	EXPECT_FALSE(OpenDialog(hwnd, &mockFileOpener));
}