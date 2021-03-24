#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x0001) ? 1 : 0)
#include <iostream>
//#include <cstdlib>
#include <windows.h>
#include "GameHeader.h"

using namespace std;

HDC hdc;


int main()
{
	system("color F0");
	HWND hwnd = GetConsoleWindow();
	COORD coord;

	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, &coord);


	int speed = 15; //�������� �������� ����������� �������� �����
	bool flag = false; //�������� �� ������ �������
	Frame Buzzer(960, 600, 80, 160); //������ ������� �����

	Healer heal(0, 0, 0, 0); //������ �������

	Point* rounds[3]; //������ ��������, ��� ����������� ������ �� ������
	Enemy round(0, 0); //������� ���������, ����������� �� ������ 
	WiseEnemy sinus(0, 0); //��������� ����������� �� ���������
	SickClocks Object(900, 1000, 80, 160); //������� ���� (�������)
	FireClocks Fire(500, 1000, 80, 160); //����-��������� 

	rounds[0] = &round;
	rounds[1] = &sinus;
	if (hwnd != NULL)
	{
		hdc = GetDC(hwnd);
		while (hdc != 0)
		{
			if (Buzzer.LivesStat(0) < 0) //���� �� �������� ��� �����
				hdc = 0;
			for (int i = 0; i < 2; i++)
				rounds[i]->Spawn(); //����� ���� ������� 
			if (Buzzer.LivesStat(0) == 0 and heal.Ressurect() == 3) //���� 0 ������, �� ���� 3 ���� �����������
			{
				flag = true;
				heal.Spawn(); //����� �������
				heal.Show(); //�������� �������
				heal.DelChance(); //�������� ���� ��������� ������ �������
			}
			if ((heal.GetX() >= Buzzer.GetX() and heal.GetX() <= Buzzer.SizeX()) and (heal.GetY() >= Buzzer.GetY() and heal.GetY() <= Buzzer.SizeY())) //���� ������ �������
			{
				Buzzer.LivesStat(4); //������������ �����
				heal.Hide(); //�������� �������
				flag = false;
			}
			for (int i = 0; i < 2; i++) //������� ������������ ����� � ����� ���������
			{
				rounds[i]->MoveTo(0, 5);
				if ((rounds[i]->GetX() >= Buzzer.GetX() and rounds[i]->GetX() <= Buzzer.SizeX()) and (rounds[i]->GetY() >= Buzzer.GetY() and rounds[i]->GetY() <= Buzzer.SizeY()) and rounds[i]->returnfriend() >= 50) //���� ���������� � �������
				{
					Buzzer.Reduce(10); //������� ����� �������� ����
					rounds[i]->MoveTo(0, 1300); //������ �� ������� ������
					Buzzer.HideInd(0);
					Buzzer.LivesStat(-1); //�������� ���������� ������
				}
				else if ((rounds[i]->GetX() >= Buzzer.GetX() and rounds[i]->GetX() <= Buzzer.SizeX()) and (rounds[i]->GetY() >= Buzzer.GetY() and rounds[i]->GetY() <= Buzzer.SizeY()))
				{
					if (heal.Ressurect() == 3)
					{
						Buzzer.Expand(15);
						Buzzer.TakePoint(1);
					}
					else
						heal.GetScoreInExchange();
					rounds[i]->MoveTo(0, 1300);
				}
			}
			if (Buzzer.TakePoint(0) == 5 and flag == false) //���� � �������� ����� 5 �����, �� �������� �������� ���� � ������� ����

			{
				Fire.Show();
				Object.Show();
			}
			if ((Object.GetX() >= Buzzer.GetX() and Object.GetX() <= Buzzer.SizeX()) and (Object.GetY() >= Buzzer.GetY() and Object.GetY() <= Buzzer.SizeY())) //���� �������� � �������� ����
			{
				speed -= 10; //������� �������� �� 10
				Buzzer.TakePoint(-2); //��������� ���������� ����� �� 2
				Buzzer.LivesStat(-3); //��������� ���������� ������ �� 3
				Object.Hide(); //�������� �������� ���� � ������� ����

				Fire.Hide();
				Object.MoveTo(-900, -1000); //����������� �� �� ������� �������
				Fire.MoveTo(-500, 1000);
				flag = true;
			}
			if ((Fire.GetX() >= Buzzer.GetX() and Fire.GetX() <= Buzzer.SizeX()) and (Fire.GetY() >= Buzzer.GetY() and Fire.GetY() <= Buzzer.SizeY()))
			{
				if (speed < 25) //��������� ��������
					speed += 10;
				Object.MoveTo(-900, -1000); //����������� �������� � ������� ���� �� ������� ������
				Fire.MoveTo(-500, 1000);
				Fire.Hide();
				Object.Hide();
				flag = true;
			}
			if (KEY_DOWN(37)) //������� �����
				Buzzer.MoveTo(-speed, 0);
			if (KEY_DOWN(38)) //������� �����
				Buzzer.MoveTo(0, -speed);
			if (KEY_DOWN(39)) //������� ������
				Buzzer.MoveTo(speed, 0);
			if (KEY_DOWN(40)) //������� ����
				Buzzer.MoveTo(0, +speed);
			if (KEY_DOWN(107))
				Buzzer.TakePoint(1);
			if (KEY_DOWN(27) or Buzzer.LivesStat(0) == -1) //escape
				Buzzer.LivesStat(-4);

		}
		system("pause");
		return 0;
	}
}
