#include <iostream>
#include <string>
#include<tchar.h>
#include "Chessboard.h"

using namespace std;

/*
int main() 
{
	Chessboard* c = new Chessboard;
	c->draw();
	c->setof(0,0,1);
	c->draw();
	wcout <<c->getof(0, 0)<<endl;
	system("PAUSE");
}
*/

Chessboard::Chessboard()
{
}

Chessboard::~Chessboard()
{
}

void Chessboard::draw()
{
	wcout.imbue(locale(locale(), "", LC_CTYPE));
	system("cls");
	for (int i = 0 ; i < 15; i++)
	{
		wcout << board[i];
	}
}

void Chessboard::setof(int i, int j, int type)
{
	board[j][i] = chessman[type];
}

void Chessboard::setof(int i, int j, wchar_t type)
{
	board[j][i] = type;
}

wchar_t Chessboard::getof(int i, int j)
{
	return board[j][i];
}
 
wchar_t Chessboard::getChessman(int i)
{
	return chessman[i];
}

//��ǰλ���Ƿ���������
bool Chessboard::allow(int i,int j)
{
	for (int i = 0; i < sizeof(chessman)/sizeof(chessman[0]); i++)
	{
		if (chessman[i] == board[i][j])
		{
			return false;
		}
	}
	return true;
}

//�жϵ�ǰλ�������Ǻ��廹�ǰ���
//���壺0 ���壺1 û�����ӣ�-1
int Chessboard::checkType(int i, int j)
{
	for (int k = 0; k < sizeof(chessman) / sizeof(chessman[0]); k++)
	{
		if (chessman[k] == board[j][i])
		{
			return k / 2;
		}
	}
	//��ǰλ��û������
	return -1;
}

int Chessboard::getBlank()
{
	return this->blank;
}

bool Chessboard::validPosition(int i, int j)
{
	if (i < 0 || j < 0 || i > 14 || j > 14)
	{
		return false;
	}
}
