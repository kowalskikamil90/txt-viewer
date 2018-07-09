#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "MockFileOpener.h"
#include "../pdfViewer/pdfViewer.h"
#include "../pdfViewer/misc.h"

using ::testing::_;
using ::testing::Return;

TEST(PdfViewerTests, openDialogSuccessTest)
{
	MockFileOpener mockFileOpener;
	HWND hwnd;

	//No really relevant but needed to silence the compiler
	ZeroMemory(&hwnd, sizeof(HWND));

	// Setup expectations and return values
	EXPECT_CALL(mockFileOpener, openFile(_))
		.Times(1)
		.WillOnce(Return(OpResult::SUCCESS));
	EXPECT_CALL(mockFileOpener, validateFilePath())
		.Times(1)
		.WillOnce(Return(OpResult::SUCCESS));

	// Test the actual function
	EXPECT_TRUE(OpenDialog(hwnd, &mockFileOpener) == OpResult::SUCCESS);
}

TEST(PdfViewerTests, openDialogOpenFileFailureTest)
{
	MockFileOpener mockFileOpener;
	HWND hwnd;
	ZeroMemory(&hwnd, sizeof(HWND));

	// Setup expectations and return values
	EXPECT_CALL(mockFileOpener, openFile(_))
		.Times(1)
		.WillOnce(Return(OpResult::FAILURE));
	EXPECT_CALL(mockFileOpener, validateFilePath())
		.Times(0);

	// Test the actual function
	EXPECT_TRUE(OpenDialog(hwnd, &mockFileOpener) == OpResult::FAILURE);
}

TEST(PdfViewerTests, openDialogValidateFailureTest)
{
	MockFileOpener mockFileOpener;
	HWND hwnd;
	ZeroMemory(&hwnd, sizeof(HWND));

	// Setup expectations and return values
	EXPECT_CALL(mockFileOpener, openFile(_))
		.Times(1)
		.WillOnce(Return(OpResult::SUCCESS));
	EXPECT_CALL(mockFileOpener, validateFilePath())
		.Times(1)
		.WillOnce(Return(OpResult::FAILURE));

	// Test the actual function
	EXPECT_TRUE(OpenDialog(hwnd, &mockFileOpener) == OpResult::FAILURE);
}

TEST(PdfViewerTests, openDialogCloseOrCancelTest)
{
	MockFileOpener mockFileOpener;
	HWND hwnd;
	ZeroMemory(&hwnd, sizeof(HWND));

	// Setup expectations and return values
	EXPECT_CALL(mockFileOpener, openFile(_))
		.Times(1)
		.WillOnce(Return(OpResult::QUIT));
	EXPECT_CALL(mockFileOpener, validateFilePath())
		.Times(0);

	// Test the actual function
	EXPECT_TRUE(OpenDialog(hwnd, &mockFileOpener) == OpResult::QUIT);
}