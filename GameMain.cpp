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


	int speed = 15; //параметр скорости перемещения главного героя
	bool flag = false; //проверка на взятую аптечку
	Frame Buzzer(960, 600, 80, 160); //объект главный герой

	Healer heal(0, 0, 0, 0); //объект аптечка

	Point* rounds[3]; //массив объектов, для перемещения врагов на экране
	Enemy round(0, 0); //обычный противник, двигающийся по прямой 
	WiseEnemy sinus(0, 0); //противник двигающийся по синусоиде
	SickClocks Object(900, 1000, 80, 160); //больные часы (ловушка)
	FireClocks Fire(500, 1000, 80, 160); //часы-помощники 

	rounds[0] = &round;
	rounds[1] = &sinus;
	if (hwnd != NULL)
	{
		hdc = GetDC(hwnd);
		while (hdc != 0)
		{
			if (Buzzer.LivesStat(0) < 0) //пока не потратил все жизни
				hdc = 0;
			for (int i = 0; i < 2; i++)
				rounds[i]->Spawn(); //спавн двух шариков 
			if (Buzzer.LivesStat(0) == 0 and heal.Ressurect() == 3) //если 0 жизней, но есть 3 очка возрождения
			{
				flag = true;
				heal.Spawn(); //спавн аптечки
				heal.Show(); //показать аптечку
				heal.DelChance(); //обнулить шанс выпадения второй аптечки
			}
			if ((heal.GetX() >= Buzzer.GetX() and heal.GetX() <= Buzzer.SizeX()) and (heal.GetY() >= Buzzer.GetY() and heal.GetY() <= Buzzer.SizeY())) //если поймал аптечку
			{
				Buzzer.LivesStat(4); //восстановить жизни
				heal.Hide(); //спрятать аптечку
				flag = false;
			}
			for (int i = 0; i < 2; i++) //функция столкновения часов с иными объектами
			{
				rounds[i]->MoveTo(0, 5);
				if ((rounds[i]->GetX() >= Buzzer.GetX() and rounds[i]->GetX() <= Buzzer.SizeX()) and (rounds[i]->GetY() >= Buzzer.GetY() and rounds[i]->GetY() <= Buzzer.SizeY()) and rounds[i]->returnfriend() >= 50) //если столкнулся с шариком
				{
					Buzzer.Reduce(10); //красный шарик уменьшил часы
					rounds[i]->MoveTo(0, 1300); //улетел за границы экрана
					Buzzer.HideInd(0);
					Buzzer.LivesStat(-1); //уменьшил количество жизней
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
			if (Buzzer.TakePoint(0) == 5 and flag == false) //если у главного героя 5 очков, то показать огненные часы и больные часы

			{
				Fire.Show();
				Object.Show();
			}
			if ((Object.GetX() >= Buzzer.GetX() and Object.GetX() <= Buzzer.SizeX()) and (Object.GetY() >= Buzzer.GetY() and Object.GetY() <= Buzzer.SizeY())) //если врезался в огненные часы
			{
				speed -= 10; //снизить скорость на 10
				Buzzer.TakePoint(-2); //уменьшить количество очков на 2
				Buzzer.LivesStat(-3); //уменьшить количество жизней на 3
				Object.Hide(); //спрятать огненные часы и больные часы

				Fire.Hide();
				Object.MoveTo(-900, -1000); //переместить их за игровую область
				Fire.MoveTo(-500, 1000);
				flag = true;
			}
			if ((Fire.GetX() >= Buzzer.GetX() and Fire.GetX() <= Buzzer.SizeX()) and (Fire.GetY() >= Buzzer.GetY() and Fire.GetY() <= Buzzer.SizeY()))
			{
				if (speed < 25) //увеличить скорость
					speed += 10;
				Object.MoveTo(-900, -1000); //переместить огненные и больные часы за область экрана
				Fire.MoveTo(-500, 1000);
				Fire.Hide();
				Object.Hide();
				flag = true;
			}
			if (KEY_DOWN(37)) //стрелка влево
				Buzzer.MoveTo(-speed, 0);
			if (KEY_DOWN(38)) //стрелка вверх
				Buzzer.MoveTo(0, -speed);
			if (KEY_DOWN(39)) //стрелка вправо
				Buzzer.MoveTo(speed, 0);
			if (KEY_DOWN(40)) //стрелка вниз
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
