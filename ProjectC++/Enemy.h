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
#include <sstream>

using namespace sf;

//Klasa wrogow
class Enemy
{
protected:
	//Zmienne dla wrogow
	int hp;
	int punkty;	
	
public:		
	//Konstruktor
	Enemy(Vector2f wymiary = Vector2f(300, 400), int hp = 1, int punkty = 1);
	//Zadefinowanie ksztaltu
	RectangleShape ksztalt;
	
	//Metoda wirtualna i klasa abstrakcyjna
	void virtual zmienKolor();	
	void inicWrog();
	int zwrocPunkty();
};

//Klasa boss dziedziwczy po Enemy
class Boss : public Enemy
{

private:
	int obrazenia;	

public:
	Boss(int hp = 10, int punkty = 5, int obrazenia = 10);
	Boss(const Boss& boss);
	
	//Przeciazenie operatorow
	void operator-(int obrazenia);

	//Nadpisanianie 
	void zmienKolor();

	int zwrocObrazenia();	
	int zwrocHp();
};

