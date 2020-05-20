#pragma once

//Biblioteki SFML
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
//Biblioteki strumieni we/wy 
#include <iostream>

using namespace sf;

class Gracz
{
private:
	//Tekstury, ksztalty
	Texture *tekstura;
	Sprite ksztalt;
	RectangleShape hitbox;

	//Zmienne lvl
	int lvl;
	int exp;
	int expNext;

	//Zmienne ¿ycie
	int HP;
	int MaxHP;
	int damage;
	int MaxDamage;

	//Wynik
	int score;

public:
	Gracz(Texture* tekstura );
	virtual ~Gracz();

	void Poruszanie();
	void Update();
	void Draw(RenderTarget &target);
};

