#pragma once

#include "misc.h"

class WindowPlacer
{

public:
	WindowPlacer();
	~WindowPlacer();

	static size2D getScreenSize();
	static coordinates2D getScreenCenter();
	static coordinates2D calculateCenteredWindowCoords(size2D wndSize);
};