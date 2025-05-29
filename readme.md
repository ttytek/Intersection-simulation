Symulacja inteligentnych świateł drogowych na skrzyżowaniu. <br>

Symulacja obejmuje 3 pasy na każdej z 4 dróg dojazdowych, każdy z pasów ma osobne światło z 3 stanami. <br>

Działanie algorytmu <br>

Symulacja ma 9 stanów świateł. <br>
1 stan w którym wszystkie światła są czerwone (oczekiwanie na samochody), <br>
4 stany w którym samochody z jednej drogi mają zielone światło we wszystkich kierunkach, <br>
2 stany w których samochody z przeciwnych kierunków mogą jechać na wprost i w prawo, <br>
2 stany w których samochody z przeciwnych kierunków mogę jechać w lewo, <br>

W każdym kroku symulacji algorytm oblicza w którym stanie największa liczba samochodów będzie miała zielone światło, jeżeli jest to aktualny tryb świateł, nic się nie dzieje, w przeciwnym wypadku światła zmieniają się zgodnie z nowym stanem (następuje jednen krok ze stanem przejściowym - żółtymi światłami). <br>

Komenda make all kompiluje program napisany w C w plik wykonywalny sim. <br>
Sim korzysta z formatu danych przetwarzanego przez simulation.py. <br>
Sim wczytuje dane ze standardowego wyjscia, na standardowe wyjscie wypisuje wyłącznie dane do przetworzenia na json, na standardowe wyjscie diagnostyczne wypisuje wizualizację skrzyżowania. <br>
Wizualizacja nie obsługuje samochodów które chcą zawrócić, ale sam algorytm uwzględnia je w symulacji. <br>

commands.py Generuje przykładowy plik wejsciowy .json <br>

make test_runner tworzy plik wykonywalny test_runner który uruchamia testy jednostkowe. <br>

Do projektu dołączony jest plik Doxyfile który umożliwia wygenerowanie dokumentacji za pomocą komendy `doxygen Doxyfile`. <br>

showcase.sh kompiluje program uruchamia wszystkie potrzebne skrypty zeby zaprezentowac dzialanie programu, generuje w data/in.json przykladowe wejscie, w data/out.json umieszcze wyjscie algorytmu, na standardowe wyjscie wypisuje wizualizacje. <br>


Wizualizacja wybranych stanów skrzyzowania
```
     |  |  |
     |     |
     |  |  |
     |     |
     |  |  |
-----+-----+-----
     |<  ^ |     
- - -| | | |- - -
     | v  >|     
-----+-----+-----
     |  |  |
     |     |
     |  |  |
     |     |
     |  |  |

	 |  |  |
     |     |
     |  |  |
     |     |
     |  |  |
-----+-----+-----
     | <- ^|     
- - -|     |- - -
     |v  ->|     
-----+-----+-----
     |  |  |
     |     |
     |  |  |
     |     |
     |  |  |

     |  |  |
     |     |
     |  |  |
     |     |
     |  |  |
-----+-----+-----
     |<   ^|     
- - -| \ \ |- - -
     |v   >|     
-----+-----+-----
     |  |  |
     |     |
     |  |  |
     |     |
     |  |  |

     |  |  |
     |     |
     |  |  |
     |     |
     |  |  |
-----+-----+-----
     |<  ^ |     
- - -|  // |- - -
     |  v >|     
-----+-----+-----
     |  |  |
     |     |
     |  |  |
     |     |
     |  |  |
```
