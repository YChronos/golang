#include "HumanPlayer.h"
#include "Chessboard.h"
#include "Game.h"
#include "Judge.h"
#include <limits>
#include <iostream>
#undef max
using namespace std;

HumanPlayer::HumanPlayer()
{
}


HumanPlayer::~HumanPlayer()
{
}

int HumanPlayer::play()
{
	Judge* judge = new Judge;
	player_start = time(0);
	ChessBoard::DrawBoard(Game::getChessBoard()->getQp());
	if (Game::getGameModel()==2) {
		printf("  �ֵ�����£�����������(eg:H5):");
		if (Game::getNow() != Game::getIsFirst())printf("����'?0'�ٱ�����");
		printf("\n");
	}
	else {
		if (Game::getNow() == 1) {
			printf("  �ֵ�player1�£�����������(eg:H5):");
		}
		else {
			printf("  �ֵ�player2�£�����������(eg:H5):");
		}
		if (Game::getNow() != Game::getIsFirst())cout << "����'?0'�ٱ�����" << endl;
	}
	
	
	char c;
	int row = 0, col = 0;
while (true)
{
	c = '\n';
	cin >> c >> row;
	if (c == '?') {
		if (Game::getNow() == Game::getIsFirst()) {
			cout << "���ܾٱ��Լ�,����������" << endl;
			continue;
		}
		if (Game::getIsBan()) {
			cout << "���־ٱ��ɹ�!YOU WIN!!!" << endl;
			return -1;
		}
		else {
			cout << "û�н���!!!��������:" << endl;
			continue;
		}
	}

	if (c < 'a')col = c - 'A' + 1;
	else col = c - 'a' + 1;
	if (!judge->ok(row, col))
	{
		printf("�˴�������");
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		Sleep(1000);
		continue;
	}
	else
	{
		break;
	}
}
	player_end = time(0);
	if (player_end - player_start > 30) {
		cout << "��ʱ!!!YOU LOSE" << endl;
		return -1;
	}
	return judge->go(row, col);
	return 0;
}