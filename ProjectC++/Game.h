#pragma once

//Deklaracje
#include "Gracz.h"

class Game
{
private:
	RenderWindow *window;

	Gracz *gracz;
	Texture TeksturaGracza;

public:
	Game(RenderWindow *window);
	virtual ~Game();

	// 
	inline RenderWindow& getWindow() { return *this->window; }

	//Funkcje
	void Move();
	void Update();
	void Draw();
};

