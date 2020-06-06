Projekt stworzony na zajęcia C++ z wykorzystaniem podanych zagadnień

"DominoBricks" polega na zestrzeliwaniu spadających klocków za pomocą kliknięcia myszką w biały bądź czerwony kwadrat. Czerwone klocki wymagają więcej trafień oraz dają i zabierają więcej punktów! Nie pozwól spaść punktom poniżej zera! 

Wersja na Linux - sprawdzana na Ubuntu 18.04.4

          Dołączony Makefile do odpalania gry. Sposób uruchomienia:
          --Wpisujemy cd Desktop w terminalu
          
          --Wpisujemy git clone https://github.com/Mrozu3/MySecond ( upewnij się wcześniej, że masz zainstalowany pakiet git ) 
         
          --Wpisujemy cd MySecond/"Wersja Linux"

          --Będąc w katalogu, w terminalu wpisujemy "make all" - skompiluje nam to wszystkie pliki gry, oraz dołączy odpowiednie biblioteki SFML

          --Po zakończeniu kompilacji, wpisujemy "make Domino" - funkcja odpala grę

          --Miłego grania
          
 
 Poszczególne wymienione zagadnienia w plikach:
 
         -Klasy: Game.h Enemy.h
                   Przykład:                  
![image](https://user-images.githubusercontent.com/64261099/83948781-0b496280-a820-11ea-9fa9-84665e6846e9.png)

        -Konstruktory, dekonstruktory: Game.h/Game.cpp Enemy.h/Enemy.cpp
                   Przykład:
![image](https://user-images.githubusercontent.com/64261099/83949303-4600ca00-a823-11ea-814c-5c00de5be8e5.png)

        -Konstruktor kopiujący: Enemy.h/Enemy.cpp - wykorzystany specjalnie do kopiowania Boss-a
 ![image](https://user-images.githubusercontent.com/64261099/83949412-ea830c00-a823-11ea-98d9-13000ebb5cac.png)
 
        -Dziedziczenie: Enemy.h/Enemy.cpp - klasa Boss dziedziczy hp i punkty po klasie Enemy
 ![image](https://user-images.githubusercontent.com/64261099/83949496-6d0bcb80-a824-11ea-8f7a-481fb9aa087d.png)
 
        -Polimofrizm: Enemy.h/Enemy.cpp - funkcja zmienKolor() zachowuje się adekwatnie do tego kiedy jest wywoływana na Enemy, a kiedy na Boss-ie
![image](https://user-images.githubusercontent.com/64261099/83949575-f4f1d580-a824-11ea-85c2-f800cdcdd53f.png)

        -Klasa abstrakcyjna i czysto wirtualna metoda: Enemy.h - metoda zostaje przesłonięta w klasie Boss, a jeżeli w klasie jest przynajmniej jedna metoda czysto wirtualna, to jest to klasa abstrakcyjna.
![image](https://user-images.githubusercontent.com/64261099/83949690-9aa54480-a825-11ea-985c-50783a4ecabb.png)
        
        -STL: Game.cpp - Wykorzystany w różnych częściach kodu do chociażby iterowania po wektorach
![image](https://user-images.githubusercontent.com/64261099/83950192-1bb20b00-a829-11ea-953a-3135b157ea0b.png)

        -Pętla zakresowa for: Game.cpp - służy do renderowania wszystkich wrogów ( niczym for each, a poniżej zastąpienie jej zwykłą pętlą ) 
![image](https://user-images.githubusercontent.com/64261099/83949825-31720100-a826-11ea-9650-7c2c2b33f3c9.png)
        
        -Własny szablon klasy: Game.cpp - wykorzystany do określania typu zmiennej początkowych punktów
![image](https://user-images.githubusercontent.com/64261099/83949881-9f1e2d00-a826-11ea-9baf-6d2ff922788b.png)

        -Przeciążenie operatorów: Enemy.h/Enemy.cpp - własny typ do odejmowania obrażeń od punktów hp dla obiektu Boss-a
![image](https://user-images.githubusercontent.com/64261099/83949927-16ec5780-a827-11ea-99b8-a0be30e2dc24.png)

        -Wyjątek: Game.cpp - wyjątek następuje kiedy ilość punktów spadnie poniżej zera, co jest niedozwolone dla gry
![image](https://user-images.githubusercontent.com/64261099/83950012-d7723b00-a827-11ea-9b75-59d07d3217dd.png)

        -Plik .h z deklaracjami i .cpp z definicjami
![image](https://user-images.githubusercontent.com/64261099/83950064-3d5ec280-a828-11ea-851a-e5e4e3978d02.png)

        -Linker-y: na Linuxie lepiej pokazane zagadnienie
![image](https://user-images.githubusercontent.com/64261099/83950146-b231fc80-a828-11ea-9899-dd177f947741.png)



