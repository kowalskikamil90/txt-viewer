#pragma once

#include "resource.h"

#include "FileOpener.h"
#include "misc.h"

// Forward declarations
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
void                AddMenus(HWND);
OpResult            OpenDialog(HWND hwnd, FileOpener *fo);
 