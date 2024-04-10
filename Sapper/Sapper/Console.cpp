#include "Console.h"

	//����� ��� ��������� ������� ������� �� ������
	void Console::Options(int x, int y)
	{
		COORD p = { x, y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
	}

	//�����, ������� ������� ������� ���� � ������ ������ ENTER ����� ������ ����
	void Console::ShowLogo()
	{
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
		int widthConsole = csbi.dwSize.X;

		int x = (widthConsole - 6) / 2; // ���������� ����� "Sapper"
		int y = 9;

		//�� ������ ����������������
		//������� ����
		Options(x, y);
		cout << "Sapper" << "\n";
		Options(40, 12);
		cout << "Please, press ENTER to start ";
		while (_getch() != ENTER);
		system("cls");
	}

	//�����, ������� �������� ������
	void Console::HideCursor(bool vision)
	{
		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_CURSOR_INFO info;
		info.bVisible = !vision;
		info.dwSize = 100;
		SetConsoleCursorInfo(h, &info);
	}

	void Console::SetCursor(int x, int y)
	{
		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD position;
		position.X = x; // ��������� ��������� X
		position.Y = y; // ��������� ��������� Y
		SetConsoleCursorPosition(h, position); // ��������� ������� � �������� �����
	}

	//����� ��� ��������� ���������� ������� (������ ����, �������� ����)
	void Console::OptionsConsole()
	{
		HWND hwnd = GetConsoleWindow();

		int screen_width = GetSystemMetrics(SM_CXSCREEN);
		int screen_height = GetSystemMetrics(SM_CYSCREEN);

		int window_width = 1360;
		int window_height = 768;

		MoveWindow(hwnd,
			(screen_width - window_width) / 2,
			(screen_height - window_height) / 2,
			window_width,
			window_height,
			1);
		system("title Sapper");
	}