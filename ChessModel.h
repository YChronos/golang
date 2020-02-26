#pragma once
class ChessModel
{
private:
	//��ʤ��
	int five;
	//��������
	int liveFour;
	//��������
	int four;
	//��������
	int liveThree;
	//��������
	int three;
	//�������
	int liveTwo;
	//�������
	int two;
	//��һ����
	int liveOne;
	//��һ����
	int one;
	//��������
	int longConnection;
public:
	ChessModel();
	~ChessModel();
	int getFive();
	int getLiveThree();
	int getThree();
	int getLiveFour();
	int getFour();
	int getLiveTwo();
	int getTwo();
	int getLiveOne();
	int getOne();
	int getLongConnection();
	void setFive(int num);
	void setLiveThree(int num);
	void setThree(int num);
	void setLiveFour(int num);
	void setFour(int num);
	void setLiveTwo(int num);
	void setTwo(int num);
	void setLiveOne(int num);
	void setOne(int num);
	void setLongConnection(int num);
	void addFive(int num);
	void addLiveThree(int num);
	void addThree(int num);
	void addLiveFour(int num);
	void addFour(int num);
	void addLiveTwo(int num);
	void addTwo(int num);
	void addLiveOne(int num);
	void addOne(int num);
	void addLongConnection(int num);
};