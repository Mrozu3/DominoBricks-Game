//Dolaczanie
#include "Game.h"

using namespace sf;
using namespace std;

int main()
{
	//Do losowych liczb
	srand(static_cast<unsigned>(time(NULL)));

	//Zalaczamy gre
	Game game;
	
	//Wywoluje metode kopiujaca
	Boss boss;
	Boss boss2 = boss;

	//Petla gry
	while (game.otwarteOkno() && !game.gameOvercontrol())
	{
		    //Na biezaco
	  	    game.update();

			//Render
			game.render();
	}

	//Zamykanie
	return 0;
}