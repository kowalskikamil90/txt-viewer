#include "stdafx.h"

#include "WindowPlacer.h"

/*
 * Returns size of the screen
 */
size2D WindowPlacer::getScreenSize()
{
	size2D screenSize(GetSystemMetrics(SM_CXSCREEN),
		              GetSystemMetrics(SM_CYSCREEN));
	return screenSize;
}

/*
 * Returns the coordinates of center of the screen
 */
coordinates2D WindowPlacer::getScreenCenter()
{
	size2D screenSize = getScreenSize();
	screenSize = screenSize / 2;
	coordinates2D coord(screenSize.x, screenSize.y);
	return coord;
}

/*
 * Given window size, calculates the position of the window (upper, left corner).
 */
coordinates2D WindowPlacer::calculateCenteredWindowCoords(size2D wndSize)
{
	coordinates2D center = getScreenCenter();

	// Upper, left corner of the window
	coordinates2D wndUpperLeftCorner(center.x - wndSize.x/2, center.y -wndSize.y/2);
	return wndUpperLeftCorner;
}

/*
 * places the window in the center of the screen
 */
void WindowPlacer::centerTheWindow(HWND hwnd)
{
	/* Place the window in the center */
	RECT rect = { 0 };
	GetWindowRect(hwnd, &rect);
	//Size in pixels
	size2D wndSize(rect.right - rect.left,
		           rect.bottom - rect.top);
	coordinates2D coords = calculateCenteredWindowCoords(wndSize);
	SetWindowPos(hwnd,
		         HWND_TOP,
		         coords.x, coords.y,
		         wndSize.x, wndSize.y,
		         SWP_SHOWWINDOW);
}