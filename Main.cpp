#include<iostream>
#include<windows.h>
#include "Game.h"
int main()
{
	system("color f0");
	Game* game = new Game;
loop1:
	system("cls");
	game->introduction();
	char c;
	cin >> c;
	switch (c)
	{
		//��ʼ��Ϸ
	case '1':
		game->startGame();
		break;
		//��ӡ��Ϸ����
	case '2':
		game->regulation();
		cout << "������������˵�" << endl;
		cin >> c;
		goto loop1;
		break;
		//�˳���Ϸ
	case '3':
		cout << "��Ϸ����!!!" << endl;
		return 0;
		system("pause");
		break;
	default:
		goto loop1;
		break;
	}
}
