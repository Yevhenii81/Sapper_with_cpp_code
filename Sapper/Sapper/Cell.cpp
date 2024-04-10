#include "Cell.h"


	Cell::Cell() : isMine(false), isRevealed(false), adjacentMines(0) {}

	//�����, ������� �������� ����������� ����
	void Cell::RandMines(int numMines, Map& map)
	{
		//�������� �� ���������� ���, ������� ����� ���������� �� ����
		if (numMines >= (map.width - 2) * (map.width - 2))
		{
			MessageBoxA(0, "������� ����� ���!", "���������� ������!", MB_OK);
			return;
		}
		for (int i = 0; i < numMines; i++)
		{
			int x = 0;
			int y = 0;
			//����� ������ ������, �� ������� �����
			do
			{
				x = rand() % (map.width - 2) + 1;
				y = rand() % (map.height - 2) + 1;
			} while (map.map[x][y] == MINE);
			map.map[x][y] = MINE;
		}
	}