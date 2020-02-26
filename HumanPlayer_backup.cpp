#include "HumanPlayer.h"
#include "Chessboard.h"
#include "Game.h"
#include "Judge.h"
#include<string>
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
	
	int row, col;
	char c;
loop1:
	c = '\n';
	row = 0;
	col = 0;
	cin >> c >> row;
	if (c == '?') {
		if (Game::getNow() == Game::getIsFirst()) {
			cout << "���ܾٱ��Լ�,����������" << endl;
			goto loop1;
		}
		if (Game::getIsBan()) {
			cout << "���־ٱ��ɹ�!YOU WIN!!!" << endl;
			return -1;
		}
		else {
			cout << "û�н���!!!��������:" << endl;
			goto loop1;
		}
	}
	if (!(((c <= 'Z' && c >= 'A') || (c <= 'z' && c >= 'a')) && (row > 0 && row <= 15))){
		cout << "�����������������:" << endl;
		
		cin.clear();
		cin.ignore(INT_MAX);
		cin.clear();
		goto loop1;
	}

	if (c <='Z'&&c>='A')col = c - 'A' + 1;
	else if(c<='z'&&c>='a') col = c - 'a' + 1;
	
	if (!judge->ok(row, col))
	{
		printf("�˴�������");
		Sleep(1000);
		goto loop1;
	}
	player_end = time(0);
	if (player_end - player_start > 15) {
		cout << "��ʱ!!!YOU LOSE" << endl;
		return -1;
	}
	return judge->go(row, col);
	//return 0;
}