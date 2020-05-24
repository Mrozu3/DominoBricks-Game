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
	this->punkty = 10;
	this->punkty_cp = 10;
	//GameOver
	this->gameOver = false;
	//Wrogowie
	this->spawnTimeMax = 16.f;
	this->spawnTime = this->spawnTimeMax;
	this->shootTimer = 0;
	this->shootTimerMax = 60 / 60;
	this->maxWrogow = 5;
	//Trzymanie myszki
	this->Trzymam = false;
	
	//Inicuje bossa	
	this->boss = Boss();	
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
	this->czcionka.loadFromFile("font.ttf");
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
	this->wrogowie.push_back(Enemy(Vector2f(this->okno->getSize())));
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

	if (this->punkty == this->punkty_cp + 10)
	{
		this->punkty_cp += 1;
		
		this->boss = boss;
	}
	
	this->boss.ksztalt.move(0.f, 4.f);

	//Wrog poza mapa
	for (int i = 0; i < this->wrogowie.size(); i++)
	{
	
		//Poruszanie po y
		this->wrogowie[i].ksztalt.move(0.f, 5.f);
		//Polimorfizm
		this->wrogowie[i].zmienKolor();

		//Czy wrog jest w ramie okna
		if (this->wrogowie[i].ksztalt.getPosition().y > this->okno->getSize().y) {
			//Usuwa wroga jesli spadl poza mape
			this->wrogowie.erase(this->wrogowie.begin() + i);			
			this->punkty -= 1;
			cout << "Klocek uciekl! Tracisz punkty, zostalo: \n" << punkty << "!\n";
		}
		
		if (this->boss.ksztalt.getPosition().y > this->okno->getSize().y)
		{
			this->boss = 0;
			this->punkty -= this->boss.zwrocObrazenia();
			cout << "Boss uciekl! Tracisz punkty, zostalo: \n" << punkty << "!\n";
		}		
	}
	
	if (this->shootTimer < this->shootTimerMax)
	{
		this->shootTimer++;
	}

	//Klikniecie na wroga
	if (Mouse::isButtonPressed(Mouse::Left)) {

		//Zapobieganie trzymania myszki
		if (this->Trzymam == false)
		{
			this->Trzymam = true;
			bool statusWroga = false;

			if (this->shootTimer >= this->shootTimerMax)
			{
				for (int i = 0; i < this->wrogowie.size() && statusWroga == false; i++)
				{
					//Czy myszka jest w ksztalcie ograniczajcym obiekt
					if (this->wrogowie[i].ksztalt.getGlobalBounds().contains(this->pozycjaMyszkiWidok))
					{
						//Usuwa wroga na pozycji ktora znalezlismy
						statusWroga = true;
						this->wrogowie.erase(this->wrogowie.begin() + i);

						//Zdobywanie punkta
						cout << "Zdobywasz punkt:" << punkty << "!\n";
						this->punkty += 1;
					}

					if (this->boss.ksztalt.getGlobalBounds().contains(this->pozycjaMyszkiWidok))
					{
						//this->punkty -= this->boss.zwrocObrazenia();
						this->boss - 1;
						this->isAlive();
						if (this->boss.zwrocHp() == 5) {
							cout << "Uderz jeszcze raz!" << "\n";
						}
					}
				}

				this->shootTimer = 0;
			}
		}

		// Jesli nie klikasz
		} else {
		this->Trzymam = false;
	}
	
}

void Game::isAlive()
{
	if (this->boss.zwrocHp() <= 0)
	{
		this->boss = 0;
		this->punkty += this->boss.zwrocPunkty();
		cout << "Boss zabity, zdobywasz punkt:" << punkty << "!\n";		
	}
}

void Game::renderWrog()
{	
	this->okno->draw(boss.ksztalt);
	
	for (size_t i = 0; i < wrogowie.size(); i++)
	{
		this->okno->draw(wrogowie[i].ksztalt);
	}
}

void Game::updateTekst()
{	
	//Tworzymy obiekt do ciagu znakow
	string tekst = "Punkty: " + to_string(this->punkty);

	//Ustawiamy
	this->tekst.setString(tekst);
}

void Game::renderTekst()
{
	//Renderuje tekst
	this->okno->draw(this->tekst);
}
