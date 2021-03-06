#include "stdafx.h"

#include "pdfViewer.h"
#include "PdfFileOpener.h"
#include "TxtFileOpener.h"
#include "misc.h"
#include "WidgetPlacer.h"
#include "TextLoaderTxt.h"

#include <Windows.h>
#include <commctrl.h>
#include <strsafe.h>

#define MAX_LOADSTRING 100
#define MAX_PAGE_DIGITS 4

// IDS for menu itemS
#define IDM_FILE_OPEN 1
#define IDM_FILE_QUIT 2

// IDs for widgets
#define ID_UPDOWN_PAGE 3
#define ID_EDIT_PAGE 4
#define ID_DEC_PAGE 5
#define ID_INC_PAGE 6

// Global variables
HINSTANCE hInst;
WCHAR titleBuff[MAX_LOADSTRING];                   // Title bar placeholder
WCHAR wndClassNameBuff[MAX_LOADSTRING];            // Class name for the main window
WCHAR filePathBuff[MAX_PATH];                      // Holds the path to the opened file
int currentPage = 0;                               // Holds the current page being displayed
TextInfo *txtInfoHndl = nullptr;                   // Handle to text info struct
bool fileChosen = false;                           // Holds info if the file was chosen

// Global handles
HWND hWnd, hCurrPage, hStaticText, hLButton, hRButton, hTextArea;
// Default window procedure for buttons
WNDPROC defaultBtnsWndProc;

// Local functions declarations
static void                destroyTheWindowAndCleanUp(HWND hWnd);
static ATOM                MyRegisterClass(HINSTANCE hInstance);
static BOOL                InitInstance(HINSTANCE, int);
static LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
static INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
static void                AddMenus(HWND);
static void                AddControls(HWND);
static void                handleMessageBox(HWND hWnd);
static void                adjustSizeOfWidgets();
static void                switchToPreviousPage();
static void                switchToNextPage();
static void                openFileProcedure();
static void                setCurrentPage(int pageNum);

/*
 * This is the application entry point
 */
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ PWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	// This is always NULL in GT 16-bit applications
    UNREFERENCED_PARAMETER(hPrevInstance);
	// No input arguments for the program
    UNREFERENCED_PARAMETER(lpCmdLine);

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, titleBuff, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PDFVIEWER, wndClassNameBuff, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Initialize the application
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PDFVIEWER));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

/* LOCAL FUNCTIONS DEFINITIONS */

/*
 * Registers a window class for main window.
 */
static ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PDFVIEWER));
    wcex.hCursor        = LoadCursor(nullptr, IDC_HAND);
	wcex.hbrBackground = (HBRUSH)(CreateSolidBrush(RGB(245, 128, 26)));
	wcex.lpszMenuName   = 0;
    wcex.lpszClassName  = wndClassNameBuff;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

/*
 * Displays main widnow.
 */
static BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   //Assign to global variable
   hInst = hInstance;

   hWnd = CreateWindowW(wndClassNameBuff, titleBuff, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

/*
 * Processes messages for main window
 */
static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hDC;
	PAINTSTRUCT ps;

    switch (message)
    {
	case WM_CREATE:
		{
			/* Main window is maximized at the very beginning.
			 * We want to have as big text area as possible. */
			ShowWindow(hWnd, SW_MAXIMIZE);

			// Add menu with possibility to open a file
			AddMenus(hWnd);

			/* ADD ALL REQUIRED CONTROLS */
			AddControls(hWnd);

			break;
		}
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);

			switch (wmId)
			{

			/* Handle page-buttons messages */
			case ID_DEC_PAGE:
			{
				switchToPreviousPage();
				break;
			}
			case ID_INC_PAGE:
			{
				switchToNextPage();
				break;
			}

			/* Handle menu-about item */
			case IDM_ABOUT:
			{
				DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
				break;
			}

			/* Handle menu-open item */
			case IDM_FILE_OPEN:
			{
				openFileProcedure();
				break;
			}

			/* Handle menu-quit item */
			case IDM_FILE_QUIT:
			{
				handleMessageBox(hWnd);
				break;
			}

            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
		break;
        }
	case WM_SIZE:
	{
		// Adjust widgets when window is resized
		adjustSizeOfWidgets();
		break;
    }
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_ESCAPE:
			{
				handleMessageBox(hWnd);
				break;
			}
		case VK_LEFT:
			{
				switchToPreviousPage();
				break;
			}
		case VK_RIGHT:
			{
				switchToNextPage();
				break;
			}
		}
		break;
	}
	case WM_PAINT:
		{
		hDC = BeginPaint(hWnd, &ps);

		HBRUSH hRedBrush = CreateHatchBrush(HS_DIAGCROSS, RGB(255, 0, 0));
		HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hRedBrush);

		RECT r;
		GetClientRect(hWnd, &r);
		Rectangle(hDC, r.left, r.top, r.right - r.left, r.bottom - r.top);

		SelectObject(hDC, hOldBrush);
		DeleteObject(hRedBrush);
		SelectObject(hDC, GetStockObject(BLACK_PEN));

		EndPaint(hWnd, &ps);
		break;
		}
    case WM_DESTROY:
		{
			destroyTheWindowAndCleanUp(hWnd);
			break;
		}
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

/*
 * Processes messages for buttons controls - subclassing
 */
static LRESULT CALLBACK extendedBtnsWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_KEYDOWN:
		{
			switch (wParam)
			{
				case VK_ESCAPE:
				{
					handleMessageBox(hWnd);
					break;
				}
				case VK_LEFT:
				{
					switchToPreviousPage();
					break;
				}
				case VK_RIGHT:
				{
					switchToNextPage();
					break;
				}
			}
			break;
		}
	}
	return CallWindowProc(defaultBtnsWndProc, hWnd, message, wParam, lParam);
}

/*
 * The entire procedure of opening the file and loading text into the window
 */
static void openFileProcedure()
{
	/* This is a singleton; NOTE: reference is needed.
	* Otherwise, copy constructor gets called.*/
	FileOpener& fo = TxtFileOpener::getInstance();

	OpResult opRes = OpenDialog(hWnd, &fo);
	if (opRes == OpResult::FAILURE)
	{
		// Non *.txt file was chosen. Popup a message box.
		MessageBoxW(NULL, L"Choose TXT file.", L"INFO", MB_OK | MB_ICONEXCLAMATION);
	}
	else if (opRes == OpResult::SUCCESS)
	{
		// The file has been successfuly chosen
		fileChosen = true;

		/* This is workaround due to difficulties with finding PDF parsing library
		* that suits requirements for this application. Instead of reading PDF we
		* read *txt files. When some good PDF parsing lib is found, it is adviced
		* to Implement the TextLoader interface in TextLoaderPdf class and use this
		* class instead */
		TextLoader& tl = TextLoaderTxt::getInstance();
		tl.loadText(filePathBuff);
		txtInfoHndl = tl.divideTextIntoPages();

		SetWindowTextW(hTextArea, txtInfoHndl->pages.at(0).c_str());

		/* Convert age number to WCHAR and set the number of pages */
		int pages = txtInfoHndl->numOfPages;

		// Buffer for 'page' string
		wchar_t pagesStr[10];
		swprintf_s(pagesStr, L"/ %d", pages);
		SetWindowTextW(hStaticText, pagesStr);

		// Set the current page as the first page
		currentPage = 1;
		SetWindowTextW(hCurrPage, L"1 ");
	}
}

/*
 * Handling the 'quit' message box
 */
static void handleMessageBox(HWND hWnd)
{
	/* This function is also used in window procedure for buttons
	 * therefore, hWnd may also be the nandle for the buttons, however
	 * we always want to send the WM_CLOSE message to the main window.
	 * That is why the global scope operator is used.	*/
	int ret = MessageBoxW(::hWnd, L"Are you sure you want to quit?",
		L"Message", MB_OKCANCEL);

	if (ret == IDOK) {

		SendMessage(::hWnd, WM_CLOSE, 0, 0);
	}
}

/*
 * Switches text area to dispaly next page
 */
static void switchToNextPage()
{
	if (fileChosen)
	{
		if (currentPage < txtInfoHndl->numOfPages)
		{
			currentPage++;
			setCurrentPage(currentPage);
		}
	}
}

/*
 * Switches text area to dispaly previous page
 */
static void switchToPreviousPage()
{
	if (fileChosen)
	{
		if (currentPage > 1)
		{
			currentPage--;
			setCurrentPage(currentPage);
		}
	}
}

/*
 * Sets current page to gven number
 */
static void setCurrentPage(int pageNum)
{
	wchar_t pageStr[10];
	swprintf_s(pageStr, L"%d ", pageNum);
	SetWindowTextW(hCurrPage, pageStr);
	SetWindowTextW(hTextArea, txtInfoHndl->pages.at(pageNum - 1).c_str());
}

/*
 * Handles messages for info window
 */
static INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
	{
		// Place the window in the center of main window
		WidgetPlacer::centerTheWindow(hDlg);
		return (INT_PTR)TRUE;
	}

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

/*
 * Adds menubar and menus in the main window
 */
static void AddMenus(HWND hwnd) {

	HMENU hMenubar;
	HMENU hFileMenu, hInfoMenu;

	hMenubar = CreateMenu();
	hFileMenu = CreateMenu();
	hInfoMenu = CreateMenu();

	// File menu
	AppendMenuW(hFileMenu, MF_STRING, IDM_FILE_OPEN, L"&Open");
	AppendMenuW(hFileMenu, MF_SEPARATOR, 0, NULL);
	AppendMenuW(hFileMenu, MF_STRING, IDM_FILE_QUIT, L"&Quit");

	// Info menu
	AppendMenuW(hInfoMenu, MF_STRING, IDM_ABOUT, L"&About");

	// Append menus to menubar
	AppendMenuW(hMenubar, MF_POPUP, (UINT_PTR)hFileMenu, L"&File");
	AppendMenuW(hMenubar, MF_POPUP, (UINT_PTR)hInfoMenu, L"&Info");
	SetMenu(hwnd, hMenubar);
}

/*
 * Call when exitting the application
 */
static void destroyTheWindowAndCleanUp(HWND hWnd)
{
	PostQuitMessage(0);
}

/*
 * Adds all required controls
 */
static void AddControls(HWND hWnd)
{
	// Add edit for page selection
	INITCOMMONCONTROLSEX icex;

	icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
	icex.dwICC = ICC_UPDOWN_CLASS;
	InitCommonControlsEx(&icex);

	hCurrPage = CreateWindowW(L"Static", L"0 ", WS_CHILD
		| WS_VISIBLE | ES_RIGHT, 15, 15, 70, 25, hWnd,
		(HMENU)ID_EDIT_PAGE, NULL, NULL);

	hStaticText = CreateWindowW(L"Static", L"/ 0", // Start with page count equal to 1
		WS_CHILD | WS_VISIBLE | SS_LEFT,
		120, 20, 25, 25,
		hWnd, NULL, NULL, NULL);

	// Add buttons for page navigation
	hLButton = CreateWindowW(L"Button", L"<",
		WS_VISIBLE | WS_CHILD,
		20, 150, 80, 25, hWnd, (HMENU)ID_DEC_PAGE, NULL, NULL);
	hRButton = CreateWindowW(L"Button", L">",
		WS_VISIBLE | WS_CHILD,
		120, 150, 80, 25, hWnd, (HMENU)ID_INC_PAGE, NULL, NULL);

	/* Set the window procedure for buttons to ensure that arrow keys work
	 * even when buttons are focused. By default this is not the case,
	 * because the default window procedure for buttons does not handle
	 * these signals as we want.*/

	defaultBtnsWndProc = (WNDPROC)
		SetWindowLong(hLButton, GWL_WNDPROC, (LONG)extendedBtnsWndProc);
	    SetWindowLong(hRButton, GWL_WNDPROC, (LONG)extendedBtnsWndProc);

	// Add the actual text field
	hTextArea = CreateWindowW(L"Static", L"\n\nOpen a TXT file by selecting 'open' from 'file' menu.",
		WS_CHILD | WS_VISIBLE | SS_LEFT,
		20, 200, 1200, 450,
		hWnd, (HMENU)1, NULL, NULL);

	/* POSITION ALL THE WIDGETS */
	adjustSizeOfWidgets();
}

static void adjustSizeOfWidgets()
{
	size2D mainWin = WidgetPlacer::getWindowSize(hWnd);
	size2D margin = WidgetPlacer::getPercentagePixelsOfWindow(Percentage::_1, hWnd);
	int panelXCoord = mainWin.x / 2.8;
	int panelYCoord = margin.y;

	/* WIDGETS: 'edit ' widget, 'upDown' widget, 'static txt' */
	// Position following widgets: 'edit ' widget, 'upDown' widget, 'static txt' widget
	coordinates2D editAndUpDownWidgetsCoords(panelXCoord, panelYCoord);

	size2D editDims = WidgetPlacer::resizeAndPositonWidgetInWnd(
		static_cast<int>(Percentage::_11),
		static_cast<int>(Percentage::_5),
		editAndUpDownWidgetsCoords,
		hCurrPage,
		hWnd);
	size2D staticTextDims = WidgetPlacer::resizeAndPositonWidgetInWnd(
		static_cast<int>(Percentage::_11),
		static_cast<int>(Percentage::_5),
		editAndUpDownWidgetsCoords.addX(editDims),
		hStaticText,
		hWnd);

	// Set font for the following widgets: 'edit ' widget, 'upDown' widget, 'static txt' widget
	int fontH = static_cast<int> (editDims.y * 0.9);
	int fontW = static_cast<int> (fontH * 0.45);
	HFONT hFont1 = CreateFontW(
		fontH, //height of character
		fontW, //width of character
		0,
		0,
		FW_DONTCARE,
		FALSE,
		FALSE,
		FALSE,
		DEFAULT_CHARSET,
		OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS,
		CLEARTYPE_QUALITY,
		VARIABLE_PITCH,
		TEXT("Times New Roman"));

	// Send messages to actually set the font
	SendMessage(hCurrPage, WM_SETFONT, (WPARAM)hFont1, true);
	SendMessage(hStaticText, WM_SETFONT, (WPARAM)hFont1, true);

	/* WIDGETS: buttons for page navigation */

	// Position the following widgets: buttons for page navigation
	coordinates2D buttonsCords(panelXCoord, panelYCoord + editDims.y + margin.y);

	size2D butsDims = WidgetPlacer::resizeAndPositonWidgetInWnd(
		static_cast<int>(Percentage::_11),
		static_cast<int>(Percentage::_5),
		buttonsCords,
		hLButton,
		hWnd);
	WidgetPlacer::resizeAndPositonWidgetInWnd(
		static_cast<int>(Percentage::_10),
		static_cast<int>(Percentage::_5),
		buttonsCords.addX(butsDims).addX(margin),
		hRButton,
		hWnd);

	// Set font for the buttons widgets
	fontH = static_cast<int> (butsDims.y * 0.9);
	fontW = static_cast<int> (fontH * 0.6);;
	HFONT hFont2 = CreateFontW(
		fontH, //height of character
		fontW, //width of character
		0,
		0,
		FW_DONTCARE,
		FALSE,
		FALSE,
		FALSE,
		DEFAULT_CHARSET,
		OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS,
		CLEARTYPE_QUALITY,
		VARIABLE_PITCH,
		TEXT("Times New Roman"));

	// Send messages to actually set the font
	SendMessage(hLButton, WM_SETFONT, (WPARAM)hFont2, true);
	SendMessage(hRButton, WM_SETFONT, (WPARAM)hFont2, true);

	/* WIDGETS: main text field */

	// Position the main text field widget
	coordinates2D tfCords(margin.x, buttonsCords.y + butsDims.y + margin.y);

	WidgetPlacer::resizeAndPositonWidgetInWnd(
		static_cast<int>(Percentage::_97),
		static_cast<int>(Percentage::_75),
		tfCords,
		hTextArea,
		hWnd);

	// Set font for the main text field - size same as panel widgets
	fontH = static_cast<int> (0.75 * editDims.y + 0.3 * editDims.x);
	fontW = static_cast<int> (fontH * 0.45);;
	HFONT hFont3 = CreateFontW(
		fontH, //height of character
		fontW, //width of character
		0,
		0,
		FW_DONTCARE,
		FALSE,
		FALSE,
		FALSE,
		DEFAULT_CHARSET,
		OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS,
		CLEARTYPE_QUALITY,
		VARIABLE_PITCH,
		TEXT("Times New Roman"));

	// Send messages to actually set the font
	SendMessage(hTextArea, WM_SETFONT, (WPARAM)hFont3, true);
}

/* GLOBAL FUNCTIONS DEFINITIONS */

/*
 * Opens 'openfile' dialog box and store filepath
 */
OpResult OpenDialog(HWND hwnd, FileOpener *fo) {

	OPENFILENAME ofn;

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.lpstrFile = filePathBuff;
	ofn.lpstrFile[0] = '\0';
	ofn.hwndOwner = hwnd;
	ofn.nMaxFile = sizeof(filePathBuff);
	ofn.lpstrFilter = TEXT("All files(*.*)\0*.*\0");
	ofn.nFilterIndex = 1;
	ofn.lpstrInitialDir = NULL;
	ofn.lpstrFileTitle = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	OpResult res = fo->openFile(&ofn);

	if (res == OpResult::SUCCESS)
	{
		if (fo->validateFilePath() == OpResult::SUCCESS)
		{
			return OpResult::SUCCESS;
		}
		else 
		{
			return OpResult::FAILURE;
		}
	}
	else
	{
		// Returns OpResult::FAILURE or OpResult::QUIT
		return res;
	}
}