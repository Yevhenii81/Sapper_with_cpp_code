#include "Map.h"


	Map::Map() : width(0), height(0), isGameWon(false), h(GetStdHandle(STD_OUTPUT_HANDLE)) {}

	void Map::setWidth(int w) { width = w; }
	int Map::getWidth() const { return width; }

	void Map::setHeight(int h) { height = h; }
	int Map::getHeight() const { return height; }

	void Map::setIsGameWon(bool value) { isGameWon = value; }
	bool Map::getIsGameWon() const { return isGameWon; }

	void Map::setMap(const std::vector<std::vector<int>>& newMap) { map = newMap; }
	std::vector<std::vector<int>> Map::getMap() const { return map; }

	void Map::setMask(const std::vector<std::vector<int>>& newMask) { mask = newMask; }
	std::vector<std::vector<int>> Map::getMask() const { return mask; }

	void Map::setHandle(HANDLE newHandle) { h = newHandle; }
	HANDLE Map::getHandle() const { return h; }

	//����� ��� ������������� �������� ����
	void Map::InitializeMap()
	{
		for (int i = 0; i < width; i++)
		{
			vector<int> temp;
			for (int j = 0; j < height; j++)
			{
				if (i == 0 || j == 0 || i == width - 1 || j == height - 1)
				{
					temp.push_back(WALL);
				}
				else
				{
					temp.push_back(HALL);
				}
			}
			map.push_back(temp);
		}
	}

	//����� ��� ����������� �������� ����
	void Map::PrintMap()
	{
		Options(0, 0);
		for (int i = 0; i < width; i++)
		{
			for (int j = 0; j < height; j++)
			{
				if (mask[j][i] == HALL)
				{
					//SetConsoleTextAttribute(h, BLACK);
					cout << "."; //�����
					continue;
				}

				if (map[j][i] == WALL)
				{
					SetConsoleTextAttribute(h, WHITE);
					cout << (char)178; // �����
				}
				else if (mask[j][i] == 2)
				{
					cout << "!"; //����
				}
				else if (map[j][i] == HALL)
				{
					SetConsoleTextAttribute(h, BLACK);
					cout << " "; // �������
				}
				else if (map[j][i] == MINE)
				{
					SetConsoleTextAttribute(h, GREEN);
					cout << "*"; //����
				}
				else
				{
					SetConsoleTextAttribute(h, BLACK);
					SetConsoleTextAttribute(h, WHITE);
					cout << map[j][i];
				}
			}
			cout << "\n";
		}
	}

	//����� ��� ����������� ����� �� ������� ����
	void Map::NumberSetting()
	{
		for (int i = 1; i < width - 1; i++)
		{
			for (int j = 1; j < height - 1; j++)
			{
				if (map[i][j] != MINE)
				{
					int count = 0;
					if (map[i - 1][j - 1] == MINE) count++;
					if (map[i - 1][j] == MINE) count++;
					if (map[i - 1][j + 1] == MINE) count++;
					if (map[i][j - 1] == MINE) count++;
					if (map[i][j + 1] == MINE) count++;
					if (map[i + 1][j - 1] == MINE) count++;
					if (map[i + 1][j] == MINE) count++;
					if (map[i + 1][j + 1] == MINE) count++;
					map[i][j] = count;
				}
			}
		}
	}

	//����� ��� ������������� ����� (��������� �����)
	void Map::InitializeMask()
	{
		for (int i = 0; i < width; i++)
		{
			vector<int> temp;
			for (int j = 0; j < height; j++)
			{
				if (i == 0 || j == 0 || i == width - 1 || j == height - 1)
				{
					temp.push_back(WALL);
				}
				else
				{
					temp.push_back(HALL);
				}
			}
			mask.push_back(temp);
		}
	}

	//����� ��� �������� ������ � ���������� �����
	int Map::OpenCell(int x, int y)
	{
		if (mask[x][y] == HALL)
		{
			mask[x][y] = 1;

			if (map[x][y] == MINE)
			{
				SetConsoleTextAttribute(h, GREEN);
				cout << "*";
				return MINE;
			}
			else if (map[x][y] == HALL)
			{
				Fill(x, y, *this);
				return HALL;
			}
			else
			{
				SetConsoleTextAttribute(h, BLACK);
				SetConsoleTextAttribute(h, WHITE);
				cout << map[x][y];
				return map[x][y];
			}
		}
		if (CheckGameWon())
		{
			isGameWon = true;
			return -2;
		}
		return -1;
	}

	//����� ��� �������� �������� � ����
	bool Map::CheckGameWon()
	{
		for (int i = 1; i < width - 1; i++)
		{
			for (int j = 1; j < height - 1; j++)
			{
				if (map[i][j] != MINE && mask[i][j] != 1) {
					return false; //���� ���� ����������������� ������, ���� �� ��������
				}
			}
		}
		return true; //��� ����������������� ������ ��� ���, ���� ��������
	}

	//����� ��� ������� ������ ������� �� ������� ����
	//������������ ���� ��� �������� ��������� ����� ��� �������
	//��������� ����� ���� � ���������� ��������� �� ������
	void Map::Fill(int px, int py, Map& map)
	{
		stack<int> stk;
		stk.push(px);
		stk.push(py);

		int x = 0;
		int y = 0;
		while (!stk.empty())
		{
			y = stk.top();
			stk.pop();

			x = stk.top();
			stk.pop();

			if (map.map[x][y + 1] == HALL && map.mask[x][y + 1] == 0)
			{
				stk.push(x);
				stk.push(y + 1);
			}
			map.mask[x][y + 1] = 1;

			if (map.map[x][y - 1] == HALL && map.mask[x][y - 1] == 0)
			{
				stk.push(x);
				stk.push(y - 1);
			}
			map.mask[x][y - 1] = 1;

			if (map.map[x + 1][y + 1] == HALL && map.mask[x + 1][y + 1] == 0)
			{
				stk.push(x + 1);
				stk.push(y + 1);
			}
			map.mask[x + 1][y + 1] = 1;

			if (map.map[x + 1][y - 1] == HALL && map.mask[x + 1][y - 1] == 0)
			{
				stk.push(x + 1);
				stk.push(y - 1);
			}
			map.mask[x + 1][y - 1] = 1;

			if (map.map[x - 1][y + 1] == HALL && map.mask[x - 1][y + 1] == 0)
			{
				stk.push(x - 1);
				stk.push(y + 1);
			}
			map.mask[x - 1][y + 1] = 1;

			if (map.map[x - 1][y - 1] == HALL && map.mask[x - 1][y - 1] == 0)
			{
				stk.push(x - 1);
				stk.push(y - 1);
			}
			map.mask[x - 1][y - 1] = 1;

			if (map.map[x - 1][y] == HALL && map.mask[x - 1][y] == 0)
			{
				stk.push(x - 1);
				stk.push(y);
			}
			map.mask[x - 1][y] = 1;

			if (map.map[x + 1][y] == HALL && map.mask[x + 1][y] == 0)
			{
				stk.push(x + 1);
				stk.push(y);
			}
			map.mask[x + 1][y] = 1;

			if (stk.empty())
			{
				break;
			}
		}
		PrintMap(); //���������� ����������� �����
	}

	// ����� ��� ��������� ����� �� ������� ����
	void Map::PlaceFlag(int x, int y)
	{
		if (mask[y][x] == HALL) //���������, ��� ������ ��� �� �������
		{
			mask[y][x] = 2; //������������� ����
			PrintMap(); //��������� ����� ����� ��������� �����
		}
		else if (mask[y][x] == 2) //���� � ������ ��� ���������� ����
		{
			mask[y][x] = HALL; //������� ����, ��������������� �����
			PrintMap(); //��������� ����� ����� �������� �����
		}
	}