//Deklaracje
#include "Game.h"

using namespace sf;
using namespace std;


//Konstruktory i destruktory
Game::Game()
{
    //Inicjowanie 
    this->inicZmienne();
    this->inicOkno();	
	this->iniCzcionka();
	this->iniTekst();	
}

Game::~Game()
{
    delete this->okno;	
}

//Funkcje publiczne

//Sprwadza czy gra uruchomina
const bool Game::otwarteOkno() const
{
    return this->okno->isOpen();
}

void Game::Nasluch()
{
	//Nasluchiwanie zdarzenia
	while (this->okno->pollEvent(this->event))
	{
		//typ zdarzenia
		switch (this->event.type)
		{
			//Jesli x 
		case Event::Closed:
			this->okno->close();
			break;

			//Jesli Esc
		case Event::KeyPressed:
			if (this->event.key.code == Keyboard::Escape) { this->okno->close(); }
			break;
		}
	}
}

const bool Game::gameOvercontrol() const
{
	return this->gameOver;
}

//Aktualizuje to co ma sie dziac na ekranie
void Game::update()
{

	this->Nasluch();

	//Jesli punkty nie spadly ponizej zera
	if (this->gameOver == false) {

		this->updateMyszka();

		this->updateWrog();

		this->updateTekst();

	}
	
	//Jesli punkty spadly ponizej 0
	if (this->punkty <= 0) {

		this->gameOver = true;
	}

	if (this->punkty > 120) {

		this->maxWrogow = 6;
	}

}

//Pozycja myszki wobec okna
void Game::updateMyszka()
{
	//Badanie pozycji myszki
	this->pozycjaMyszkiOkno = Mouse::getPosition(*this->okno);
	//Koordynaty myszki na mapie pikseli
	this->pozycjaMyszkiWidok = this->okno->mapPixelToCoords(this->pozycjaMyszkiOkno);


	/* 
	//Pozycja myszki do ekranu
	cout << "Pozycja myszki do ekranu: "
		<< Mouse::getPosition().x << " "
		<< Mouse::getPosition().y << "\n";
	//Pozycja myszki do okna
	cout << "Pozycja myszki do okna: "
		<< Mouse::getPosition(*this->okno).x << " "
		<< Mouse::getPosition(*this->okno).y << "\n";
	*/
}

//Pokazuje wszystko co sie ma dziac na ekranie
void Game::render()
{
	//Czyscimy okno
	this->okno->clear();

	//Generujemy obiekty
	this->renderWrog();
	//Generujemy tekst
	this->renderTekst();
	 
	//Wyswietlamy okno
	this->okno->display();
}


//Funkcje prywatne

void Game::inicZmienne()
{
	//Literal pustego wskaznika
    this->okno = nullptr;
	//Punkty na start
	this->punkty = 100;
	//GameOver
	this->gameOver = false;
	//Wrogowie
	this->spawnTimeMax = 16.f;
	this->spawnTime = this->spawnTimeMax;
	this->maxWrogow = 5;
	//Trzymanie myszki
	this->Trzymam = false;
}

void Game::inicOkno()
{
    //VideoMode(640, 480) zamiast 2 linijek nizej i this->videoMode w renderwindow
	this->videoMode.width = 400;
	this->videoMode.height = 800;
    //Tworzymy okono gry  hight,width, nazwa gry, przyciski, ale bez zmiany wielkosci
    this->okno = new RenderWindow(this->videoMode, "Domino Bricks", Style::Titlebar | Style::Close);
	//Limit klatek
	this->okno->setFramerateLimit(60);	
}

void Game::iniCzcionka()
{
	this->czcionka.loadFromFile("Pixellari.ttf");

	if (this->czcionka.loadFromFile("Pixellari.ttf")) {
		cout << "ERROR! Nie mozna zaladowac czcionki" << "\n";
	}

}

void Game::iniTekst()
{
	this->tekst.setFont(this->czcionka);
	this->tekst.setCharacterSize(20);
	this->tekst.setFillColor(Color(255,255,255,255));
	this->tekst.setString("EXAMPLE");

}
 //
void Game::spawnWrog()
{	
	
	if (this->punkty >= this->punkty + 50)
	{
		//this->boss = new Boss(10, 50, 10);
		//Boss bos(1, 2, 3);
	}

	this->wrogowie.push_back(Enemy(1, 1, Vector2f(this->okno->getSize())));
}

void Game::updateWrog()
{
	//Update czasu spawnowania wroga
	if (this->wrogowie.size() < this->maxWrogow)
	{

		if (this->spawnTime >= this->spawnTimeMax) {
			
			//Spawn wroga i reset czasu
			this->spawnWrog();
			this->spawnTime = 0.f;
		} 
		else {
				this->spawnTime += 1.f;
		}
	}
	
	//Wrog poza mapa
	for (int i = 0; i < this->wrogowie.size(); i++)
	{
	
		//Poruszanie po y
		this->wrogowie[i].ksztalt.move(0.f, 4.f);

		//Czy wrog jest w ramie okna
		if (this->wrogowie[i].ksztalt.getPosition().y > this->okno->getSize().y) {
			//Usuwa wroga jesli spadl poza mape
			this->wrogowie.erase(this->wrogowie.begin() + i);			
			cout << "Klocek uciekl! Tracisz punkty, zostalo: \n" << punkty << "!\n";
			this->punkty -= 5;
		}
	}
	
	//Klikniecie na wroga
	if (Mouse::isButtonPressed(Mouse::Left)) {

		//Zapobieganie trzymania myszki
		if (this->Trzymam == false) {

			this->Trzymam = true;
			bool statusWroga = false;

			for (int i = 0; i < this->wrogowie.size() && statusWroga == false; i++)
			{
				//Czy myszka jest w ksztalcie ograniczajcym obiekt
				if (this->wrogowie[i].ksztalt.getGlobalBounds().contains(this->pozycjaMyszkiWidok))
				{
					//Usuwa wroga na pozycji ktora znalezlismy
					statusWroga = true;
					this->wrogowie.erase(this->wrogowie.begin() + i);
					
					//Zdobywanie punkta
					cout << "Zdobywasz punkt:" << punkty <<"!\n";
					this->punkty += 1;
				}
			}
		}

		// Jesli nie klikasz
		} else {
		this->Trzymam = false;
		

	}
	

	/* jakaœ ciekawa pêtla
	for (auto& e : this->wrogowie)
	{
		//Poruszanie po y
		e.move(0.f, 2.f);
	}
	*/
}

void Game::renderWrog()
{
	//Renderuje wszystkich wrogow	
	
	/*for (auto& trigger : this->wrogowie.ksztalt)
	{
		this->okno->draw(trigger);
	}*/
	
	for (size_t i = 0; i < wrogowie.size(); i++)
	{
		this->okno->draw(wrogowie[i].ksztalt);
	}
}

void Game::updateTekst()
{	
	//Tworzymy obiekt do ciagu znakow
	stringstream wypisz;

	//Wypisujemy w niego tekst
	wypisz << "Punkty: " << this->punkty;

	//Ustawiamy
	this->tekst.setString("awdawdawdawdawd");
}

void Game::renderTekst()
{
	//Renderuje tekst
	this->okno->draw(this->tekst);
}
