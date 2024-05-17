#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>

void hideCursor();

void showCursor();

bool checkConsoleSize(int requiredRows, int requiredCols);
// ©w¸q gotoxy ¨ç¦¡
void gotoxy(int x, int y);

void printFileAtPosition(const std::string& fileName, int startX, int startY);

void setConsoleSize(int width, int height);

void SetColor(int color);
