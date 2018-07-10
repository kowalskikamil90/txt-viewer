#pragma once

// Types for defining file format to be read
enum class FileFormat
{
	TXT,
	PDF,
	UNDEFINED
};

// General type for any kind of boolean operations
enum class OpResult
{
	SUCCESS,
	FAILURE,
	QUIT
};

// Type for expressing the percentage of generaly anything
enum class Percentage
{
	_1 = 1,
	_2 = 2,
	_3 = 3,
	_5 = 5,
	_10 = 10,
	_11 = 11,
	_12 = 12,
	_75 = 75,
	_98 = 98
	// Add more values when needed
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

	coordinates2D operator+(size2D toAdd)
	{
		return coordinates2D(this->x + toAdd.x, this->y + toAdd.y);
	}

	coordinates2D addX(size2D toAdd)
	{
		return coordinates2D(this->x + toAdd.x, this->y);
	}

	coordinates2D addY(size2D toAdd)
	{
		return coordinates2D(this->x, this->y + toAdd.y);
	}
};