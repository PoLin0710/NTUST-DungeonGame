/***********************************************************************
 * File: IO.h
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
 * Description: for Declare Input and Output
***********************************************************************/

#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>

/**
 * Hides the console cursor.
 */
void hideCursor();

/**
 * Shows the console cursor.
 */
void showCursor();

/**
 * Checks if the console size meets the specified requirements.
 * \param requiredRows The required number of rows.
 * \param requiredCols The required number of columns.
 * \return True if the console size meets the requirements, false otherwise.
 */
bool checkConsoleSize(int requiredRows, int requiredCols);

/**
 * Moves the console cursor to the specified position.
 * \param x The x-coordinate of the position.
 * \param y The y-coordinate of the position.
 */
void gotoxy(int x, int y);

/**
 * Prints the contents of a file at the specified position in the console.
 * \param fileName The name of the file to print.
 * \param startX The x-coordinate of the starting position.
 * \param startY The y-coordinate of the starting position.
 */
void printFileAtPosition(const std::string& fileName, int startX, int startY);

/**
 * Sets the size of the console window.
 * \param width The width of the console window.
 * \param height The height of the console window.
 */
void setConsoleSize(int width, int height);

/**
 * Sets the color of the console text.
 * \param color The color code to set.
 */
void SetColor(int color);
