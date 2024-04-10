#pragma once
#include "Console.h"

class Map : public Console
{
private:
	/*int width = 10;
	int height = 10;*/
	int width;
	int height;
	friend class Cell;
	friend class Game;

	bool isGameWon;  //���������� ��� ������������ ��������
	vector<vector<int>> map;  //��������� ������ ��� �������� ����
	vector<vector<int>> mask;  //��������� ������ ��� ����� �������� ����
	HANDLE h;  //���������� ��� ������ � ��������
public:
	/*Map(int w, int h) : width(w), height(h), h(GetStdHandle(STD_OUTPUT_HANDLE))
	{
		InitializeMap();
		InitializeMask();
	}*/

	Map();

	void setWidth(int w);
	int getWidth() const;
	void setHeight(int h);
	int getHeight() const;
	void setIsGameWon(bool value);
	bool getIsGameWon() const;
	void setMap(const std::vector<std::vector<int>>& newMap);
	std::vector<std::vector<int>> getMap() const;
	void setMask(const std::vector<std::vector<int>>& newMask);
	std::vector<std::vector<int>> getMask() const;
	void setHandle(HANDLE newHandle);
	HANDLE getHandle() const;

	//����� ��� ������������� �������� ����
	void InitializeMap();

	//����� ��� ����������� �������� ����
	void PrintMap();

	//����� ��� ����������� ����� �� ������� ����
	void NumberSetting();

	//����� ��� ������������� ����� (��������� �����)
	void InitializeMask();

	//����� ��� �������� ������ � ���������� �����
	int OpenCell(int x, int y);

	//����� ��� �������� �������� � ����
	bool CheckGameWon();

	//����� ��� ������� ������ ������� �� ������� ����
	//������������ ���� ��� �������� ��������� ����� ��� �������
	//��������� ����� ���� � ���������� ��������� �� ������
	void Fill(int px, int py, Map& map);

	// ����� ��� ��������� ����� �� ������� ����
	void PlaceFlag(int x, int y);
};