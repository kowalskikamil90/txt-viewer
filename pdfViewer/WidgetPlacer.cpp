#include "stdafx.h"

#include "WidgetPlacer.h"

/*
 * Returns size of the screen
 */
size2D WidgetPlacer::getScreenSize()
{
	size2D screenSize(GetSystemMetrics(SM_CXSCREEN),
		              GetSystemMetrics(SM_CYSCREEN));
	return screenSize;
}

/*
 * Returns size of the window
 */
size2D WidgetPlacer::getWindowSize(HWND hwnd)
{
	RECT wndRect;
	GetWindowRect(hwnd, &wndRect);
	size2D wndSize(wndRect.right - wndRect.left,
		           wndRect.bottom - wndRect.top);
	return wndSize;
}

/*
 * Returns the coordinates of center of the screen
 */
coordinates2D WidgetPlacer::getScreenCenter()
{
	size2D screenSize = getScreenSize();
	screenSize = screenSize / 2;
	coordinates2D coord(screenSize.x, screenSize.y);
	return coord;
}

/*
 * Returns the coordinates of center of the window
 */
coordinates2D WidgetPlacer::getWindowCenter(HWND hwnd)
{
	size2D screenSize = getWindowSize(hwnd);
	screenSize = screenSize / 2;
	coordinates2D coord(screenSize.x, screenSize.y);
	return coord;
}

/*
 * Given window size, calculates the position of the window (upper, left corner).
 */
coordinates2D WidgetPlacer::calculateCenteredWindowCoords(size2D wndSize)
{
	coordinates2D center = getScreenCenter();

	// Upper, left corner of the window
	coordinates2D wndUpperLeftCorner(center.x - wndSize.x/2, center.y -wndSize.y/2);
	return wndUpperLeftCorner;
}

/*
 * places the window in the center of the screen
 */
void WidgetPlacer::centerTheWindow(HWND hwnd)
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

/*
 * Sets widget size according to screen's width and height percentage
 * and places it in specified place. Returns dimensions of the widget.
 */
size2D WidgetPlacer::resizeAndPositonWidget(int screenWPercentage,
	                                        int screenHPercentage,
                                            coordinates2D position,
	                                        HWND hWidget)
{
	// Get screen width and height
	size2D screen = getScreenSize();

	// Calculate wanted dimensions of the widget (in pixels)
	size2D dimensions(static_cast<int> ((screenWPercentage) / 100.0 * screen.x),
                      static_cast<int> ((screenHPercentage) / 100.0 * screen.y));

	SetWindowPos(hWidget,
		         HWND_TOP, // Z axis order
		         position.x,
		         position.y,
		         dimensions.x,
		         dimensions.y,
		         SWP_SHOWWINDOW);

	return dimensions;
}

/*
 * Sets widget size according to main window's width and height percentage
 * and places it in specified place. Returns dimensions of the widget.
 */
size2D WidgetPlacer::resizeAndPositonWidgetInWnd(int wndWPercentage,
	                                            int wndHPercentage,
	                                            coordinates2D position,
	                                            HWND hWidget,
	                                            HWND mainWindow)
{
	// Get screen width and height
	size2D windowSize = getWindowSize(mainWindow);

	// Calculate wanted dimensions of the widget (in pixels)
	size2D dimensions(static_cast<int> ((wndWPercentage) / 100.0 * windowSize.x),
		static_cast<int> ((wndHPercentage) / 100.0 * windowSize.y));

	// Need to place the window relatively to the main window
	RECT wndRect;
	GetWindowRect(mainWindow, &wndRect);

	SetWindowPos(
		hWidget,
		HWND_TOP, // Z axis order
		position.x,// + wndRect.left,
		position.y,// + wndRect.top,
		dimensions.x,
		dimensions.y,
		SWP_SHOWWINDOW | SWP_DRAWFRAME);

	return dimensions;
}

/*
 * Returns the number of pixel (width and height) associated to
 * the percentage of the screen.
 */
size2D WidgetPlacer::getPercentagePixelsOfScreen(Percentage p)
{
	// Get screen width and height
	size2D screen = getScreenSize();

	// Calculate wanted dimensions of the widget (in pixels)
	return size2D(static_cast<int> (static_cast<int>(p)/100.0 * screen.x),
		          static_cast<int> (static_cast<int>(p)/100.0 * screen.y));
}

/*
* Returns the number of pixel (width and height) associated to
* the percentage of the application window.
*/
size2D WidgetPlacer::getPercentagePixelsOfWindow(Percentage p, HWND hwnd)
{
	// Get screen width and height
	size2D wndSize = getWindowSize(hwnd);

	// Calculate wanted dimensions of the widget (in pixels)
	return size2D(static_cast<int> (static_cast<int>(p) / 100.0 * wndSize.x),
		static_cast<int> (static_cast<int>(p) / 100.0 * wndSize.y));
}