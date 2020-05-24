#pragma once

#include "Enemy.h"

//Klasa narzedna jako serce/silnik gry

using namespace sf;
using namespace std;

class Game
{
private:
	
	//Zmienne render
		//Dynamicznie, zeby moc usuwac
		RenderWindow* okno;
		//Wielkosc
		VideoMode videoMode;
		//Zdarzenie
		Event event;
				
		vector<Enemy> wrogowie;		
		Boss boss;
		
	//Prywatna struktura
	void inicZmienne();
	void inicOkno();
	void inicWrog();
	void iniCzcionka();
	void iniTekst();

	//Mechanizmy
		//Wynik, zawsze dodatni wynik, koniec gry
		int punkty;
		int punkty_cp;
		bool gameOver;
		//Wrogowie
		float spawnTime;
		float spawnTimeMax;
		int shootTimer, shootTimerMax;
		int maxWrogow;
		//Myszka oszusta
		int Trzymam;

	//Obiekty gry

	//RectangleShape wrog;
	//vector<RectangleShape> wrogowie;

	//Czcionka i tekst
	Font czcionka;
	Text tekst;


	//Pozycja myszki
	Vector2i pozycjaMyszkiOkno;
	Vector2f pozycjaMyszkiWidok;

public: 

	//Konstruktory
	Game();
	//Destruktor wirtualny
	virtual ~Game();

	//Kontrolki
	const bool otwarteOkno() const;
	const bool gameOvercontrol() const;

	//Funkcje obslugi
	void Nasluch();
	void update();
	void updateMyszka();
	void render();
	//Funkcje wrogow
	void spawnWrog();
	void updateWrog();
	void renderWrog();
	void isAlive();
	//Dodatki
	void updateTekst();
	void renderTekst();
};

