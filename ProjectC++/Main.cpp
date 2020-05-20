//Deklaracje
#include "Game.h"
#include "Gracz.h"
#include <SFML/Graphics.hpp>

int main()
{

	//Okno gry window
	RenderWindow window(VideoMode(800, 600), "Nazwa Gry", Style::Default);

	//Zainicjowanie gry
	Game game(&window);
	
	CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	//Gra w³¹czona
	while(window.isOpen())
	{
		//Obs³uga zdarzeñ
		Event event;
		while(window.pollEvent(event))
		{
			//Zamkniecie
			if (event.type == Event::Closed) {
				window.close();
			}
			
			//Klikniecie Esc
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
				window.close();
			}
		}

		game.Update();
		game.Draw();
	}
	
	return 0; 
}