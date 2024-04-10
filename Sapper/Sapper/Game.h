#pragma once
#include "Console.h"
#include "Map.h"
#include "Cell.h"

class Game
{
public:
	Map map;
	Cell cell;
	Console console;

	void ResizeMap(int w, int h, int numMines);

	void StartEasyLevel();

	void StartMediumLevel();

	void StartHardLevel();

	void Menu();

	//����� ���������
	void GameOver();

	//����� �������� 
	void Won();

	//�����, ������� ��������� ����, �������������� �����, ����������� ����,
	//��������� ������ ��������� ���������� � ��������� ������� ������
	void run();
};