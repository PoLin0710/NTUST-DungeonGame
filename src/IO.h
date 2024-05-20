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
 * Description: Description
***********************************************************************/

#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>

void hideCursor();

void showCursor();

bool checkConsoleSize(int requiredRows, int requiredCols);

void gotoxy(int x, int y);

void printFileAtPosition(const std::string& fileName, int startX, int startY);

void setConsoleSize(int width, int height);

void SetColor(int color);
