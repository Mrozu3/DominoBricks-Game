#pragma once

#include "Player.h"

using namespace sf;

class Game
{
    private: 
        RenderWindow *window;

    public:
        Game(RenderWindow *window);
        virtual ~Game();

        //Komentarz
        inline RenderWindow& getWindow() {return *this->window;}




        //Funkcje
        void Update();
        void Draw();
};