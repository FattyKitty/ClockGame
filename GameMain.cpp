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


	int speed = 15; //speed movement parameter of hero by default
	bool flag = false; //check for used medicine
	Frame Buzzer(960, 600, 80, 160); //hero object

	Healer heal(0, 0, 0, 0); //medicine object

	Point* rounds[3]; //enemies
	Enemy round(0, 0); //usual enemy, moving straight
	WiseEnemy sinus(0, 0); //enemy, which moves by sinus law
	SickClocks Object(900, 1000, 80, 160); //sick watches (trap)
	FireClocks Fire(500, 1000, 80, 160); //helper

	rounds[0] = &round;
	rounds[1] = &sinus;
	if (hwnd != NULL)
	{
		hdc = GetDC(hwnd);
		while (hdc != 0)
		{
			if (Buzzer.LivesStat(0) < 0) //while has lives
				hdc = 0;
			for (int i = 0; i < 2; i++)
				rounds[i]->Spawn(); //spawn two balls
			if (Buzzer.LivesStat(0) == 0 and heal.Ressurect() == 3) //if 0 lives, spawn a medicine
			{
				flag = true;
				heal.Spawn(); //spawn medicine
				heal.Show(); //show medicine
				heal.DelChance(); //second medkit will not spawn
			}
			if ((heal.GetX() >= Buzzer.GetX() and heal.GetX() <= Buzzer.SizeX()) and (heal.GetY() >= Buzzer.GetY() and heal.GetY() <= Buzzer.SizeY())) //if catched medkit
			{
				Buzzer.LivesStat(4); //restore lives
				heal.Hide(); //hide medkit
				flag = false;
			}
			for (int i = 0; i < 2; i++) //collision with other objects
			{
				rounds[i]->MoveTo(0, 5);
				if ((rounds[i]->GetX() >= Buzzer.GetX() and rounds[i]->GetX() <= Buzzer.SizeX()) and (rounds[i]->GetY() >= Buzzer.GetY() and rounds[i]->GetY() <= Buzzer.SizeY()) and rounds[i]->returnfriend() >= 50) //collided with ball
				{
					Buzzer.Reduce(10); //red ball reduces size of clocks
					rounds[i]->MoveTo(0, 1300); //flew away from screen
					Buzzer.HideInd(0);
					Buzzer.LivesStat(-1); //shorts amount of lives
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
			if (Buzzer.TakePoint(0) == 5 and flag == false) //if hero has 5 points of energy show sick and fire clocks

			{
				Fire.Show();
				Object.Show();
			}
			if ((Object.GetX() >= Buzzer.GetX() and Object.GetX() <= Buzzer.SizeX()) and (Object.GetY() >= Buzzer.GetY() and Object.GetY() <= Buzzer.SizeY())) //collided with sick clocks
			{
				speed -= 10; //reduce speed by 10
				Buzzer.TakePoint(-2); //score reduce by 10
				Buzzer.LivesStat(-3); //lives score reduce by 3
				Object.Hide(); //hide fire and sick clocks

				Fire.Hide();
				Object.MoveTo(-900, -1000); //move them awayy from gaming zone
				Fire.MoveTo(-500, 1000);
				flag = true;
			}
			if ((Fire.GetX() >= Buzzer.GetX() and Fire.GetX() <= Buzzer.SizeX()) and (Fire.GetY() >= Buzzer.GetY() and Fire.GetY() <= Buzzer.SizeY())) //collided with fire clocks
			{
				if (speed < 25) //adds some speed
					speed += 10;
				Object.MoveTo(-900, -1000); //move sick and fire watches away from the screen
				Fire.MoveTo(-500, 1000);
				Fire.Hide();
				Object.Hide();
				flag = true;
			}
			if (KEY_DOWN(37)) //left arrow
				Buzzer.MoveTo(-speed, 0);
			if (KEY_DOWN(38)) //up arrow
				Buzzer.MoveTo(0, -speed);
			if (KEY_DOWN(39)) //right arrow
				Buzzer.MoveTo(speed, 0);
			if (KEY_DOWN(40)) //down arrow
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
