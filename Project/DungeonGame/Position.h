#pragma once
#include <iostream>
class Position {
public:
	int x, y;

	Position() : x(0), y(0) {}
	Position(int x, int y) : x(x), y(y) {}
	Position(const Position& ref) { *this = ref; }

	// Operator overloading
	Position operator+(const Position& rhs) const {
		return Position(x + rhs.x, y + rhs.y);
	}
	Position& operator+=(const Position& rhs) {
		x += rhs.x;
		y += rhs.y;
		return *this;
	}
	Position operator-(const Position& rhs) const {
		return Position(x - rhs.x, y - rhs.y);
	}
	Position& operator-=(const Position& rhs) {
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}
	Position operator*(int scale) const {
		return Position(x * scale, y * scale);
	}
	bool operator==(const Position& rhs) const {
		return x == rhs.x && y == rhs.y;
	}
	bool operator!=(const Position& rhs) const {
		return !(*this == rhs);
	}

	friend std::ostream& operator<<(std::ostream& strm, const Position& c) //output
	{
		strm << c.x << " " << c.y;
		return strm;
	}

	friend std::istream& operator>>(std::istream& strm, Position& c) // input
	{
		strm >> c.x >> c.y;
		return strm;
	}
};