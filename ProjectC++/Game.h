#pragma once
//Dolaczanie
#include "Enemy.h"

//Klasa narzedna jako serce/silnik gry

using namespace sf;
using namespace std;

//Klasa Game
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
		//Wrogowie
		vector<Enemy> wrogowie;		
		Boss boss;
		
	//Prywatna struktura
	void inicZmienne();
	void inicOkno();
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

	/*Obiekty gry sprzed zmiany na dynamicznych
	RectangleShape wrog;
	vector<RectangleShape> wrogowie;
	*/

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

	//Accessor
	const bool otwarteOkno() const;
	
	//Funkcje obslugi
	void Nasluch();
	void render();
	void update();
	void updateMyszka();
	int zwrocPunkty();

	//Accessor
	const bool gameOvercontrol() const;

	//Funkcje wrogow
	void spawnWrog();
	void renderWrog();
	void updateWrog();
	void liveBoss();
	//Dodatki
	void updateTekst();
	void renderTekst();
};

