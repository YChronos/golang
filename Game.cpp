#include "Game.h"
#include "Strategy.h"
#include "HumanPlayer.h"
#include "Chessboard.h"

ChessBoard* Game::board = new ChessBoard;
int Game::gameModel = 0;//1->���VS���;2->���VS����
int Game::isFirst = 0;//1->�������;2->��������
int Game::now = 0;//1->��ǰ�����;2->��ǰ������;now==firstʱ,Ϊ����
bool Game::isEnd = false;//�Ƿ����
bool Game::isBan = false;//�Ƿ񱻽�
int Game::total = 0;//����
int Game::score1 = 0;//����
int Game::score2 = 0;//����
int Game::steps = 0;//����,�жϺ���
Game::Game()
{
	
}


Game::~Game()
{
	delete board;
}

ChessBoard * Game::getChessBoard()
{
	return board;
}

int Game::getGameModel()
{
	return gameModel;
}

int Game::getIsFirst()
{
	return isFirst;
}

int Game::getNow()
{
	return now;
}

bool Game::getIsEnd()
{
	return isEnd;
}

void Game::setIsBan(bool ban)
{
	isBan = ban;
}

bool Game::getIsBan()
{
	return isBan;
}

int Game::getTotal()
{
	return total;
}

int Game::getScore1()
{
	return score1;
}
int Game::getScore2()
{
	return score2;
}
int Game::getSteps() {
	return steps;
}
void Game::addSteps() {
	steps += 1;
}
void Game::introduction()
{
	cout << "�W�������������������������������������������������Z" << endl;
	cout << "�U         ~~~~~~��ӭ������������Ϸ~~~~~~         �U" << endl;
	cout << "�U         1 ��ʼ��Ϸ                             �U" << endl;
	cout << "�U         2 �������                             �U" << endl;
	cout << "�U         3 �˳�                                 �U" << endl;
	cout << "�]�������������������������������������������������`" << endl;
}

void Game::regulation()
{
	cout << "���ȡ��׺󣬴���Ԫ��ʼ�໥˳������" << endl;
	cout << "��ʱʱ��Ϊ15s,��ʱ����" << endl;
	cout << "���������̺�������б���γ���������ͬɫ������ӵ�һ��Ϊʤ" << endl;
	cout << "���������ͬʱ�γɣ�����Ϊʤ��" << endl;
	cout << "�ڷ������γ�ʱ���׷��ĳ���Ӧ����ָ�������׷�δ���ֻ��ֺ�δָ��������Ӧ�ӣ������кڷ�����" << endl;
	cout << "ÿ��ѡ�ֱ������֣�����ִ�����У�ʤһ�ּ�2�֣���һ�ּ�0�֣��������1�֡�" << endl;

}
void Game::startGame()
{
loop1:
	system("cls");
	char tmpModel;
	char tmpFirst;
	cout << "��ѡ���淨:" << endl;
	cout << "People VS People (1)" << endl;
	cout << "People VS Computer (2)" << endl;
	cin >> tmpModel;
	switch (tmpModel)
	{
	case '1':
		cout << "OK! you choose People VS People.Good Game!" << endl;
		Game::gameModel=1;
		break;
	case '2':
		cout << "OK! you choose People VS Computer.Good Game!" << endl;
		Game::gameModel = 2;
		break;
	default:
		cout << "����������" << endl;
		goto loop1;
		break;
	}
loop2:
	cout << "��ѡ��:����(1)����(2):" << endl;
	cin >> tmpFirst;
	switch (tmpFirst)
	{
	case '1':
		cout << "YOU choose First" << endl;
		Game::isFirst = 1;
		Game::now = 1;
		break;
	case '2':
		cout << "YOU choose Second" << endl;
		Game::isFirst = 2;
		Game::now = 2;
		break;
	default:
		cout << "����������" << endl;
		goto loop2;
		break;
	}
	switch (Game::gameModel){
		case 1:
			people();
			break;
		case 2:
			ai();
			break;
	}
}
//����̨��Ϣ��Ӧ
void CALLBACK TimerProc(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
	if (1 == idEvent)
	{//����Ƕ�ʱ��1
		::MessageBeep(0);//Beep��
	}

}
void Game::people() {
	HumanPlayer* player1 = new HumanPlayer;
	HumanPlayer* player2 = new HumanPlayer;
	while (!Game::isEnd)
	{
		int result = 0;
		if (now == 2) {
			result =player2->play();
			Game::addSteps();
		}
		else {
			result = player1->play();
			Game::addSteps();
		}
		switch (result) {
		case 0:
			break;
		case 2:
			cout << "����" << endl;
			Game::total += 1;
			Game::score1 += 1;
			Game::score2 += 1;
			Game::isEnd = true;
			Sleep(2000);
			break;
		case 1:
			cout << "�������1ʤ" << endl;
			Game::total += 1;
			Game::score1 += 2;
			Game::isEnd = true;
			Sleep(2000);
			break;
		case -1:
			cout << "�������2ʤ" << endl;
			Game::total += 1;
			Game::score2 += 2;
			Game::isEnd = true;
			Sleep(2000);
			break;
		default:
			break;
		}
		if (result != 0) {
			if (Game::total < 2) {
				Game::isFirst = 3-isFirst;
				Game::now = Game::isFirst;
				Game::isEnd = false;//�Ƿ����
				Game::isBan = false;//�Ƿ񱻽�
				Game::board = new ChessBoard;
				Game::steps = 0;//��ղ���
				return people();
			}
			else {
				if (Game::score1 > Game::score2) {
					cout << "���һʤ�����÷�:" << Game::score1 << endl;
					system("pause");
					return;
				}
				else if (Game::score2 > Game::score1) {
					cout << "��Ҷ�ʤ�����÷�:" << Game::score2 << endl;
					system("pause");
					return;
				}
				else {
					cout << "ƽ��" << endl;
					cout << "���һ�÷�"<<Game::score1<<"��Ҷ��÷�:"<<Game::score2<<endl;
					system("pause");
					return;
				}
			}
		}
		Game::now = (3 - Game::now);//�����巽
	}
}
void Game::ai() {
	Strategy* stra= new Strategy;
	HumanPlayer* player = new HumanPlayer;

	while (!Game::isEnd)
	{
		int result=0;
		if (now == 2) {
			result=stra->AI();
			Game::addSteps();
		}
		else {
			result=player->play();
			Game::addSteps();
		}
		//û�з��ֽ���,������
		if (now != isFirst)Game::isBan = false;
		switch (result) {
		case 0:
			break;
		case 2:
			cout << "����" << endl;
			Game::total += 1;
			Game::score1 += 1;
			Game::score2 += 1;
			Game::isEnd = true;
			Sleep(2000);
			break;
		case 1:
			cout << "�������ʤ" << endl;
			Game::total += 1;
			Game::score1 += 2;
			Game::isEnd = true;
			Sleep(2000);
			break;
		case -1:
			cout << "���ֵ���ʤ" << endl;
			Game::total += 1;
			Game::score2 += 2;
			Game::isEnd = true;
			Sleep(2000);
			break;
		default:
			break;
		}
		if (result != 0) {
			if (Game::total < 2) {
				Game::isFirst = 3 - Game::isFirst;
				Game::now = Game::isFirst;
				Game::isEnd = false;//�Ƿ����
				Game::isBan = false;//�Ƿ񱻽�
				Game::board = new ChessBoard;
				Game::steps = 0;
				return ai();
			}
			else {
				if (Game::score1 > Game::score2) {
					cout << "���ʤ�����÷�:" << Game::score1 << endl;
					system("pause");
					return;
				}
				else if (Game::score2 > Game::score1) {
					cout << "����ʤ�����÷�:" << Game::score2 << endl;
					system("pause");
					return;
				}
				else {
					cout << "ƽ��" << endl;
					cout << "��ҵ÷�" << Game::score1 << "���Ե÷�:" << Game::score2 << endl;
					system("pause");
					return;
				}
			}
		}
		Game::now=(3-Game::now);//�����巽
		
	}
}
/*
int Game::getModel() {
	return Game::gameModel;
}
int Game::getFirst() {
	return Game::isFirst;
}
void Game::setModel(int tmp) {
	Game::gameModel = tmp;
}
void Game::setFirst(int tmp) {
	Game::isFirst = tmp;
}
ChessBoard* Game::getChessBoard() {
	return board;
}
int Game::getNow() {
	return now;
}
void Game::setNow(int tmp) {
	now = tmp;
}
bool Game::getEnd() {
	return isEnd;
}
void Game::setEnd(bool tmp) {
	isEnd= tmp;
}
*/