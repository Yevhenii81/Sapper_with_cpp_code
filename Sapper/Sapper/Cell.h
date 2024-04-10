#pragma once

#include "Console.h"
#include "Map.h"

class Cell
{
private:
	bool isMine;
	bool isRevealed;
	int adjacentMines;
public:
	Cell();

	//�����, ������� �������� ����������� ����
	void RandMines(int numMines, Map& map);
};