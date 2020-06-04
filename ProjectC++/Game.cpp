//Dolaczanie
#include "Game.h"

using namespace sf;
using namespace std;


//Konstruktor
Game::Game()
{
    //Inicjowanie aspektow gry
    this->inicZmienne();
    this->inicOkno();	
	this->iniCzcionka();
	this->iniTekst();	
}

//Destruktor wirtualnie, usuwwanie okna
Game::~Game()
{
    delete this->okno;	
}

//***************************************************************************************
//Funkcje publiczne

//Sprwadza czy gra uruchomina
const bool Game::otwarteOkno() const
{
    return this->okno->isOpen();
}

//Kontrola co sie dzieje z ekranem
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

//Aktualizuje to co ma sie dziac na ekranie
void Game::update()
{
	//Zaleznei od zdarzenia
	this->Nasluch();

	//Jesli punkty nie spadly ponizej zera
	if (this->gameOver == false) {

		this->updateMyszka();

		this->updateWrog();

		this->updateTekst();

	}

		//Wyj¹tek
		try
		{
			this->zwrocPunkty();
		}
		catch (string w)
		{
			cout << "Wyjatek: " << w;
			this->gameOver = true;
		}

		//Ilosc wrogow na ekranie w zaleznosci od punktow
		if (this->punkty > 100) {

			this->maxWrogow = 8;
		}

		if (this->punkty > 200) {

			this->maxWrogow = 11;
		}
}

//Pozycja myszki wobec okna
void Game::updateMyszka()
{
	//Badanie pozycji myszki
	this->pozycjaMyszkiOkno = Mouse::getPosition(*this->okno);
	//Koordynaty myszki na mapie pikseli
	this->pozycjaMyszkiWidok = this->okno->mapPixelToCoords(this->pozycjaMyszkiOkno);

	//Pozycja myszki do ekranu
	/*
	cout << "Pozycja myszki do ekranu: "
		<< Mouse::getPosition().x << " "
		<< Mouse::getPosition().y << "\n";
	//Pozycja myszki do okna
	cout << "Pozycja myszki do okna: "
		<< Mouse::getPosition(*this->okno).x << " "
		<< Mouse::getPosition(*this->okno).y << "\n";
	*/
}


//Kontorluje ilosc punktow, zwraca wyjatek
int Game::zwrocPunkty()
{
	//Jesli punkty spadly ponizej 0
	if (this->punkty <= 0) {

		//Ustawia gameOver na zero dla konca gry, stosuje wyjatek
		this->gameOver = true;
		string wyjatek = "Punkty spadly ponizej zera!";
		throw wyjatek;
	}
	else
	{
		return this->punkty;
	}
}

//Koniec gry po stracie punktow
const bool Game::gameOvercontrol() const
{
	return this->gameOver;
}


//-----------------------------------------
//Funkcje Wrogow

//Resp wrogow
void Game::spawnWrog()
{
	this->wrogowie.push_back(Enemy(Vector2f(this->okno->getSize())));
}

//Rysuje wrogow
void Game::renderWrog()
{
	//Renderuje boss-a
	this->okno->draw(boss.ksztalt);

	//Petla zakresowa for renderuje wszystkich wrogow
	for (auto& trigger : this->wrogowie)
	{
		this->okno->draw(trigger.ksztalt);
	}

	//Petla renderuje wrogow
	/*
	for (size_t i = 0; i < wrogowie.size(); i++)
	{
		this->okno->draw(wrogowie[i].ksztalt);
	}
	*/

}

//Zmienianie pozycji wroga i boss-a
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

	//Zwiekszanie wartosci bossa ( nie dziala poprawnie? )
	if (this->punkty == this->punkty_cp + 10)
	{
		this->punkty_cp += 1;

		this->boss = boss;
	}

	//Poruszanie bossa
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
			//Iteratory STL
			this->wrogowie.erase(this->wrogowie.begin() + i);
			this->punkty -= 1;
			cout << "Klocek uciekl! Tracisz punkty, zostalo: \n" << punkty << "!\n";
		}

		//Boss poza mapa
		if (this->boss.ksztalt.getPosition().y > this->okno->getSize().y)
		{
			this->boss = 0;
			this->punkty -= this->boss.zwrocObrazenia();
			cout << "Boss uciekl! Tracisz punkty, zostalo: \n" << punkty << "!\n";
		}
	}

	//Cooldown myszki
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
						//Iteratory STL
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
						this->liveBoss();
						if (this->boss.zwrocHp() == 5) {
							cout << "Uderz jeszcze raz!" << "\n";
						}
					}
				}

				this->shootTimer = 0;
			}
		}

		// Jesli nie klikasz
	}
	else {
		this->Trzymam = false;
	}

}

//Czy boss zyje, jesli zabijesz bossa
void Game::liveBoss()
{
	if (this->boss.zwrocHp() <= 0)
	{
		this->boss = 0;

		this->punkty += this->boss.zwrocPunkty();
		cout << "Boss zabity, zdobywasz punkt:" << punkty << "!\n";
	}

}

//-----------------------------------------
//Dodatki

//Aktualizuje liczbe punkow
void Game::updateTekst()
{
	//Tworzymy obiekt do ciagu znakow
	string tekst = "Punkty: " + to_string(this->punkty);

	//Ustawiamy
	this->tekst.setString(tekst);
}

//Rysuje tekst
void Game::renderTekst()
{
	//Renderuje tekst
	this->okno->draw(this->tekst);
}

//***************************************************************************************
//Funkcje prywatne

//Wlasny szablon funkcji dla losowych punktow na start
template <typename T>
T luckyNumber()
{
	T punkty = rand() % 20 + 1;
	return punkty;
}

//Inicialuzje zmienne
void Game::inicZmienne()
{
	//Literal pustego wskaznika
    this->okno = nullptr;
	//Punkty na start
	this->punkty = luckyNumber<float>();
	this->punkty_cp = 10;
	//GameOver
	this->gameOver = false;
	//Wrogowie
	this->spawnTimeMax = 16.f;
	this->spawnTime = this->spawnTimeMax;
	this->shootTimer = 0;
	this->shootTimerMax = 60 / 60;
	this->maxWrogow = 5;
	//Inicuje bossa	
	this->boss = Boss();
	//Trzymanie myszki
	this->Trzymam = false;	
}

//Ustawienia okna
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

//Ustawienia czcionki
void Game::iniCzcionka()
{
	if(!this->czcionka.loadFromFile("font.ttf")) {
	   cout << "Mamy problem z czcionka!" << endl;
	}
}

//Ustawienia tekstu
void Game::iniTekst()
{
	this->tekst.setFont(this->czcionka);
	this->tekst.setCharacterSize(20);
	this->tekst.setFillColor(Color(255,255,255,255));
	this->tekst.setString("EXAMPLE");
}
 

