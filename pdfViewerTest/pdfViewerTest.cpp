#include "gtest/gtest.h"
#include "../pdfViewer/func1.h"

// Dummy test in order to setup and test the testing environment
TEST(DummyTests, Func1)
{
	EXPECT_DOUBLE_EQ(2.22, func1());
}