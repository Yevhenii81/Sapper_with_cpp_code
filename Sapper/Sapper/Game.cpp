#include "Game.h"


	void Game::ResizeMap(int w, int h, int numMines)
	{
		map.width = w;
		map.height = h;
		map.InitializeMap();
		map.InitializeMask();
		cell.RandMines(numMines, map);
		map.NumberSetting();
		map.PrintMap();
	}

	void Game::StartEasyLevel()
	{
		ResizeMap(10, 10, 10);
	}

	void Game::StartMediumLevel()
	{
		ResizeMap(15, 15, 20);
	}

	void Game::StartHardLevel()
	{
		ResizeMap(20, 20, 30);
	}

	void Game::Menu()
	{
		int choice = 0;
		int totalChoices = 3; //���������� ��������� ������
		bool levelChosen = false;

		while (true)
		{
			system("cls");
			console.Options(43, 9);
			cout << "Play";
			console.Options(43, 10);
			cout << "Rules";
			console.Options(43, 11);
			cout << "Level selection";

			console.HideCursor(true);

			//����������� ������� � �������� ������
			switch (choice)
			{
			case 0:
				console.Options(37, 9);
				cout << "->";
				break;
			case 1:
				console.Options(37, 10);
				cout << "->";
				break;
			case 2:
				console.Options(37, 11);
				cout << "->";
				break;
			}

			int key = _getch();
			if (key == UP)
			{
				choice = (choice - 1 + totalChoices) % totalChoices;
			}
			else if (key == DOWN)
			{
				choice = (choice + 1) % totalChoices;
			}
			else if (key == ENTER)
			{
				if (choice == 0)
				{
					//������ ����
					if (levelChosen) {
						/*system("cls");
						console.Options(40, 9);
						cout << "Game started!" << "\n";
						Sleep(1500);
						system("cls");
						return;*/

						system("cls");
						console.Options(40, 9);
						cout << "Game started!" << "\n";
						Sleep(1000);
						console.Options(40, 12);
						cout << "Loading ";
						for (int i = 0; i < 10; i++) {
							cout << ".";
							Sleep(100);
						}
						cout << "\n";
						Sleep(500);
						system("cls");
						return;

					}
					else {
						system("cls");
						console.Options(40, 9);
						cout << "Please select a level first!" << "\n";
						console.Options(40, 11);
						Sleep(1500);
						cout << "Press any key to go back to menu..." << "\n";
						_getch();
					}
				}
				else if (choice == 1)
				{
					//����� ������
					system("cls");
					cout << "Game Rules:" << "\n";
					cout << "1. Uncover all cells except mines." << "\n";
					cout << "2. Use arrow keys to move around the map." << "\n";
					cout << "3. Press space to place a flag in a cell suspected to contain a mine." << "\n";
					cout << "4. Press enter to uncover a cell and reveal its content." << "\n";
					cout << "5. If you uncover a mine, the game is over." << "\n";
					cout << "6. Numbers on the cells indicate the number of mines adjacent to that cell." << "\n";
					cout << "7. Flag all mines correctly to win the game." << "\n";
					cout << "Press any key to go back to menu..." << "\n";
					_getch();
				}
				else if (choice == 2)
				{
					//����� ���� ������ ������
					system("cls");
					cout << "Level Selection:" << "\n";
					cout << "1. Easy (10x10, 10 mines)" << "\n";
					cout << "2. Medium (15x15, 20 mines)" << "\n";
					cout << "3. Hard (20x20, 30 mines)" << "\n";
					cout << "Enter your choice: ";

					int levelChoice;
					cin >> levelChoice;

					//��������� ������ ������
					switch (levelChoice)
					{
					case 1:
						//������ ���� � ������ �������
						StartEasyLevel();
						levelChosen = true;
						break;
					case 2:
						//������ ���� � ������� �������
						StartMediumLevel();
						levelChosen = true;
						break;
					case 3:
						//������ ���� � ������� �������
						StartHardLevel();
						levelChosen = true;
						break;
					default:
						cout << "Invalid choice. Please enter a valid option" << "\n";
						_getch();
					}
				}
			}
		}
	}

	//����� ���������
	void Game::GameOver()
	{
		console.Options(40, 9);
		cout << "Game over";
		Sleep(2000);
		console.Options(0, 20);
		system("pause");
		exit(0);
	}

	//����� �������� 
	void Game::Won()
	{
		console.Options(40, 9);
		if (map.isGameWon)
		{
			cout << "Congratulations! You won!";
		}
		else
		{
			GameOver();
		}
		Sleep(2000);
		console.Options(0, 15);
		system("pause");
	}

	//�����, ������� ��������� ����, �������������� �����, ����������� ����,
	//��������� ������ ��������� ���������� � ��������� ������� ������
	void Game::run()
	{
		console.OptionsConsole();
		console.ShowLogo();
		Menu();
		map.InitializeMap();
		map.InitializeMask();
		//cell.RandMines(8, map);
		map.NumberSetting();
		map.PrintMap();

		COORD position;
		position.X = 1;
		position.Y = 1;
		console.SetCursor(1, 1);
		console.HideCursor(false);

		bool exit = false;
		while (!exit)
		{
			int code = _getch();
			if (code == 224)
			{
				code = _getch();
			}

			int tx = position.X;
			int ty = position.Y;

			console.Options(tx, ty);
			//console.SetCursor(position.X, position.Y, BLACK, " ");

			if (code == RIGHT && map.map[position.Y][position.X + 1] != WALL)
			{
				position.X++;
			}
			else if (code == LEFT && map.map[position.Y][position.X - 1] != WALL)
			{
				position.X--;
			}
			else if (code == DOWN && map.map[position.Y + 1][position.X] != WALL)
			{
				position.Y++;
			}
			else if (code == UP && map.map[position.Y - 1][position.X] != WALL)
			{
				position.Y--;
			}
			else if (code == SPACE)
			{
				map.PlaceFlag(position.Y, position.X);
			}
			else if (code == ENTER)
			{
				int result = map.OpenCell(position.X, position.Y);
				if (result == MINE)
				{
					GameOver();
					exit = true;
				}
				if (result == HALL)
				{
					map.Fill(position.X, position.Y, map);
					map.PrintMap();
				}
			}

			console.Options(tx, ty); // ������� ���������� ������
			console.Options(position.X, position.Y); // ���������� ������
		}
	}