#pragma once
#include <time.h>
#include <Windows.h>
#include "Chessboard.h"
using namespace std;
class Game
{
private:
	static ChessBoard* board;
	static int Game::gameModel;//1->���VS���;2->���VS����
	static int Game::isFirst;//1->�������;2->��������
	static int Game::now;//1->��ǰ�����;2->��ǰ������;now==firstʱ,Ϊ����
	static bool Game::isEnd;//�Ƿ����
	static bool Game::isBan;//�Ƿ񱻽�
	static int Game::total;//����
	static int Game::score1;//������>0���Ӯ������AIӮ��
	static int Game::score2;
	static int Game::steps;
public:
	Game();
	~Game();
	static ChessBoard* getChessBoard();
	static int getGameModel();
	static int getIsFirst();
	static int getNow();
	static bool getIsEnd();
	static void setIsBan(bool ban);
	static bool getIsBan();
	static int getTotal();
	static int getScore1();
	static int getScore2();
	static int getSteps();
	static void addSteps();
	/*
	int getModel();
	void setModel(int tmp);
	int getFirst();
	void setFirst(int tmp);
	int getNow();
	void setNow (int tmp);
	bool getEnd();
	void setEnd(bool tmp);
	*/
	

	void introduction();
	void regulation();
	void startGame();
	
	void ai();
	void people();

};

