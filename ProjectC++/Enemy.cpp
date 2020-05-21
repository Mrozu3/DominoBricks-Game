#include "Enemy.h"

Enemy::Enemy(int hp, int punkty, Vector2f wymiary)
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

//Konstruktor kopiujacy
/*Enemy::Enemy(Enemy& wrog)
{
	this->hp = hp;
	this->punkty = punkty;
	
	this->ksztalt.setPosition(400, 300);
	//Wyglad wroga
	this->ksztalt.setSize(Vector2f(50.f, 50.f));
	this->ksztalt.setScale(Vector2f(1.f, 1.f));
	this->ksztalt.setOutlineColor(Color(0, 0, 0, 255));
	this->ksztalt.setOutlineThickness(3.f);
	this->ksztalt.setFillColor(Color::White);
}*/

/*Boss::Boss(int hp, int punkty, int obrazenia)	
{
	this->obrazenia = obrazenia;
}*/

void Enemy::zmienKolor(std::string kolor)
{
	if (kolor == "red")
	{
		this->ksztalt.setFillColor(Color::Red);
	}
}

/*
void Enemy::inicWrog()
{
//Pozycja wroga
this->setPosition(Vector2f(400, 300));
//Wyglad wroga
this->setSize(Vector2f(50.f, 50.f));
this->setScale(Vector2f(1.f, 1.f));
this->setOutlineColor(Color(0, 0, 0, 255));
this->setOutlineThickness(3.f);
}
*/

