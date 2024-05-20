/***********************************************************************
 * File: Position.h
 * Author:
 *        B11215040 HUANG,PO-LIN (oliver590617@gmail.com)
 *        B11215030 SONG,BING-YU (yehyi817@gmail.com)
 *        B11215014 ¤ýà±´¸ (sunnyching901105@gmail.com)
 *        B11215008 ¬x§B¿o (n590762743@gmail.com)
 * Create Date: 2024-05-20
 * Editor:
 *        B11215040 HUANG,PO-LIN (oliver590617@gmail.com)
 *        B11215030 SONG,BING-YU (yehyi817@gmail.com)
 *        B11215014 ¤ýà±´¸ (sunnyching901105@gmail.com)
 *        B11215008 ¬x§B¿o (n590762743@gmail.com)
 * Update Date: 2024-05-20
 * Description: This file defines a Position class representing a two-dimensional point with x and y coordinates.
 *				It provides basic arithmetic operations such as addition, subtraction, and scalar multiplication, as well as comparison operations for equality and inequality.
 *				Additionally, it overloads input and output operators for easy input and output of Position objects.
***********************************************************************/
#pragma once
#include <iostream>
class Position {
public:
	int x, y;

	// Constructors
	Position() : x(0), y(0) {}
	Position(int x, int y) : x(x), y(y) {}
	Position(const Position& ref) { *this = ref; }

	// Operator overloading
	Position operator+(const Position& rhs) const {
		//add
		return Position(x + rhs.x, y + rhs.y);
	}

	//Operator +=
	Position& operator+=(const Position& rhs) {
		//cal
		x += rhs.x;
		y += rhs.y;

		//return
		return *this;
	}

	//Operator -
	Position operator-(const Position& rhs) const {
		//cal
		return Position(x - rhs.x, y - rhs.y);
	}

	//Operator -=
	Position& operator-=(const Position& rhs) {
		//cal
		x -= rhs.x;
		y -= rhs.y;

		//return
		return *this;
	}

	//Operator *
	Position operator*(int scale) const {
		//cal
		return Position(x * scale, y * scale);
	}

	//Operator ==
	bool operator==(const Position& rhs) const {
		//return isSame
		return x == rhs.x && y == rhs.y;
	}

	//Operator !=
	bool operator!=(const Position& rhs) const {
		//return isNotSame
		return !(*this == rhs);
	}

	/**
	 * Intent: Overloads the output operator for easy printing of Position objects.
	 * Pre: Requires a valid output stream (strm) and a Position object (c).
	 * Post: Prints the x and y coordinates of the Position object to the output stream.
	 * \param strm: The output stream to which the Position object will be printed.
	 * \param c: The Position object to be printed.
	 * \return Returns the output stream after printing.
	 */
	friend std::ostream& operator<<(std::ostream& strm, const Position& c) //output
	{
		strm << c.x << " " << c.y;
		return strm;
	}

	/**
	* Intent: Overloads the input operator for easy input of Position objects.
	* Pre: Requires a valid input stream (strm) and a Position object (c).
	* Post: Reads the x and y coordinates from the input stream into the Position object.
	* \param strm: The input stream from which the Position object will be read.
	* \param c: The Position object to store the input coordinates.
	* \return Returns the input stream after reading.
	*/
	friend std::istream& operator>>(std::istream& strm, Position& c) // input
	{
		strm >> c.x >> c.y;
		return strm;
	}
};