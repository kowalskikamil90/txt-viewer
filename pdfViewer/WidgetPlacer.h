#pragma once

#include "misc.h"

#include <Windows.h>

/*
 * This class acts as a primitive layout manager.
 * It enables to place widgets in a relatively simple way,
 * in reference to both screen and window.
 */
class WidgetPlacer
{

public:

	static size2D getScreenSize();
	static size2D getWindowSize(HWND hwnd);
	static coordinates2D getScreenCenter();
	static coordinates2D getWindowCenter(HWND hwnd);
	static coordinates2D calculateCenteredWindowCoords(size2D wndSize);
	static void centerTheWindow(HWND hwnd);
	static size2D getPercentagePixelsOfScreen(Percentage p);
	static size2D getPercentagePixelsOfWindow(Percentage p, HWND hwnd);
	static size2D resizeAndPositonWidget(
		int screenWPercentage,
		int screenHPercentage,
		coordinates2D position,
		HWND hWidget);
	static size2D resizeAndPositonWidgetInWnd(
		int screenWPercentage,
		int screenHPercentage,
		coordinates2D position,
		HWND hWidget,
		HWND mainWindow);
};