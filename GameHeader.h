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



class Point :public Location //точка, первый видимый объект
{
protected:
	bool Visible;
public:
	Point(int initX, int initY);
	bool IsVisible();
	virtual void Spawn(); //спавн точки
	virtual int returnfriend();
	virtual void setcolor();
	virtual void MoveTo(int NewX, int NewY); //перемещает точку
	virtual void Show(); //показать
	virtual void Hide(); //закрасить
};


class IClocks //интерфейс часов
{
public:
	virtual void ShowTime() = 0; //показать время (дисплей)
	virtual void HideTime() = 0; //(спрятать дисплей)
	virtual void BuzzerColor() = 0; //закрашивает будильник каким-то цветом
	virtual void ShowInd(int* i) = 0; //показывает точки на дисплее
	virtual void HideInd(int* i) = 0; //закрашивает точки на дисплее
	virtual void EnergyBar() = 0; //полоска жизни
};


class Clocks :public IClocks, public Point //часы 
{
protected:
	int Lives; //количество жизней
	int Points; //количество очков
	int Height; //высота часов
	int radius; //радиус энергий
	int Width; //ширина часов
public:
	Clocks(int initX, int initY, int NHeight, int NWidth);
	int TakePoint(int value); //получить очко энергии
	int LivesStat(int value); //возвращает, уменьшает и увеличивает переменную жизней
	int SizeX(); //возвращает размер по X+ширина
	int SizeY(); //возвращает размер по Y+высота
	virtual void Hide() override; //спрятать часы
	virtual void Show() override; //показать
	virtual void ShowTime() override; //см интерфейс
	virtual void BuzzerColor() override;
	virtual void EnergyBar() override;
	virtual void ShowInd(int* i) override;
	virtual void HideInd(int* i) override;
	virtual void HideTime() override;
	virtual void Expand(int value); //метод увеличения часов
	virtual void Reduce(int value); //метод уменьшения часов

};

class Frame : public Clocks //класс рамки, обрамляющий часы
{
public:
	Frame(int iniX, int initY, int NHeight, int NWidth); //конструктор рамки
	virtual void Show() override; //показать рамку
	virtual void Hide() override; //спрятать рамку
};

class Enemy :public Point //обычный противник, двигающийся по прямой
{
protected:
	int friendorfoe; //друг или враг
public:
	Enemy(int initX, int initY);
	virtual void MoveTo(int NewX, int NewY) override; //перемещение энергии по прямой
	virtual void Show() override; //показать энергию
	void Hide(); //спрятать энергию
	virtual void Spawn() override; //спавнит энергию
	virtual int returnfriend() override; //возвращает статус энергии


};
class WiseEnemy :public Enemy //противник, двигающийся по синусоиде
{
public:
	WiseEnemy(int iniX, int initY);
	virtual void MoveTo(int NewX, int NewY) override; //двигает энергию по синусоиде
};


class Healer :public Point //аптечка
{
protected:
	int size; //размер аптечки
	int ressurection; //шанс появления аптечки
public:
	Healer(int initX, int initY, int NHeight, int NWidth);
	void Spawn();
	int Ressurect(); //исцелить будильник
	void DelChance(); //удалить шанс появления аптечки
	void GetScoreInExchange(); //всю схваченную энергию пускает на восстановление аптечки
	virtual void Show() override;
	void Hide();

};

class FireClocks :public Frame //огненные часы дают скорость
{
public:
	FireClocks(int initX, int initY, int NHeight, int NWidth);
	virtual void BuzzerColor() override; //цвет часов
	virtual void EnergyBar() override; //цвет шкалы энергии

};

class SickClocks :public Frame //больные часы, отнимают скорость, наносят урон
{
public:
	SickClocks(int initX, int initY, int NHeight, int NWidth);
	virtual void BuzzerColor() override; //цвет часов
	virtual void EnergyBar() override; //цвет энергии
};
