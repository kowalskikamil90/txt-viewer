// This needs to be the first include
#include "stdafx.h"

#include "pdfViewer.h"
#include "PdfFileOpener.h"
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
WCHAR szTitle[MAX_LOADSTRING];                  // Title bar placeholder
WCHAR szWindowClass[MAX_LOADSTRING];            // Class name for the main window
WCHAR szFile[MAX_PATH];                         // Holds the path to the opened file
WORD maxPos = 1, minPos = 0;
TextInfo *ti = nullptr;

// Global handles
HWND hUpDown, hEdit, hStaticText, hLButton, hRButton, hTextArea;

// Local functions declarations
static void                destroyTheWindowAndCleanUp(HWND hWnd);
static ATOM                MyRegisterClass(HINSTANCE hInstance);
static BOOL                InitInstance(HINSTANCE, int);
static LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
static INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
static void                AddMenus(HWND);
static void                AddControls(HWND);
static void                handleMessageBox(HWND hWnd);

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
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PDFVIEWER, szWindowClass, MAX_LOADSTRING);
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
 * Registers a window class.
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
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName   = 0;
    wcex.lpszClassName  = szWindowClass;
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

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
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
				// Implement when pdf parsing ready
				break;
			}
			case ID_INC_PAGE:
			{
				// Implement when pdf parsing ready
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
				/* This is a singleton; NOTE: reference is needed.
				 * Otherwise, copy constructor gets called.*/
				PdfFileOpener& fod = PdfFileOpener::getInstance();

				OpResult opRes = OpenDialog(hWnd, &fod);
				if (opRes == OpResult::FAILURE)
				{ 
					// Non *.pdf file was chosen. Popup a message box.
					MessageBoxW(NULL, L"Choose *.pdf file.", L"INFO", MB_OK | MB_ICONEXCLAMATION);
					break;
				}
				/* This is workaround due to difficulties with finding PDF parsing library
				 * that suits requirements for this application. Instead of reading PDF we
				 * read *txt files. When some good PDF parsing lib is found, it is adviced
				 * to Implement the TextLoader interface in TextLoaderPdf class and use this
				 * class instead */
				TextLoader& tl = TextLoaderTxt::getInstance();
				ti = tl.loadText(szFile);

				//TODO: update text field, etc

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
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: Add here painting code that uses hdc element...
        EndPaint(hWnd, &ps);
     	break;
    }
	case WM_KEYDOWN:
	{
		if (wParam == VK_ESCAPE) {
			handleMessageBox(hWnd);
		}
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

static void handleMessageBox(HWND hWnd)
{
	int ret = MessageBoxW(hWnd, L"Are you sure you want to quit?",
		L"Message", MB_OKCANCEL);

	if (ret == IDOK) {

		SendMessage(hWnd, WM_CLOSE, 0, 0);
	}
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
		// Place the window in the center
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

	hUpDown = CreateWindowW(UPDOWN_CLASSW, NULL, WS_CHILD | WS_VISIBLE
		| UDS_SETBUDDYINT | UDS_ALIGNRIGHT,
		0, 0, 0, 0, hWnd, (HMENU)ID_UPDOWN_PAGE, NULL, NULL);

	hEdit = CreateWindowExW(WS_EX_CLIENTEDGE, WC_EDITW, NULL, WS_CHILD
		| WS_VISIBLE | ES_RIGHT, 15, 15, 70, 25, hWnd,
		(HMENU)ID_EDIT_PAGE, NULL, NULL);

	SendMessageW(hUpDown, UDM_SETBUDDY, (WPARAM)hEdit, 0);
	SendMessageW(hUpDown, UDM_SETRANGE, 0, MAKELPARAM(maxPos, minPos));
	SendMessageW(hUpDown, UDM_SETPOS32, 0, 0);

	hStaticText = CreateWindowW(L"Static", L"/ 1",
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

	// Add the actual text field
	hTextArea = CreateWindowW(L"Static", L"Open a PDF file by selecting\n'open' from 'file' menu.",
		WS_CHILD | WS_VISIBLE | SS_LEFT,
		20, 200, 1200, 450,
		hWnd, (HMENU)1, NULL, NULL);

	/* POSITION ALL THE WIDGETS */
	size2D screen = WidgetPlacer::getScreenSize();
	size2D margin = WidgetPlacer::getPercentagePixels(Percentage::_1);
	int panelXCoord = screen.x / 3;
	int panelYCoord = margin.y;

	/* WIDGETS: 'edit ' widget, 'upDown' widget, 'static txt' */
	// Position following widgets: 'edit ' widget, 'upDown' widget, 'static txt' widget
	coordinates2D editAndUpDownWidgetsCoords(panelXCoord, panelYCoord);

	size2D editDims = WidgetPlacer::resizeAndPositonWidget(static_cast<int>(Percentage::_10),
		static_cast<int>(Percentage::_5),
		editAndUpDownWidgetsCoords,
		hEdit);
	size2D upDownDims = WidgetPlacer::resizeAndPositonWidget(static_cast<int>(Percentage::_3),
		static_cast<int>(Percentage::_5),
		editAndUpDownWidgetsCoords.addX(editDims),
		hUpDown);
	size2D staticTextDims = WidgetPlacer::resizeAndPositonWidget(static_cast<int>(Percentage::_10),
		static_cast<int>(Percentage::_5),
		editAndUpDownWidgetsCoords.addX(upDownDims).addX(editDims),
		hStaticText);

	// Set font for the following widgets: 'edit ' widget, 'upDown' widget, 'static txt' widget
	int fontH = static_cast<int> (editDims.y * 0.9);
	int fontW = static_cast<int> (fontH * 0.45);
	HFONT hFont1 = CreateFontW(fontH, //height of character
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
	SendMessage(hEdit, WM_SETFONT, (WPARAM)hFont1, true);
	SendMessage(hStaticText, WM_SETFONT, (WPARAM)hFont1, true);

	/* WIDGETS: buttons for page navigation */

	// Position the following widgets: buttons for page navigation
	coordinates2D buttonsCords(panelXCoord, panelYCoord + editDims.y + margin.y);

	size2D butsDims = WidgetPlacer::resizeAndPositonWidget(static_cast<int>(Percentage::_11),
		static_cast<int>(Percentage::_5),
		buttonsCords,
		hLButton);
	WidgetPlacer::resizeAndPositonWidget(static_cast<int>(Percentage::_11),
		static_cast<int>(Percentage::_5),
		buttonsCords.addX(butsDims).addX(margin),
		hRButton);

	// Set font for the buttons widgets
	fontH = static_cast<int> (butsDims.y * 0.9);
	fontW = static_cast<int> (fontH * 0.6);;
	HFONT hFont2 = CreateFontW(fontH, //height of character
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

	WidgetPlacer::resizeAndPositonWidget(static_cast<int>(Percentage::_98),
		static_cast<int>(Percentage::_75),
		tfCords,
		hTextArea);

	// Set font for the main text field - size same as panel widgets
	fontH = static_cast<int> (editDims.y * 2);
	fontW = static_cast<int> (fontH * 0.45);;
	HFONT hFont3 = CreateFontW(fontH, //height of character
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
	ofn.lpstrFile = szFile;
	ofn.lpstrFile[0] = '\0';
	ofn.hwndOwner = hwnd;
	ofn.nMaxFile = sizeof(szFile);
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