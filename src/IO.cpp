#include "IO.h"

void hideCursor() {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

// 函數來顯示光標
void showCursor() {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = TRUE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

bool checkConsoleSize(int requiredRows, int requiredCols) {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
		int consoleRows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
		int consoleCols = csbi.srWindow.Right - csbi.srWindow.Left + 1;
		return (consoleRows >= requiredRows) && (consoleCols >= requiredCols);
	}
	return false;
}
// 定義 gotoxy 函式
void gotoxy(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void printFileAtPosition(const std::string& fileName, int startX, int startY) {
	std::ifstream file(fileName);

	if (!file.is_open()) {
		std::cerr << "無法開啟檔案 " << fileName << std::endl;
		return;
	}

	std::string line;
	int y = startY;

	while (std::getline(file, line)) {
		gotoxy(startX, y++);
		std::cout << line << std::endl;
	}

	file.close();
}

void setConsoleSize(int width, int height) {
	SMALL_RECT rect = { 0, 0, width - 1, height - 1 };
	COORD coord = { width, height };

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleScreenBufferSize(hConsole, coord);
	SetConsoleWindowInfo(hConsole, TRUE, &rect);
}

void SetColor(int color = 7)
{
	// Declare
	HANDLE hConsole;

	//Get
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	//Set Color
	SetConsoleTextAttribute(hConsole, color);
}
