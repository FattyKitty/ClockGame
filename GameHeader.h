#pragma once

//clocks == buzzer 
//sometimes i call it one way, sometimes another
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



class Point :public Location //point, first visible object
{
protected:
	bool Visible;
public:
	Point(int initX, int initY);
	bool IsVisible();
	virtual void Spawn(); //spawn point
	virtual int returnfriend();
	virtual void setcolor();
	virtual void MoveTo(int NewX, int NewY); //moves point
	virtual void Show(); //show it			//
											// it means - point
	virtual void Hide(); //hide it			//
};


class IClocks //clocks interface
{
public:
	virtual void ShowTime() = 0; //show time (display)
	virtual void HideTime() = 0; //hide display
	virtual void BuzzerColor() = 0; //paints clock with some color
	virtual void ShowInd(int* i) = 0; //shows dots on display
	virtual void HideInd(int* i) = 0; //shows dots on display
	virtual void EnergyBar() = 0; //live line
};


class Clocks :public IClocks, public Point //clock
{
protected:
	int Lives; //amount of lives
	int Points; //score points
	int Height; //Height of clock
	int radius; //radius of energy
	int Width; //width of clock
public:
	Clocks(int initX, int initY, int NHeight, int NWidth);
	int TakePoint(int value); //get energy score
	int LivesStat(int value); //returns amount of lives left
	int SizeX(); //returns X value + width
	int SizeY(); //returns Y value + height
	virtual void Hide() override; //hide clock
	virtual void Show() override; //show clock
	virtual void ShowTime() override; // shows time on clock
	virtual void BuzzerColor() override;
	virtual void EnergyBar() override;
	virtual void ShowInd(int* i) override;
	virtual void HideInd(int* i) override;
	virtual void HideTime() override;
	virtual void Expand(int value); //expands clocks
	virtual void Reduce(int value); //reduces clocks

};

class Frame : public Clocks //border around buzzer
{
public:
	Frame(int iniX, int initY, int NHeight, int NWidth); 
	virtual void Show() override; //show border
	virtual void Hide() override; //hide border
};

class Enemy :public Point //usual enemy
{
protected:
	int friendorfoe; //friend or foe
public:
	Enemy(int initX, int initY);
	virtual void MoveTo(int NewX, int NewY) override; //moves by line 
	virtual void Show() override; //show energy
	void Hide(); //hide energy
	virtual void Spawn() override; //spawns energy
	virtual int returnfriend() override; //returns energy status


};
class WiseEnemy :public Enemy //enemy which moves by sinus
{
public:
	WiseEnemy(int iniX, int initY);
	virtual void MoveTo(int NewX, int NewY) override; //moves energy by sinus law
};


class Healer :public Point //аптечка
{
protected:
	int size; //size of medkit
	int ressurection; //medkit's chance to appear
public:
	Healer(int initX, int initY, int NHeight, int NWidth);
	void Spawn();
	int Ressurect(); //heal clocks (hero)
	void DelChance(); //delete chance of medkit spawn
	void GetScoreInExchange(); //energy goes to restore medkit
	virtual void Show() override;
	void Hide();

};

class FireClocks :public Frame //fire buzzer, gives u speed
{
public:
	FireClocks(int initX, int initY, int NHeight, int NWidth);
	virtual void BuzzerColor() override; //color of watches
	virtual void EnergyBar() override; //energy line color

};

class SickClocks :public Frame //sick watches, cause damage
{
public:
	SickClocks(int initX, int initY, int NHeight, int NWidth);
	virtual void BuzzerColor() override; //buzzer color
	virtual void EnergyBar() override; //energy color
};
