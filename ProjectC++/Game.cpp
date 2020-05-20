//Deklaracje
#include "Game.h"

Game::Game(RenderWindow* window)
{
    //Limit klatek po wskazniku
    this->window = window;  
    this->window->setFramerateLimit(60);

    //Tekstura gracza
    TeksturaGracza.loadFromFile("Tekstury/jet.png");

    //Stworzenie gracza
    gracz = new Gracz(&this->TeksturaGracza);


}

Game::~Game()
{
    //Usuniecie gracza
    delete gracz;
}
 
void Game::Update()
{
    gracz->Update();
}

void Game::Draw()
{
    window->clear();

    gracz->Draw(*window);

    window->display();
}