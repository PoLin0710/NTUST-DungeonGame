#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>

bool checkConsoleSize(int requiredRows, int requiredCols);
// �w�q gotoxy �禡
void gotoxy(int x, int y);

void printFileAtPosition(const std::string& fileName, int startX, int startY);

void setConsoleSize(int width, int height);

void SetColor(int color);
