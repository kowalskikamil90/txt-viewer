#include "stdafx.h"

#include <Windows.h>

#include "WindowPlacer.h"


WindowPlacer::WindowPlacer()
{
}

WindowPlacer::~WindowPlacer()
{
}

size2D WindowPlacer::getScreenSize()
{
	size2D screenSize(GetSystemMetrics(SM_CXSCREEN),
		              GetSystemMetrics(SM_CYSCREEN));
	return screenSize;
}

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