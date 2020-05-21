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

class Enemy
{
private:
	int hp;
	int punkty;	
	
public:	
	Enemy();
	Enemy(int hp, int punkty, Vector2f wymiary);
	//Enemy(Enemy &wrog);
	RectangleShape ksztalt;
	

	void zmienKolor(std::string);
	int zwrocPunkty();
	//!!!!!!!!!!!!!!!!!!!!!!! void virtual wyswietlHp();
	void inicWrog();	
};


class Boss : public Enemy
{
	int obrazenia;

public:
	Boss();
	Boss(int hp, int punkty, int obrazenia);
};

