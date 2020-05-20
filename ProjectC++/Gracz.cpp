//Deklaracje
#include "Gracz.h"
 
Gracz::Gracz(Texture* tekstura)
    :lvl(1), exp(0), expNext(100), HP(10), MaxHP(10), damage(1), MaxDamage(2), score(0)
{ 
    this->tekstura = tekstura;
    this->ksztalt.setTexture(*this->tekstura);
} 

Gracz::~Gracz()
{

}

void Gracz::Poruszanie()
{
    if (Keyboard::isKeyPressed(Keyboard::Key(0)))
        std::cout << "A" << "\n";
}

void Gracz::Update()
{ 
  
}

void Gracz::Draw(RenderTarget &target)
{
    target.draw(this->ksztalt);
} 