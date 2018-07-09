// This needs to be the first include
#include "stdafx.h"

#include "pdfViewer.h"
#include "PdfFileOpener.h"
#include "misc.h"
#include "WindowPlacer.h"

#define MAX_LOADSTRING 100

// ID for menu item
#define IDM_FILE_OPEN 1
#define IDM_FILE_QUIT 2

// Global variables
HINSTANCE hInst;
WCHAR szTitle[MAX_LOADSTRING];                  // Title bar placeholder
WCHAR szWindowClass[MAX_LOADSTRING];            // Class name for the main window
WCHAR szFile[MAX_PATH];                         // Holds the path to the opened file

// Local functions declarations
static void destroyTheWindowAndCleanUp(HWND hWnd);

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

/*
 * Registers a window class.
 */
ATOM MyRegisterClass(HINSTANCE hInstance)
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
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
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
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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

			break;
		}
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            
			/* This is a singleton; NOTE: reference is needed.
			 * Otherwise, copy constructor gets called.*/
			PdfFileOpener& fod = PdfFileOpener::getInstance();

			switch (wmId)
			{
			case IDM_ABOUT:
			{
				DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
				break;
			}
			case IDM_FILE_OPEN:
			{
				OpResult opRes = OpenDialog(hWnd, &fod);
				if (opRes == OpResult::FAILURE)
				{ 
					// Non *.pdf file was chosen. Popup a message box.
					MessageBoxW(NULL, L"Choose *.pdf file.", L"INFO", MB_OK | MB_ICONEXCLAMATION);
				}
				/*else if (opRes == OpResult::QUIT)
				{
					 User opened the dialog but clicked Cancel
					 Do not pop up message box. 
				}*/
				break;
			}
			case IDM_FILE_QUIT:
			{
				int ret = MessageBoxW(hWnd, L"Are you sure you want to quit?",
					L"Message", MB_OKCANCEL);

				if (ret == IDOK) {

					SendMessage(hWnd, WM_CLOSE, 0, 0);
				}

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

			int ret = MessageBoxW(hWnd, L"Are you sure you want to quit?",
				L"Message", MB_OKCANCEL);

			if (ret == IDOK) {

				SendMessage(hWnd, WM_CLOSE, 0, 0);
			}
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

/*
 * Handles messages for info window
 */
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
	{
		// Place the window in the center
		WindowPlacer::centerTheWindow(hDlg);
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
void AddMenus(HWND hwnd) {

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

static void destroyTheWindowAndCleanUp(HWND hWnd)
{
	PostQuitMessage(0);
}