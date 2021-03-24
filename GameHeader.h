#pragma once
class Location
{
protected:
	int X;
	int Y;
public:
	Location(int initX, int initY);
	int GetX();
	int GetY();

};



class Point :public Location //�����, ������ ������� ������
{
protected:
	bool Visible;
public:
	Point(int initX, int initY);
	bool IsVisible();
	virtual void Spawn(); //����� �����
	virtual int returnfriend();
	virtual void setcolor();
	virtual void MoveTo(int NewX, int NewY); //���������� �����
	virtual void Show(); //��������
	virtual void Hide(); //���������
};


class IClocks //��������� �����
{
public:
	virtual void ShowTime() = 0; //�������� ����� (�������)
	virtual void HideTime() = 0; //(�������� �������)
	virtual void BuzzerColor() = 0; //����������� ��������� �����-�� ������
	virtual void ShowInd(int* i) = 0; //���������� ����� �� �������
	virtual void HideInd(int* i) = 0; //����������� ����� �� �������
	virtual void EnergyBar() = 0; //������� �����
};


class Clocks :public IClocks, public Point //���� 
{
protected:
	int Lives; //���������� ������
	int Points; //���������� �����
	int Height; //������ �����
	int radius; //������ �������
	int Width; //������ �����
public:
	Clocks(int initX, int initY, int NHeight, int NWidth);
	int TakePoint(int value); //�������� ���� �������
	int LivesStat(int value); //����������, ��������� � ����������� ���������� ������
	int SizeX(); //���������� ������ �� X+������
	int SizeY(); //���������� ������ �� Y+������
	virtual void Hide() override; //�������� ����
	virtual void Show() override; //��������
	virtual void ShowTime() override; //�� ���������
	virtual void BuzzerColor() override;
	virtual void EnergyBar() override;
	virtual void ShowInd(int* i) override;
	virtual void HideInd(int* i) override;
	virtual void HideTime() override;
	virtual void Expand(int value); //����� ���������� �����
	virtual void Reduce(int value); //����� ���������� �����

};

class Frame : public Clocks //����� �����, ����������� ����
{
public:
	Frame(int iniX, int initY, int NHeight, int NWidth); //����������� �����
	virtual void Show() override; //�������� �����
	virtual void Hide() override; //�������� �����
};

class Enemy :public Point //������� ���������, ����������� �� ������
{
protected:
	int friendorfoe; //���� ��� ����
public:
	Enemy(int initX, int initY);
	virtual void MoveTo(int NewX, int NewY) override; //����������� ������� �� ������
	virtual void Show() override; //�������� �������
	void Hide(); //�������� �������
	virtual void Spawn() override; //������� �������
	virtual int returnfriend() override; //���������� ������ �������


};
class WiseEnemy :public Enemy //���������, ����������� �� ���������
{
public:
	WiseEnemy(int iniX, int initY);
	virtual void MoveTo(int NewX, int NewY) override; //������� ������� �� ���������
};


class Healer :public Point //�������
{
protected:
	int size; //������ �������
	int ressurection; //���� ��������� �������
public:
	Healer(int initX, int initY, int NHeight, int NWidth);
	void Spawn();
	int Ressurect(); //�������� ���������
	void DelChance(); //������� ���� ��������� �������
	void GetScoreInExchange(); //��� ���������� ������� ������� �� �������������� �������
	virtual void Show() override;
	void Hide();

};

class FireClocks :public Frame //�������� ���� ���� ��������
{
public:
	FireClocks(int initX, int initY, int NHeight, int NWidth);
	virtual void BuzzerColor() override; //���� �����
	virtual void EnergyBar() override; //���� ����� �������

};

class SickClocks :public Frame //������� ����, �������� ��������, ������� ����
{
public:
	SickClocks(int initX, int initY, int NHeight, int NWidth);
	virtual void BuzzerColor() override; //���� �����
	virtual void EnergyBar() override; //���� �������
};
