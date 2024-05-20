/***********************************************************************
 * File: IO.cpp
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
 * Description: Description
***********************************************************************/
#include "IO.h"

/**
 * Hides the console cursor.
 */
void hideCursor() {
	//Declare
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;

	//Set
	info.dwSize = 100;
	info.bVisible = FALSE;

	//Change
	SetConsoleCursorInfo(consoleHandle, &info);
}

/**
 * Shows the console cursor.
 */
void showCursor() {
	//Declare
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;

	//Set
	info.dwSize = 100;
	info.bVisible = TRUE;

	//Change
	SetConsoleCursorInfo(consoleHandle, &info);
}

/**
 * Checks if the console size meets the specified requirements.
 * \param requiredRows The required number of rows.
 * \param requiredCols The required number of columns.
 * \return True if the console size meets the requirements, false otherwise.
 */
bool checkConsoleSize(int requiredRows, int requiredCols) {
	//Declare
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	//Detect screen size
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
		int consoleRows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
		int consoleCols = csbi.srWindow.Right - csbi.srWindow.Left + 1;

		return (consoleRows >= requiredRows) && (consoleCols >= requiredCols);
	}

	return false;
}

/**
 * Moves the console cursor to the specified position.
 * \param x The x-coordinate of the position.
 * \param y The y-coordinate of the position.
 */
void gotoxy(int x, int y) {
	//Declare
	COORD coord;

	//Set
	coord.X = x;
	coord.Y = y;

	//Change
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

/**
 * Prints the contents of a file at the specified position in the console.
 * \param fileName The name of the file to print.
 * \param startX The x-coordinate of the starting position.
 * \param startY The y-coordinate of the starting position.
 */
void printFileAtPosition(const std::string& fileName, int startX, int startY) {
	//Declare
	std::ifstream file(fileName);

	//Check File
	if (!file.is_open()) {
		std::cerr << "µLªk¶}±ÒÀÉ®× " << fileName << std::endl;

		return;
	}

	// Declare
	std::string line;
	int y = startY;

	//Output
	while (std::getline(file, line)) {
		gotoxy(startX, y++);
		std::cout << line << std::endl;
	}

	//Close
	file.close();
}


/**
 * Sets the size of the console window.
 * \param width The width of the console window.
 * \param height The height of the console window.
 */
void setConsoleSize(int width, int height) {
	//Declare
	SMALL_RECT rect = { 0, 0, width - 1, height - 1 };
	COORD coord = { width, height };
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	//Set
	SetConsoleScreenBufferSize(hConsole, coord);
	SetConsoleWindowInfo(hConsole, TRUE, &rect);
}

/**
 * Sets the color of the console text.
 * \param color The color code to set.
 */
void SetColor(int color = 7)
{
	// Declare
	HANDLE hConsole;

	//Get
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	//Set Color
	SetConsoleTextAttribute(hConsole, color);
}
