#pragma once

// General type for any kind of boolean operations
enum class OpResult {
	SUCCESS,
	FAILURE
};

// General type for rectangural dimensions.
struct size2D {
	int x;
	int y;

	size2D(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	size2D operator/(int divider)
	{
		size2D ret(x/divider, y/divider);
		return ret;
	}

	size2D operator*(int divider)
	{
		size2D ret(x * divider, y * divider);
		return ret;
	}

	size2D operator+(size2D toAdd)
	{
		size2D ret(x + toAdd.x, y + toAdd.y);
		return ret;
	}

	size2D operator-(size2D toSubstr)
	{
		size2D ret(x - toSubstr.x, y - toSubstr.y);
		return ret;
	}
};

// General type for coordinates/points.
struct coordinates2D {
	int x;
	int y;

	coordinates2D(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
};