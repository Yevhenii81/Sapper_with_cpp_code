#include <iostream>  //подключаем заголовочный файл для работы с вводом/выводом через стандартный поток ввода-вывода
#include <windows.h>  //подключаем заголовочный файл для работы с функциями и структурами Windows API
#include <conio.h>  //подключаем заголовочный файл для работы с функциями для работы с консольным вводом-выводом и управлением курсором
#include <ctime>  //подключаем аголовочный файл для работы с функциями для работы с временем и датой
#include <vector>  //подключаем заголовочный файл для работы с динамическими массивами и стандартными контейнерами вектор
#include <locale>  //подключаем заголовочный файл для работы с локализацией и локальными функциями
#include <string>  //подключаем заголовочный файл для работы со строками
#include <stack>  //подключаем заголовочный файл для работый с контейнером стек
using namespace std;  //используем пространство имен std

#include "Console.h"
#include "Map.h"
#include "Cell.h"
#include "Game.h"

//Игра Сапёр
//В этой игре есть такие классы как: Map(игровое поле), Game(Игра), Console(настройка консоли), Cell(клетка)

//enum NumberColor {BLUE = 1, GREEN = 2, RED = 3, DARKBLUE = 4, BROWN = 5, TURQUOISE = 6, BLACK = 7, WHITE = 8}; //раскрас игровых цифр
//enum KeyCode {ENTER = 13, SPACE = 32,LEFT = 75, RIGHT = 77, DOWN = 80, UP = 72 }; //управление клавиатурой
//enum SapperObject {WALL = 100, HALL = 0, MINE = 10}; //

//класс для работы с консолью
//class Console
//{
//public:
//	//метод для установки позиции курсора на экране
//	void Options(int x, int y)
//	{
//		COORD p = { x, y };
//		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
//	}
//
//	//метод, который выводит логотип игры и просит нажать ENTER чтобы начать игру
//	void ShowLogo()
//	{
//		CONSOLE_SCREEN_BUFFER_INFO csbi;
//		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
//		int widthConsole = csbi.dwSize.X;
//
//		int x = (widthConsole - 6) / 2; // Центрируем текст "Sapper"
//		int y = 9;
//
//		//не забыть разкоментировать
//		//логотип игры
//		Options(x, y);
//		cout << "Sapper" << "\n";
//		Options(40, 12);
//		cout << "Please, press ENTER to start ";
//		while (_getch() != ENTER);
//		system("cls");
//	}
//
//	//метод, который скрывает курсор
//	void HideCursor(bool vision)
//	{
//		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
//		CONSOLE_CURSOR_INFO info;
//		info.bVisible = !vision;
//		info.dwSize = 100;
//		SetConsoleCursorInfo(h, &info);
//	}
//
//	//метод, который настравивает курсор
//	//void SetCursor(int x, int y, int color, string text) 
//	//{
//	//	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
//	//	COORD position;
//	//	position.X = x; // настройка конкретных координат
//	//	position.Y = y;
//	//	SetConsoleCursorPosition(h, position); // установка курсора в заданную точку
//	//	SetConsoleTextAttribute(h, color); // смена цвета
//	//	cout << text; // вывод строки текста
//	//	cout << "\n";
//	//}
//
//	void SetCursor(int x, int y)
//	{
//		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
//		COORD position;
//		position.X = x; // Настройка координат X
//		position.Y = y; // Настройка координат Y
//		SetConsoleCursorPosition(h, position); // Установка курсора в заданную точку
//	}
//
//	//метод для настройки параметров консоли (размер окна, название окна)
//	void OptionsConsole()
//	{
//		HWND hwnd = GetConsoleWindow();
//
//		int screen_width = GetSystemMetrics(SM_CXSCREEN);
//		int screen_height = GetSystemMetrics(SM_CYSCREEN);
//
//		int window_width = 1360;
//		int window_height = 768;
//
//		MoveWindow(hwnd,
//			(screen_width - window_width) / 2,
//			(screen_height - window_height) / 2,
//			window_width,
//			window_height,
//			1);
//		system("title Sapper");
//	}
//};

//класс для работы с игровым полем
//class Map : public Console
//{
//private:
//	/*int width = 10;
//	int height = 10;*/
//	int width;
//	int height;
//	friend class Cell;
//	friend class Game;
//
//	bool isGameWon;  //переменная для отслеживания выиграша
//	vector<vector<int>> map;  //двумерный вектор для игрового поля
//	vector<vector<int>> mask;  //двумерный вектор для маски игрового поля
//	HANDLE h;  //дескриптор для работы с консолью
//public:
//	/*Map(int w, int h) : width(w), height(h), h(GetStdHandle(STD_OUTPUT_HANDLE))
//	{
//		InitializeMap();
//		InitializeMask();
//	}*/
//
//	Map() : width(0), height(0), isGameWon(false), h(GetStdHandle(STD_OUTPUT_HANDLE)) {}
//
//	void setWidth(int w) { width = w; }
//	int getWidth() const { return width; }
//
//	void setHeight(int h) { height = h; }
//	int getHeight() const { return height; }
//
//	void setIsGameWon(bool value) { isGameWon = value; }
//	bool getIsGameWon() const { return isGameWon; }
//
//	void setMap(const vector<vector<int>>& newMap) { map = newMap; }
//	vector<vector<int>> getMap() const { return map; }
//
//	void setMask(const vector<vector<int>>& newMask) { mask = newMask; }
//	vector<vector<int>> getMask() const { return mask; }
//
//	void setHandle(HANDLE newHandle) { h = newHandle; }
//	HANDLE getHandle() const { return h; }
//
//	//метод для инициализации игрового поля
//	void InitializeMap()
//	{
//		for (int i = 0; i < width; i++)
//		{
//			vector<int> temp;
//			for (int j = 0; j < height; j++)
//			{
//				if (i == 0 || j == 0 || i == width - 1 || j == height - 1)
//				{
//					temp.push_back(WALL);
//				}
//				else
//				{
//					temp.push_back(HALL);
//				}
//			}
//			map.push_back(temp);
//		}
//	}
//
//	//метод для отображения игрового поля
//	void PrintMap()
//	{
//		Options(0, 0);
//		for (int i = 0; i < width; i++)
//		{
//			for (int j = 0; j < height; j++)
//			{
//				if (mask[j][i] == HALL)
//				{
//					//SetConsoleTextAttribute(h, BLACK);
//					cout << "."; //маска
//					continue;
//				}
//
//				if (map[j][i] == WALL)
//				{
//					SetConsoleTextAttribute(h, WHITE);
//					cout << (char)178; // стена
//				}
//				else if (mask[j][i] == 2)
//				{
//					cout << "!"; //флаг
//				}
//				else if (map[j][i] == HALL)
//				{
//					SetConsoleTextAttribute(h, BLACK);
//					cout << " "; // коридор
//				}
//				else if (map[j][i] == MINE)
//				{
//					SetConsoleTextAttribute(h, GREEN);
//					cout << "*"; //мина
//				}
//				else 
//				{
//					SetConsoleTextAttribute(h, BLACK);
//					SetConsoleTextAttribute(h, WHITE);
//					cout << map[j][i];
//				}
//			}
//			cout << "\n";
//		}
//	}
//
//	//метод для расстановки чисел на игровом поле
//	void NumberSetting()
//	{
//		for (int i = 1; i < width - 1; i++)
//		{
//			for (int j = 1; j < height - 1; j++)
//			{
//				if (map[i][j] != MINE)
//				{
//					int count = 0;
//					if (map[i - 1][j - 1] == MINE) count++;
//					if (map[i - 1][j] == MINE) count++;
//					if (map[i - 1][j + 1] == MINE) count++;
//					if (map[i][j - 1] == MINE) count++;
//					if (map[i][j + 1] == MINE) count++;
//					if (map[i + 1][j - 1] == MINE) count++;
//					if (map[i + 1][j] == MINE) count++;
//					if (map[i + 1][j + 1] == MINE) count++;
//					map[i][j] = count;
//				}
//			}
//		}
//	}
//
//	//метод для инициализации маски (состояние ячеек)
//	void InitializeMask()
//	{
//		for (int i = 0; i < width; i++)
//		{
//			vector<int> temp;
//			for (int j = 0; j < height; j++)
//			{
//				if (i == 0 || j == 0 || i == width - 1 || j == height - 1)
//				{
//					temp.push_back(WALL);
//				}
//				else
//				{
//					temp.push_back(HALL);
//				}
//			}
//			mask.push_back(temp);
//		}
//	}
//
//	//метод для открытия ячейки и обновления маски
//	int OpenCell(int x, int y)
//	{
//		if (mask[x][y] == HALL)
//		{
//			mask[x][y] = 1;
//
//			if (map[x][y] == MINE)
//			{
//				SetConsoleTextAttribute(h, GREEN);
//				cout << "*";
//				return MINE;
//			}
//			else if (map[x][y] == HALL)
//			{
//				Fill(x, y, *this);
//				return HALL;
//			}
//			else
//			{
//				SetConsoleTextAttribute(h, BLACK);
//				SetConsoleTextAttribute(h, WHITE);
//				cout << map[x][y];
//				return map[x][y];
//			}
//		}
//		if (CheckGameWon())
//		{
//			isGameWon = true;
//			return -2;
//		}
//		return -1;
//	}
//
//	//метод для проверки выиграша в игре
//	bool CheckGameWon()
//	{
//		for (int i = 1; i < width - 1; i++)
//		{
//			for (int j = 1; j < height - 1; j++)
//			{
//				if (map[i][j] != MINE && mask[i][j] != 1) {
//					return false; //если есть незамаскированные ячейки, игра не выиграна
//				}
//			}
//		}
//		return true; //все незамаскированные ячейки без мин, игра выиграна
//	}
//
//	//метод для заливки пустой области на игровом поле
//	//используется стек для хранения координат ячеек для заливки
//	//обновляем маску поля и отображаем изменения на экране
//	void Fill(int px, int py, Map& map)
//	{
//		stack<int> stk;
//		stk.push(px);
//		stk.push(py);
//
//		int x = 0;
//		int y = 0;
//		while (!stk.empty())
//		{
//			y = stk.top();
//			stk.pop();
//
//			x = stk.top();
//			stk.pop();
//
//			if (map.map[x][y + 1] == HALL && map.mask[x][y + 1] == 0)
//			{
//				stk.push(x);
//				stk.push(y + 1);
//			}
//			map.mask[x][y + 1] = 1;
//
//			if (map.map[x][y - 1] == HALL && map.mask[x][y - 1] == 0)
//			{
//				stk.push(x);
//				stk.push(y - 1);
//			}
//			map.mask[x][y - 1] = 1;
//
//			if (map.map[x + 1][y + 1] == HALL && map.mask[x + 1][y + 1] == 0)
//			{
//				stk.push(x + 1);
//				stk.push(y + 1);
//			}
//			map.mask[x + 1][y + 1] = 1;
//
//			if (map.map[x + 1][y - 1] == HALL && map.mask[x + 1][y - 1] == 0)
//			{
//				stk.push(x + 1);
//				stk.push(y - 1);
//			}
//			map.mask[x + 1][y - 1] = 1;
//
//			if (map.map[x - 1][y + 1] == HALL && map.mask[x - 1][y + 1] == 0)
//			{
//				stk.push(x - 1);
//				stk.push(y + 1);
//			}
//			map.mask[x - 1][y + 1] = 1;
//
//			if (map.map[x - 1][y - 1] == HALL && map.mask[x - 1][y - 1] == 0)
//			{
//				stk.push(x - 1);
//				stk.push(y - 1);
//			}
//			map.mask[x - 1][y - 1] = 1;
//
//			if (map.map[x - 1][y] == HALL && map.mask[x - 1][y] == 0)
//			{
//				stk.push(x - 1);
//				stk.push(y);
//			}
//			map.mask[x - 1][y] = 1;
//
//			if (map.map[x + 1][y] == HALL && map.mask[x + 1][y] == 0)
//			{
//				stk.push(x + 1);
//				stk.push(y);
//			}
//			map.mask[x + 1][y] = 1;
//
//			if (stk.empty())
//			{
//				break;
//			}
//		}
//		PrintMap(); //распечатка обновленной карты
//	}
//
//	// метод для установки флага на игровом поле
//	void PlaceFlag(int x, int y)
//	{
//		if (mask[y][x] == HALL) //проверяем, что ячейка еще не открыта
//		{
//			mask[y][x] = 2; //устанавливаем флаг
//			PrintMap(); //обновляем экран после установки флага
//		}
//		else if (mask[y][x] == 2) //если в ячейке уже установлен флаг
//		{
//			mask[y][x] = HALL; //убираем флаг, восстанавливаем маску
//			PrintMap(); //обновляем экран после удаления флага
//		}
//	}
//};

//class Cell
//{
//private:
//	bool isMine;
//	bool isRevealed;
//	int adjacentMines;
//public:
//	Cell() : isMine(false), isRevealed(false), adjacentMines(0) {}
//
//	//метод, который рандомно расставляет мины
//	void RandMines(int numMines, Map& map)
//	{
//		//проверка на количество мин, которые можно установить на поле
//		if (numMines >= (map.width - 2) * (map.width - 2))
//		{
//			MessageBoxA(0, "Слишком много мин!", "Попробуйте заново!", MB_OK);
//			return;
//		}
//		for (int i = 0; i < numMines; i++)
//		{
//			int x = 0;
//			int y = 0;
//			//поиск пустой ячейки, не занятой миной
//			do
//			{
//				x = rand() % (map.width - 2) + 1;
//				y = rand() % (map.height - 2) + 1;
//			} while (map.map[x][y] == MINE);
//			map.map[x][y] = MINE;
//		}
//	}
//};

//класс отвечающий за управление игровым процессом и логикой игры

//class Game
//{
//public:
//	Map map;
//	Cell cell;
//	Console console;
//	
//	void ResizeMap(int w, int h, int numMines)
//	{
//		map.width = w;
//		map.height = h;
//		map.InitializeMap();
//		map.InitializeMask();
//		cell.RandMines(numMines, map);
//		map.NumberSetting();
//		map.PrintMap();
//	}
//
//	void StartEasyLevel()
//	{
//		ResizeMap(10, 10, 10);
//	}
//
//	void StartMediumLevel()
//	{
//		ResizeMap(15, 15, 20);
//	}
//
//	void StartHardLevel()
//	{
//		ResizeMap(20, 20, 30);
//	}
//
//	void Menu()
//	{
//		int choice = 0;
//		int totalChoices = 3; //количество вариантов выбора
//		bool levelChosen = false; 
//		
//		while (true)
//		{
//			system("cls");
//			console.Options(43, 9);
//			cout << "Play";
//			console.Options(43, 10);
//			cout << "Rules";
//			console.Options(43, 11);
//			cout << "Level selection";
//
//			console.HideCursor(true);
//
//			//отображение стрелки у текущего выбора
//			switch (choice)
//			{
//			case 0:
//				console.Options(37, 9);
//				cout << "->";
//				break;
//			case 1:
//				console.Options(37, 10);
//				cout << "->";
//				break;
//			case 2:
//				console.Options(37, 11);
//				cout << "->";
//				break;
//			}
//
//			int key = _getch();
//			if (key == UP)
//			{
//				choice = (choice - 1 + totalChoices) % totalChoices;
//			}
//			else if (key == DOWN)
//			{
//				choice = (choice + 1) % totalChoices;
//			}
//			else if (key == ENTER)
//			{
//				if (choice == 0)
//				{
//					//запуск игры
//					if (levelChosen) {
//						/*system("cls");
//						console.Options(40, 9);
//						cout << "Game started!" << "\n";
//						Sleep(1500);
//						system("cls");
//						return;*/
//
//						system("cls");
//						console.Options(40, 9);
//						cout << "Game started!" << "\n";
//						Sleep(1000);
//						console.Options(40, 12);
//						cout << "Loading ";
//						for (int i = 0; i < 10; i++) {
//							cout << ".";
//							Sleep(100);
//						}
//						cout << "\n";
//						Sleep(500);
//						system("cls");
//						return;
//
//					}
//					else {
//						system("cls");
//						console.Options(40, 9);
//						cout << "Please select a level first!" << "\n";
//						console.Options(40, 11);
//						Sleep(1500);
//						cout << "Press any key to go back to menu..." << "\n";
//						_getch();
//					}
//				}
//				else if (choice == 1)
//				{
//					//показ правил
//					system("cls");
//					cout << "Game Rules:" << "\n";
//					cout << "1. Uncover all cells except mines." << "\n";
//					cout << "2. Use arrow keys to move around the map." << "\n";
//					cout << "3. Press space to place a flag in a cell suspected to contain a mine." << "\n";
//					cout << "4. Press enter to uncover a cell and reveal its content." << "\n";
//					cout << "5. If you uncover a mine, the game is over." << "\n";
//					cout << "6. Numbers on the cells indicate the number of mines adjacent to that cell." << "\n";
//					cout << "7. Flag all mines correctly to win the game." << "\n";
//					cout << "Press any key to go back to menu..." << "\n";
//					_getch();
//				}
//				else if (choice == 2)
//				{
//					//показ меню выбора уровня
//					system("cls");
//					cout << "Level Selection:" << "\n";
//					cout << "1. Easy (10x10, 10 mines)" << "\n";
//					cout << "2. Medium (15x15, 20 mines)" << "\n";
//					cout << "3. Hard (20x20, 30 mines)" << "\n";
//					cout << "Enter your choice: ";
//
//					int levelChoice;
//					cin >> levelChoice;
//
//					//обработка выбора уровня
//					switch (levelChoice)
//					{
//					case 1:
//						//запуск игры с легким уровнем
//						StartEasyLevel();
//						levelChosen = true;
//						break;
//					case 2:
//						//запуск игры с средним уровнем
//						StartMediumLevel();
//						levelChosen = true;
//						break;
//					case 3:
//						//запуск игры с тяжелым уровнем
//						StartHardLevel();
//						levelChosen = true;
//						break;
//					default:
//						cout << "Invalid choice. Please enter a valid option" << "\n";
//						_getch();
//					}
//				}
//			}
//		}
//	}
//
//	//метод проиграша
//	void GameOver()
//	{
//		console.Options(40, 9);
//		cout << "Game over";
//		Sleep(2000);
//		console.Options(0, 20);
//		system("pause");
//		exit(0);
//	}
//
//	//метод выиграша 
//	void Won()
//	{
//		console.Options(40, 9);
//		if (map.isGameWon) 
//		{
//			cout << "Congratulations! You won!";
//		}
//		else 
//		{
//			GameOver();
//		}
//		Sleep(2000);
//		console.Options(0, 15);
//		system("pause");
//	}
//
//	//метод, который запускает игру, инициализирует карту, расставляет мины,
//	//позволяет игроку управлять персонажем и выполняет игровую логику
//	void run()
//	{
//		console.OptionsConsole();
//		console.ShowLogo();
//		Menu();
//		map.InitializeMap();
//		map.InitializeMask();
//		//cell.RandMines(8, map);
//		map.NumberSetting();
//		map.PrintMap();		
//
//		COORD position;
//		position.X = 1;
//		position.Y = 1;
//		console.SetCursor(1, 1);
//		console.HideCursor(false);
//
//		bool exit = false;
//		while (!exit)
//		{
//			int code = _getch();
//			if (code == 224)
//			{
//				code = _getch();
//			}
//
//			int tx = position.X;
//			int ty = position.Y;
//
//			console.Options(tx, ty);
//			//console.SetCursor(position.X, position.Y, BLACK, " ");
//
//			if (code == RIGHT && map.map[position.Y][position.X + 1] != WALL)
//			{
//				position.X++;
//			}
//			else if (code == LEFT && map.map[position.Y][position.X - 1] != WALL)
//			{
//				position.X--;
//			}
//			else if (code == DOWN && map.map[position.Y + 1][position.X] != WALL)
//			{
//				position.Y++;
//			}
//			else if (code == UP && map.map[position.Y - 1][position.X] != WALL)
//			{
//				position.Y--;
//			}
//			else if (code == SPACE)
//			{
//				map.PlaceFlag(position.Y, position.X);
//			}
//			else if (code == ENTER)
//			{
//				int result = map.OpenCell(position.X, position.Y);
//				if (result == MINE)
//				{
//					GameOver();
//					exit = true;
//				}
//				if (result == HALL)
//				{
//					map.Fill(position.X, position.Y, map);
//					map.PrintMap();
//				}
//			}
//
//			console.Options(tx, ty); // Убираем предыдущий курсор
//			console.Options(position.X, position.Y); // Перемещаем курсор
//		}
//	}
//};

int main()
{
	srand(time(NULL));
	
	Game game;
	game.run();
}