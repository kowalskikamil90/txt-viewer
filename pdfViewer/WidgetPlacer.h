#pragma once

#include "misc.h"

#include <Windows.h>

class WidgetPlacer
{

public:

	static size2D getScreenSize();
	static coordinates2D getScreenCenter();
	static coordinates2D calculateCenteredWindowCoords(size2D wndSize);
	static void centerTheWindow(HWND hwnd);
	static size2D resizeAndPositonWidget(int screenWPercentage,
		                                 int screenHPercentage,
		                                 coordinates2D position,
		                                 HWND hWidget);
	static size2D getPercentagePixels(Percentage p);
};