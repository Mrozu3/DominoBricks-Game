#pragma once

//Biblioteki SFML
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Window.hpp"
#include "SFML/Network.hpp"

//Biblioteki strumieni we/wy 
#include <iostream>
#include <vector>
#include <ctime>

using namespace sf;

//Klasa wrogow
class Enemy
{
protected:
	//Zmienne dla wrogow
	int hp;
	int punkty;	
	
public:		
	//Konstruktor wroga
	Enemy(Vector2f wymiary = Vector2f(300, 400), int hp = 1, int punkty = 1);
	//Zadefinowanie ksztaltu
	RectangleShape ksztalt;
	
	//Metoda wirtualna i klasa abstrakcyjna
	void virtual zmienKolor();	
	//Zwracanie punktow dla wroga
	int zwrocPunkty();
};

//Klasa boss dziedziczy po Enemy
class Boss : public Enemy
{

//Dodaje obrazenia dla boss-a
private:
	int obrazenia;	

public:
	//Dziedziczy hp i punkty po wrogu, nadpisuje im wartosc, dodaje obrazenia
	Boss(int hp = 10, int punkty = 5, int obrazenia = 10);
	Boss(const Boss& boss);
	
	//Przeciazenie operatorow
	void operator-(int obrazenia);

	//Nadpisanianie 
	void zmienKolor();
	//Obrazenia i HP wroga
	int zwrocObrazenia();	
	int zwrocHp();
};

