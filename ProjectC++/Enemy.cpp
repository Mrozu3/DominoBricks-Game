#include "Enemy.h"


//Wyglad wroga, jego statystyki
Enemy::Enemy(Vector2f wymiary, int hp, int punkty)
{
	this->hp = hp;
	this->punkty = punkty;
	//Wyglad wroga
	this->ksztalt.setSize(Vector2f(50.f, 50.f));
	this->ksztalt.setScale(Vector2f(1.f, 1.f));
	this->ksztalt.setOutlineColor(Color(0, 0, 0, 255));
	this->ksztalt.setOutlineThickness(3.f);
	this->ksztalt.setFillColor(Color::White);	
	this->ksztalt.setPosition(Vector2f(
		static_cast<float>(rand() % static_cast<int>(wymiary.x - this->ksztalt.getSize().x)),
		0
	));

}

//
void Enemy::zmienKolor()
{
	this->ksztalt.setFillColor(Color::White);	
}

void Boss::zmienKolor()
{
	this->ksztalt.setFillColor(Color::Red);
}

//Zwraca punkty
int Enemy::zwrocPunkty()
{
	return this->punkty;
}

//Zwaraca obrazenia
int Boss::zwrocObrazenia()
{
	return this->obrazenia;
}

//Zwraca HP
int Boss::zwrocHp()
{
	return this->hp;
}

//Przeciązenie operatorw ( znajdzie sie obiekt typu boss, po prawiej znajdzie sie liczba, to odejmuje ) 
void Boss::operator-(int obrazenia)
{
	this->hp -= obrazenia;
}

//Dziedziczenie
Boss::Boss(int hp, int punkty, int obrazenia)
	: Enemy(Vector2f(300, 400), 10, punkty)
{	
	this->obrazenia = obrazenia;
	this->zmienKolor();	
}

//Kopiowanie
Boss::Boss(const Boss& boss)
	: Enemy(Vector2f(300, 400), 5, boss.punkty)
{	
	this->obrazenia = boss.obrazenia + 1;
	
	std::cout << "Kopia" << std::endl;
}

