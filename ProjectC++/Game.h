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

//Klasa nadrzêdna jako serce/silnik gry

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

	//Prywatna struktura
	void inicZmienne();
	void inicOkno();
	void inicWrog();
	void iniCzcionka();
	void iniTekst();

	//Mechanizmy
		//Wynik, zawsze dodatni wynik, koniec gry
		int punkty;
		bool gameOver;
		//Wrogowie
		float spawnTime;
		float spawnTimeMax;
		int maxWrogow;
		//Myszka oszusta
		int Trzymam;

	//Obiekty gry
	RectangleShape wrog;
	vector<RectangleShape> wrogowie;
	//Czcionka i tekst
	Font czcionka;
	Text tekst;


	//Pozycja myszki
	Vector2i pozycjaMyszkiOkno;
	Vector2f pozycjaMyszkiWidok;

public: 

	//Konstruktory i destruktory
	Game();
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
	//Dodatki
	void updateTekst();
	void renderTekst();
};

