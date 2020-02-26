#include <iostream>
#include <string>
#include "Judge.h"
#include "Game.h"
#include "Point.h"
using namespace std;
Judge::Judge()
{
}


Judge::~Judge()
{
}

//�������֣������������Ľ��֡���������
//�����жϷ�����������һ�����Ӻ���һ���ܷ��γɻ���
//0��ʾ���γɽ��֣�1��ʾ�γɽ���
int Judge::judgeForbiddenMove(Point point, ChessBoard* chessBoard, string& info)
{
	int preType = chessBoard->getof(point);
	//��ǰ������
	chessBoard->setof(point, 1);
	ChessModel chessModel;
	for (int k = 0; k < 4; k++)
	{
		caculateModel(point, k, chessBoard, chessModel);
		if (chessModel.getFive() >= 1)
		{
			break;
		}
	}
	//��ԭ
	chessBoard->setof(point, preType);
	if (chessModel.getFive() >= 1)
	{
		info = "û�н���";
		return 0;
	}
	else if (chessModel.getLiveThree() >= 2 || chessModel.getFour() >= 2 || chessModel.getLongConnection() >= 1)
	{
		info = "���ֽ���,���� " + to_string(chessModel.getLiveThree()) + " �ģ�" + to_string(chessModel.getFour()) + " ����: " + to_string(chessModel.getLongConnection());
		return 1;
	}
	else
	{
		info = "û�н���";
		return 0;
	}
}

void Judge::caculateModel(Point point, int direction, ChessBoard* chessBoard, ChessModel& chessModel)
{
	Point next;
	Point pointA;
	Point pointB;
	Point innerPointA;
	Point innerPointB;
	bool innerA = false, innerB = false;
	bool marginA = false, marginB = false;
	int marginNumA = 0, marginNumB = 0;
	int series = 1;
	int directionX = point.getX();
	int directionY = point.getY();
	int empty = 0;
	int black = 1;
	while (1 == nextPoint(directionX, directionY, direction, next))
	{
		if (black == abs(chessBoard->getof(next)))
		{
			++series;
		}
		else if (empty == abs(chessBoard->getof(next)))
		{
			if (innerA && !marginA)
			{
				pointA.setX(next.getX());
				pointA.setY(next.getY());
				marginA = true;
				++marginNumA;
			}
			else if (marginNumA <= 4)
			{
				++marginNumA;
				//break;
			}

			//��λ�õ���һ����
			if (1 == nextPoint(directionX, directionY, direction, next))
			{
				//��λ�õ���һ����Ϊ��λ��
				if (empty == abs(chessBoard->getof(next)))
				{
					frontPoint(next.getX(), next.getY(), direction, pointA);
					marginA = true;
					marginNumA += 1;
					break;
				}
				//��λ�õ���һ����Ϊ��������
				else if (black == abs(chessBoard->getof(next)))
				{
					++series;
					innerA = true;
					frontPoint(next.getX(), next.getY(), direction, innerPointA);
				}
				//��λ�õ���һ����Ϊ�Է�����
				else
				{
					frontPoint(next.getX(), next.getY(), direction, pointA);
					marginA = true;
					++marginNumA;
					break;
				}
			}
			//��λ�õ���һ��û��λ����
			else
			{
				pointA.setX(next.getX());
				pointA.setY(next.getY());
				marginA = true;
				break;
			}
		}
		else
		{
			pointA.setX(next.getX());
			pointA.setY(next.getY());
			//�Է�����
			break;
		}
	}
	marginNumA -= innerA;
	directionX = point.getX();
	directionY = point.getY();
	direction = (direction + 4) % 8;
	while (1 == nextPoint(directionX, directionY, direction, next))
	{
		if (black == abs(chessBoard->getof(next)))
		{
			++series;
		}
		else if (empty == abs(chessBoard->getof(next)))
		{
			if (innerB && !marginB)
			{
				pointB.setX(next.getX());
				pointB.setY(next.getY());
				marginB = true;
				++marginNumB;
			}
			else if (marginNumB <= 4)
			{
				++marginNumB;
			}

			//��λ�õ���һ����
			if (1 == nextPoint(directionX, directionY, direction, next))
			{
				//��λ�õ���һ����Ϊ��λ��
				if (empty == abs(chessBoard->getof(next)))
				{
					frontPoint(next.getX(), next.getY(), direction, pointB);
					marginB = true;
					marginNumB += 1;
					break;
				}
				//��λ�õ���һ����Ϊ��������
				else if (black == abs(chessBoard->getof(next)))
				{
					++series;
					innerB = true;
					frontPoint(next.getX(), next.getY(), direction, innerPointB);
				}
				//��λ�õ���һ����Ϊ�Է�����
				else
				{
					frontPoint(next.getX(), next.getY(), direction, pointB);
					marginB = true;
					++marginNumB;
					break;
				}
			}
			//��λ�õ���һ��û��λ����
			else
			{
				pointB.setX(next.getX());
				pointB.setY(next.getY());
				marginB = true;
				break;
			}
		}
		else {
			//�Է�����
			pointB.setX(next.getX());
			pointB.setX(next.getX());
			break;
		}
	}
	marginNumB -= innerB;
	string s;
	bool forbiddenMoveA = true;
	bool forbiddenMoveB = true;
	bool forbiddenMoveInnerA = true;
	bool forbiddenMoveInnerB = true;

	if (5 == series && !innerA && !innerB)
	{
		chessModel.addFive(1);
	}
	else if (innerA && innerB && series == 6)
	{
		int lengthA = caculateLength(pointA, innerPointB, direction);
		int lengthB = caculateLength(pointB, innerPointA, direction);
		if (lengthA == 5 && lengthB == 5 && judgeForbiddenMove(innerPointA, chessBoard, s) == 0
			&& judgeForbiddenMove(innerPointB, chessBoard, s) == 0)
		{
			//������ֲ������ֻ��Ļ��ǳ��ģ�ͳһ���ļ�¼
			chessModel.addFour(2);
		}
	}
	else if (series == 5 && (innerA || innerB))
	{
		int lengthA = caculateLength(pointA, innerPointB, direction);
		int lengthB = caculateLength(pointB, innerPointA, direction);
		if (((innerA && lengthB == 4 && marginB && judgeForbiddenMove(pointB, chessBoard, s) == 0)
			|| (innerB && lengthA == 4 && marginA && judgeForbiddenMove(pointA, chessBoard, s) == 0)))
		{
			//������ж�
			chessModel.addFour(1);
		}
	}
	else if (!innerA && !innerB && series >= 6)
	{
		//����
		chessModel.addLongConnection(1);
	}
	else if (!innerB && !innerA && series == 4 && ((marginA && judgeForbiddenMove(pointA, chessBoard, s) == 0)
		|| (marginB && judgeForbiddenMove(pointB, chessBoard, s) == 0)))
	{
		//�����ĵ��ж�--������
		chessModel.addFour(1);
	}
	else if (series == 4 && ((innerA && judgeForbiddenMove(innerPointA, chessBoard, s) == 0)
		|| (innerB && judgeForbiddenMove(innerPointB, chessBoard, s) == 0)))
	{
		//�����ĵ��ж�--�����
		chessModel.addFour(1);
	}
	else if (series == 3 && !innerA && !innerB && marginA && marginB &&
		judgeForbiddenMove(pointA, chessBoard, s) == 0 && judgeForbiddenMove(pointB, chessBoard, s) == 0)
	{
		int rivalType = 2;
		//�����ж�--������
		Point pointA2;
		Point pointB2;
		if (nextPoint(pointA, (direction + 4) % 8, pointA2) == 1
			&& rivalType != abs(chessBoard->getof(pointA2)) && judgeForbiddenMove(pointA2, chessBoard, s) == 0)
		{
			chessModel.addLiveThree(1);
		}
		else if (nextPoint(pointB, direction, pointB2) == 1
			&& rivalType != abs(chessBoard->getof(pointB2)) && judgeForbiddenMove(pointB2, chessBoard, s) == 0)
		{
			chessModel.addLiveThree(1);
		}
	}
	else if (series == 3 && marginA && marginB && ((innerA && judgeForbiddenMove(innerPointA, chessBoard, s) == 0) ||
		(innerB && judgeForbiddenMove(innerPointB, chessBoard, s) == 0)) && judgeForbiddenMove(pointA, chessBoard, s) == 0
		&& judgeForbiddenMove(pointB, chessBoard, s) == 0)
	{
		//�����ж�--�����
		chessModel.addLiveThree(1);
	}
}

/*
������һ����
direction: 1
*/
int Judge::frontPoint(int i, int j, int direction, Point& next)
{
	if (i < 0 || j < 0 || i > 14 || j > 14)
	{
		return -1;
	}
	switch (direction)
	{
	case 0:
		j++;
		break;
	case 1:
		i--;
		j++;
		break;
	case 2:
		i--;
		break;
	case 3:
		i--;
		j--;
		break;
	case 4:
		j--;
		break;
	case 5:
		i++;
		j--;
		break;
	case 6:
		i++;
		break;
	case 7:
		i++;
		j++;
		break;
	default:
		return -1;
		break;
	}
	if (i < 0 || j < 0 || i > 14 || j > 14)
	{
		return -1;
	}
	next.setX(i);
	next.setY(j);
	return 1;
}

/*
������һ����
direction: 1
*/
int Judge::nextPoint(Point current, int direction, Point& next)
{
	int i = current.getX(), j = current.getY();
	if (i < 0 || j < 0 || i > 14 || j > 14)
	{
		return -1;
	}
	switch (direction)
	{
	case 0:
		j--;
		break;
	case 1:
		i++;
		j--;
		break;
	case 2:
		i++;
		break;
	case 3:
		i++;
		j++;
		break;
	case 4:
		j++;
		break;
	case 5:
		i--;
		j++;
		break;
	case 6:
		i--;
		break;
	case 7:
		i--;
		j--;
		break;
	default:
		return -1;
		break;
	}
	if (i < 0 || j < 0 || i > 14 || j > 14)
	{
		return -1;
	}
	next.setX(i);
	next.setY(j);
	return 1;
}

int Judge::caculateLength(Point A, Point B, int direction)
{
	switch (direction)
	{
	case 0:
	case 4:
		return abs(A.getY(), B.getY()) - 1;
	case 1:
	case 5:
	case 3:
	case 7:
		return abs(A.getY(), B.getY()) - 1;
	case 2:
	case 6:
		return abs(A.getX(), B.getX()) - 1;
	default:
		return -100;
		break;
	}
}

int Judge::abs(int A, int B)
{
	return A - B > 0 ? A - B : B - A;
}

bool Judge::ban(int row, int col) {
	//ִ�ײ�������
	if (same(row, col, 2))return false;
	Point p(col,16 - row);
	string s;
	bool flag=(1==judgeForbiddenMove(p,Game::getChessBoard(),s));
	return flag;
}
int Judge::same(int row, int col, int key)//�ж�2�������Ƿ�ͬɫ
{
	if (!inChessBoard(row, col))return false;
	return (Game::getChessBoard()->getof(row,col) == key || Game::getChessBoard()->getof(row, col) + key == 0);
}

int Judge::num(int row, int col, int u)//���꣨row,col������������u
{
	int i = row + directionRow[u], j = col + directionCol[u], sum = 0, ref = Game::getChessBoard()->getof(row, col);
	if (ref == 0)return 0;
	while (same(i, j, ref))sum++, i += directionRow[u], j += directionCol[u];
	return sum;
}

bool Judge::ok(int row, int col) {
	return inChessBoard(row, col) && (Game::getChessBoard()->getof(row, col) == 0);
}
int Judge::go(int row, int col) {
	if (Game::getNow()==Game::getIsFirst())Game::getChessBoard()->setof(row,col,-1); //��������µ���
	else Game::getChessBoard()->setof(row, col, -2);
	for (int i = 0; i <= 15; i++)
		for (int j = 0; j <= 15; j++) //ȡ����һ��������ı�ʶ
	{
		if (i == row && j == col)continue;
		if (Game::getChessBoard()->getof(i ,j) < 0)Game::getChessBoard()->setof(i,j,Game::getChessBoard()->getof(i,j)*(-1));
	}
	ChessBoard::DrawBoard(Game::getChessBoard()->getQp());
	if (ban(row, col))
	{
		if (Game::getGameModel() != 2) {
			if (Game::getNow() == Game::getIsFirst())Game::setIsBan(true);
		}
		else {
			if (Game::getNow() == Game::getIsFirst())Game::setIsBan(true);
		}
		
	}
	if (chessOver(row, col)==2) {
		return 2;
	}
	if (chessOver(row, col))
	{
		if (Game::getNow() == 2) {
			return -1;
		}
		else{
			return 1;
		}
		Sleep(10000);
	}
	return 0;
}
//�ж��¸���ʱ,�Ƿ����
bool Judge::chessOver(int row, int col) {
	bool end = false;
	for (int u = 0; u < 4; u++)if (num(row, col, u) + num(row, col, u + 4) >= 4)end = true;
	if (!end && Game::getSteps() == 224)return 2;//����
	return end;
}
//�ж������Ƿ������̷�Χ��
bool Judge::inChessBoard(int row, int col) {
	if (row < 1 || row > 15 || col < 1 || col>15)return false;
	else return true;
}

//�жϵ�ǰ���Ƿ��γɻ���
int Judge::liveFour(int row, int col)
{
	int key = Game::getChessBoard()->getof(row, col);
	int sum = 0;
	for (int u = 0; u < 4; u++)
	{
		//ÿ�������������
		int sumCurrent = 1;
		int i = 0;
		for (i = 1; same(row + directionRow[u] * i, col + directionCol[u] * i, key); i++)sumCurrent++;
		if (!inChessBoard(row + directionRow[u] * i, col + directionCol[u] * i) || Game::getChessBoard()->getof( row + directionRow[u] * i, col + directionCol[u] * i) != 0)
			continue; 
		for (i = -1; same(row + directionRow[u] * i, col + directionCol[u] * i, key); i--)
			sumCurrent++;
		if (!inChessBoard(row + directionRow[u] * i, col + directionCol[u] * i) || Game::getChessBoard()->getof(row + directionRow[u] * i, col + directionCol[u] * i) != 0)
			continue;
		if (sumCurrent == 4)sum++;
	}
	return sum;
}
//����
int Judge::reachFour(int row, int col)
{
	int key = Game::getChessBoard()->getof(row,col), sum = 0;
	for (int u = 0; u < 8; u++)
	{
		int i = 0;
		int  sumCurrent = 0;
		bool flag = true;
		for (i = 1; same(row + directionRow[u] * i, col + directionCol[u] * i, key) || flag; i++)
		{
			if (!same(row + directionRow[u] * i, col + directionCol[u] * i, key))
			{
				if (flag && Game::getChessBoard()->getof(row + directionRow[u] * i,col + directionCol[u] * i))sumCurrent -= 10;
				flag = false;
			}
			sumCurrent++;
		}
		if (!inChessBoard(row + directionRow[u] * --i, col + directionCol[u] * i))continue;
		for (i = -1; same(row + directionRow[u] * i, col + directionCol[u] * i, key); i--)sumCurrent++;
		if (sumCurrent == 4)sum++;
	}
	return sum - liveFour(row, col) * 2;
}
//����
int Judge::liveThree(int row, int col)
{
	int key = Game::getChessBoard()->getof(row,col), sum = 0;
	for (int u = 0; u < 4; u++)
	{
		int i = 0;
		int sumCurrent = 1;
		for (i = 1; same(row + directionRow[u] * i, col + directionCol[u] * i, key); i++)sumCurrent++; 
		if (!inChessBoard(row + directionRow[u] * i, col + directionCol[u] * i) || Game::getChessBoard()->getof(row + directionRow[u] * i,col + directionCol[u] * i) != 0)
			continue; 
		i++; 
		if (!inChessBoard(row + directionRow[u] * i, col + directionCol[u] * i) || Game::getChessBoard()->getof(row + directionRow[u] * i,col + directionCol[u] * i) != 0)
			continue;;
		for (i = -1; same(row + directionRow[u] * i, col + directionCol[u] * i, key); i--)sumCurrent++;
		if (!inChessBoard(row + directionRow[u] * i, col + directionCol[u] * i) || Game::getChessBoard()->getof(row + directionRow[u] * i,col + directionCol[u] * i) != 0)
			continue; 
		i++; 
		if (!inChessBoard(row + directionRow[u] * i, col + directionCol[u] * i) || Game::getChessBoard()->getof(row + directionRow[u] * i,col + directionCol[u] * i) != 0)
			continue;
		i--;
		if (sumCurrent == 3)sum++;
	}
	for (int u = 0; u < 8; u++)
	{
		int  sumCurrent = 0;
		bool flag = true;
		int i = 0;
		for (i = 1; same(row + directionRow[u] * i, col + directionCol[u] * i, key) || flag; i++)
		{
			if (!same(row + directionRow[u] * i, col + directionCol[u] * i, key))
			{
				if (flag && Game::getChessBoard()->getof(row + directionRow[u] * i,col + directionCol[u] * i))sumCurrent -= 10;
				flag = false;
			}
			sumCurrent++;
		}if (!inChessBoard(row + directionRow[u] * i, col + directionCol[u] * i) ||Game::getChessBoard()->getof(row + directionRow[u] * i,col + directionCol[u] * i) != 0)
			continue;
		if (Game::getChessBoard()->getof(row + directionRow[u] * --i,col + directionCol[u] * i) == 0)
			continue;
		for (i = 1; same(row + directionRow[u] * i, col + directionCol[u] * i, key); i++)sumCurrent++; 
		if (!inChessBoard(row + directionRow[u] * i, col + directionCol[u] * i) || Game::getChessBoard()->getof(row + directionRow[u] * i,col + directionCol[u] * i) != 0)
			continue;
		if (sumCurrent == 3)sum++;
	}
	return sum;
}
//����
bool Judge::overline(int row, int col)
{
	bool flag = false;
	for (int u = 0; u < 4; u++)if (num(row, col, u) + num(row, col, u + 4) > 4)flag = true;
	return flag;
}
int Judge::getDxOf(int pos)
{
	return directionRow[pos];
}
int Judge::getDyOf(int pos)
{
	return directionCol[pos];
}


int Judge::abs(int A)
{
	return A > 0 ? A : -A;
}

/*
������һ����
direction: 1
*/
int Judge::nextPoint(int& i, int& j, int direction, Point& next)
{
	if (i < 0 || j < 0 || i > 14 || j > 14)
	{
		return -1;
	}
	switch (direction)
	{
	case 0:
		j--;
		break;
	case 1:
		i++;
		j--;
		break;
	case 2:
		i++;
		break;
	case 3:
		i++;
		j++;
		break;
	case 4:
		j++;
		break;
	case 5:
		i--;
		j++;
		break;
	case 6:
		i--;
		break;
	case 7:
		i--;
		j--;
		break;
	default:
		return -1;
		break;
	}
	if (i < 0 || j < 0 || i > 14 || j > 14)
	{
		return -1;
	}
	next.setX(i);
	next.setY(j);
	return 1;
}



