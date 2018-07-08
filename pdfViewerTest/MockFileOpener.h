#include "gmock/gmock.h"

#include "../pdfViewer/FileOpener.h"

class MockFileOpener : public FileOpener {
public:
	MOCK_METHOD1(openFile,
		bool(OPENFILENAME *ofn));
	MOCK_METHOD0(validateFilePath,
		OpResult());
};