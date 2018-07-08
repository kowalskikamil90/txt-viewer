#pragma once

#include "resource.h"

#include "FileOpener.h"

// Forward declarations
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
void                AddMenus(HWND);
bool                OpenDialog(HWND hwnd, FileOpener *fo);
 