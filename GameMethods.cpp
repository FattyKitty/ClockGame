#include <iostream>
#include <cmath>
#include "GameHeader.h"
#include <Windows.h>

using namespace std;

extern HDC hdc;

int Location::GetX()
{
	return X;
}

int Location::GetY()
{
	return Y;
}

Location::Location(int initX, int initY)
{
	X = initX;
	Y = initY;
}

Point::Point(int initX, int initY) :Location(initX, initY)
{
	Visible = false;
}


void Point::Hide()
{
	RECT r;
	r.left = 0;
	r.right = 1920;
	r.bottom = 0;
	r.top = 1080;
	FillRect(hdc, &r, (HBRUSH)CreateSolidBrush(RGB(0, 0, 0)));
}
void Point::Show() //����� ����� �� ������
{
	Visible = true;
	for (int i = -1; i < 10; i++)
		for (int j = -1; j < 10; j++)
			SetPixel(hdc, X + i, Y + i, RGB(0, 0, 0));
}
int Point::returnfriend()
{
	return 0;
}
void Point::setcolor()
{

}
void Point::MoveTo(int NewX, int NewY)
{
	Hide();
	X = X + NewX;
	Y = Y + NewY;
	Show();
}

bool Point::IsVisible()
{
	return Visible;
}

void Point::Spawn()
{
}

void Clocks::Show() //���������� �������� ����� �������
{
	char Message[] = "Lives:  "; //����� ������
	char Score[] = "Score:  "; //����� �����
	int param = 0;
	RECT r;
	r.left = X;
	r.right = X + Width;
	r.bottom = Y;
	r.top = Y + Height;
	BuzzerColor();
	HPEN pen = CreatePen(PS_SOLID, 4, RGB(255, 0, 0)); //������� ���� �������
	SelectObject(hdc, pen);
	Message[8] = Lives + '0';
	Score[7] = Points + '0';
	TextOutA(hdc, X, r.top - Width * 0.1, (LPCSTR)Message, 9); //����� ����� ������������� �� �����
	TextOutA(hdc, X + Width / 2, r.top - Width * 0.1, (LPCSTR)Score, 8);
	EnergyBar();
	if (LivesStat(0) == 4)
		ShowTime();
	else if (LivesStat(0) == 3)
	{
		ShowTime();
		HideInd(&param);
	}
	else
		HideTime();
	DeleteObject(SelectObject(hdc, pen));
}

void Clocks::ShowTime()
{
	HPEN pen = CreatePen(PS_SOLID, 4, RGB(255, 0, 0)); //������� ���� �������
	SelectObject(hdc, pen);
	for (int i = Width * 0.25; i < Width * 0.75; i += Width * 0.1) //������ ����� �� �����
	{
		ShowInd(&i);
		MoveToEx(hdc, X + i, Y + Height / 2, NULL);
		LineTo(hdc, X + i, Y + Height / 4);
	}
	DeleteObject(SelectObject(hdc, pen));
}
void Clocks::HideTime() //�������� ���������� ������� �� �����
{
	HPEN pen = CreatePen(PS_SOLID, 4, RGB(169, 169, 169)); //������� ���� �������
	SelectObject(hdc, pen);
	for (int i = Width * 0.25; i < Width * 0.75; i += Width * 0.1) //������ ����� �� �����
	{
		if (Width * 0.5 - Width * 0.1 < i && Width * 0.5 + Width * 0.1 > i)
		{
			i = Width * 0.45;
			HideInd(&i);
			i = Width * 0.6;
		}
		MoveToEx(hdc, X + i, Y + Height / 2, NULL);
		LineTo(hdc, X + i, Y + Height / 4);
	}
	DeleteObject(SelectObject(hdc, pen));
}
void Clocks::EnergyBar() //������� ��������� ����� �������
{
	HPEN pen = CreatePen(PS_SOLID, 4, RGB(0, 255, 0));
	SelectObject(hdc, pen);
	MoveToEx(hdc, X, Y + 5, NULL);
	switch (LivesStat(0))
	{
	case 4:
		LineTo(hdc, X + 150, Y + 5);
		break;
	case 3:
		LineTo(hdc, X + 100, Y + 5);
		break;
	case 2:
		LineTo(hdc, X + 75, Y + 5);
		break;
	case 1:
		LineTo(hdc, X + 35, Y + 5);
		break;
	case 0:
		LineTo(hdc, X + 10, Y + 5);
	}
	DeleteObject(SelectObject(hdc, pen));
}
void Clocks::HideInd(int* i) //�������� ����� �����
{
	HPEN pen = CreatePen(PS_SOLID, 4, RGB(169, 169, 169)); //������� ���� �������
	SelectObject(hdc, pen);
	for (*i = Width * 0.25; *i < Width * 0.75; *i += Width * 0.1) //������ ����� �� �����
	{
		if (Width * 0.5 - Width * 0.1 < *i && Width * 0.5 + Width * 0.1 > *i)
		{
			*i = Width * 0.45;
			Ellipse(hdc, X + *i - radius, Y + Height / 2 - radius, X + *i + radius, Y + Height / 2 + radius); //������ ����� �� �������� �������
			Ellipse(hdc, X + *i - radius, Y + Height / 4 - radius, X + *i + radius, Y + Height / 4 + radius);
			*i = Width * 0.6;
		}
	}
	DeleteObject(SelectObject(hdc, pen));
}
void Clocks::ShowInd(int* i) //�������� ����� �����
{
	if (Width * 0.5 - Width * 0.1 < *i && Width * 0.5 + Width * 0.1 > *i)
	{
		*i = Width * 0.45;
		Ellipse(hdc, X + *i - radius, Y + Height / 2 - radius, X + *i + radius, Y + Height / 2 + radius); //������ ����� �� �������� �������
		Ellipse(hdc, X + *i - radius, Y + Height / 4 - radius, X + *i + radius, Y + Height / 4 + radius);
		*i = Width * 0.6;
	}
}
Clocks::Clocks(int initX, int initY, int NHeight, int NWidth) :Point(initX, initY)
{
	Lives = 4;
	Points = 0;
	X = initX;
	Y = initY;
	Height = NHeight;
	Width = NWidth;
	radius = 5;
}

int Clocks::TakePoint(int value) //������ �������� � �������� ����
{
	Points += value;
	return Points; //������� ����� ����
}
void Clocks::Hide()
{
	RECT r; //����������� ��������������, ��� ��������� ������� FillRect
	r.left = X;
	r.right = X + Width;
	r.bottom = Y;
	r.top = Y + Height;
	FillRect(hdc, &r, (HBRUSH)CreateSolidBrush(RGB(255, 255, 255)));
}
void Clocks::Expand(int value) //��������� ���� �� ������
{
	Hide(); //��������
	if (Height > 75 or value > 0)
		Height += value / 2;
	if (Width > 75 or value > 0)
		Width += value / 2;
	X -= value / 2;
	Y -= value / 2;
	Show(); //��������
}
void Clocks::Reduce(int value) //��������� ������ ����� �� ������
{
	Expand(-value);
}
int Clocks::SizeX() //���������� ������ �����
{
	return X + Width;
}
int Clocks::SizeY() //���������� ������ �����
{
	return Y + Height;
}
int Clocks::LivesStat(int value) //������� �������
{
	Lives += value;

	if (value == 4) //���� ������ �������
	{
		Lives = value; //������������ ��� �����
	}
	return Lives;
}

void Clocks::BuzzerColor()
{
	RECT r;
	r.left = X;
	r.right = X + Width;
	r.bottom = Y;
	r.top = Y + Height;
	FillRect(hdc, &r, (HBRUSH)CreateSolidBrush(RGB(169, 169, 169)));
}
void Frame::Show()
{
	HPEN pen = CreatePen(PS_SOLID, 4, RGB(0, 0, 0)); //������ ���� ���������
	SelectObject(hdc, pen);
	Rectangle(hdc, X - 5, Y + Height + 5, X + Width + 5, Y - 5); //�������� ������������� ���������
	Clocks::Show();
	DeleteObject(SelectObject(hdc, pen));
}
Frame::Frame(int initX, int initY, int NHeight, int NWidth) :Clocks(initX, initY, NHeight, NWidth)
{
	X = initX;
	Y = initY;
	Height = NHeight;
	Width = NWidth;
}
void Frame::Hide()
{
	RECT r;
	r.left = X - 20;
	r.right = X + Width + 20;
	r.bottom = Y - 20;
	r.top = Y + Height + 20;
	FillRect(hdc, &r, (HBRUSH)CreateSolidBrush(RGB(255, 255, 255)));
}

Enemy::Enemy(int initX, int initY) :Point(initX, initY)
{
	Visible = false;
	friendorfoe = 0;
}
void Enemy::Spawn()
{

	if (Visible == false) //���� ����������� ������� �� ������ ���, �� ������� ����� ������
	{
		friendorfoe = rand() % 100 + 0; //�������� ����� ��� �����
		X = rand() % 1920 + 0; //���������� ������
		Y = 0;
		Visible = true;
	}
}

void Enemy::MoveTo(int NewX, int NewY)
{
	Hide();
	Y += NewY;
	if (Y >= 1300) //������� �� �� ������� ������
		Visible = false;
	Show();
	Sleep(10); //������ ������� ���� �������� �� ������
}

void Enemy::Show() //������������ �������
{

	HBRUSH brush;
	if (friendorfoe >= 50) //����
		brush = CreateSolidBrush(RGB(255, 0, 0));

	else //����
		brush = CreateSolidBrush(RGB(0, 255, 0));

	SelectObject(hdc, brush);
	Ellipse(hdc, X - 20, Y - 20, X + 20, Y + 20);
	DeleteObject(SelectObject(hdc, brush));

}

void Enemy::Hide() //������ �������
{
	HPEN pen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
	SelectObject(hdc, pen);
	HBRUSH  brush = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(hdc, brush);

	Ellipse(hdc, X - 20, Y - 20, X + 20, Y + 20);
	DeleteObject(SelectObject(hdc, brush));
	DeleteObject(SelectObject(hdc, pen));

}

int Enemy::returnfriend() //��������� ������ �������
{
	return friendorfoe;
}

void Healer::Spawn()
{
	if (Visible == false) //������ ��������� ������ ������ �������
	{
		X = rand() % 1920 + 0;
		Y = rand() % 1080 + 0;
		Visible = true;
	}

}
void Healer::Hide() //������� ������������ ������� �����, ����� ������ ��
{

	HBRUSH brush = CreateSolidBrush(RGB(255, 255, 255));

	RECT r{ X, Y, X + size, Y + size };
	FillRect(hdc, &r, brush);
	Y = 10000;
	DeleteObject(brush);
}
Healer::Healer(int initX, int initY, int NHeight, int NWidth) :Point(initX, initY) //����������� �������

{
	size = 100;
	ressurection = 3;
}

void Healer::Show() //��������� �������
{
	HBRUSH brush = CreateSolidBrush(RGB(94, 33, 0));

	RECT r{ X, Y, X + size, Y + size };
	FillRect(hdc, &r, brush);

	brush = CreateSolidBrush(RGB(255, 255, 255));
	Ellipse(hdc, X + size / 6 - size / 20, Y + size / 6 - size / 20, X + 5 * size / 6 + size / 20, Y + 5 * size / 6 + size / 20);

	brush = CreateSolidBrush(RGB(205, 0, 0));

	r.left = X + size / 2 - size / 10;
	r.top = Y + size / 6;
	r.right = X + size / 2 + size / 10;
	r.bottom = Y + 5 * size / 6;
	FillRect(hdc, &r, brush);

	r.left = X + size / 6;
	r.top = Y + size / 2 - size / 10;
	r.right = X + 5 * size / 6;
	r.bottom = Y + size / 2 + size / 10;
	FillRect(hdc, &r, brush);
	DeleteObject(brush);
}

int Healer::Ressurect() //���������� ����� ����� ����������� ��� ������ �������
{
	return ressurection;
}
void Healer::DelChance() //������� � ���� ���� ������ ����� ������� ����� ��������� ����������
{
	ressurection = 0;
}
void Healer::GetScoreInExchange() //��������������� ���� ��������� �������
{
	ressurection++;
}

void SickClocks::EnergyBar()
{
	HPEN pen = CreatePen(PS_SOLID, 4, RGB(255, 92, 205));
	SelectObject(hdc, pen);
	MoveToEx(hdc, X, Y + 5, NULL);
	DeleteObject(pen);
}
SickClocks::SickClocks(int initX, int initY, int NHeight, int NWidth) :Frame(initX, initY, NHeight, NWidth)
{
	Lives = 1;
	X = initX;
	Y = initY;
	Height = NHeight;
	Width = NWidth;
}
void SickClocks::BuzzerColor() //������� ������� ������ "������� �����"
{
	RECT r;
	r.left = X;
	r.right = X + Width;
	r.bottom = Y;
	r.top = Y + Height;
	FillRect(hdc, &r, (HBRUSH)CreateSolidBrush(RGB(0, 255, 255)));
}

FireClocks::FireClocks(int initX, int initY, int NHeight, int NWidth) :Frame(initX, initY, NHeight, NWidth)
{
	Lives = 1;
	X = initX;
	Y = initY;
	Height = NHeight;
	Width = NWidth;
}

void FireClocks::BuzzerColor() //������� ������� ����� ������� ������, "�������� ����"
{
	RECT r;
	r.left = X;
	r.right = X + Width;
	r.bottom = Y;
	r.top = Y + Height;
	FillRect(hdc, &r, (HBRUSH)CreateSolidBrush(RGB(255, 0, 0)));
}

void FireClocks::EnergyBar() //������� ��������� ������� �����
{
	HPEN pen = CreatePen(PS_SOLID, 4, RGB(0, 0, 255));
	SelectObject(hdc, pen);
	MoveToEx(hdc, X, Y + 5, NULL);
	DeleteObject(pen);
}

void WiseEnemy::MoveTo(int NewX, int NewY) //������� ������������ �������������� �����
{
	Hide();
	NewY = 5;
	Y += NewY;
	NewX = sin(Y * 3.14 / 180) * 20; //������� ������� ���������
	X += NewX;
	if (Y >= 1300) //������� �� �� ������� ������
		Visible = false;
	Show();
	Sleep(10);

}
WiseEnemy::WiseEnemy(int initX, int initY) :Enemy(initX, initY) //����������� �������������� �����
{
	Visible = false; //�������� ��������� 
	friendorfoe = 0; //��� ������� ����/����
}
