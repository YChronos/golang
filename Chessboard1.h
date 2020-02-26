#pragma once
#include <iostream>
#include <string>
#include<tchar.h>

using namespace std;
class Chessboard
{
//���Щ�
private:
	wchar_t board[15][17] = {
		L"����ЩЩЩЩЩЩЩЩЩЩЩ�\n",
		L"�����������������\n",
		L"�����������������\n",
		L"�����������������\n",
		L"�����������������\n",
		L"�����������������\n",
		L"�����������������\n",
		L"�����������������\n",
		L"�����������������\n",
		L"�����������������\n",
		L"�����������������\n",
		L"�����������������\n",
		L"�����������������\n",
		L"�����������������\n",
		L"���ةةةةةةةةةةةةة�\n" };
	wchar_t chessman[5] = { L"������" };
	int blank = 225;
public:
	Chessboard();
	~Chessboard();
	void draw();
	void setof(int i, int j, int type);
	void setof(int i, int j, wchar_t type);
	wchar_t getof(int i, int j);
	wchar_t getChessman(int i);
	bool allow(int i, int j);
	int checkType(int i, int j);
	int getBlank();
	bool validPosition(int i, int j);
};
