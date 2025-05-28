Symulacja inteligentnych świateł drogowych na skrzyżowaniu.

Symulacja obejmuje 3 pasy na każdej z 4 dróg dojazdowych.

Działanie algorytmu

Symulacja ma 9 stanów świateł.
1 stan w którym wszystkie światła są czerwone (oczekiwanie na samochody)
4 stany w którym samochody z jednej drogi mają zielone światło we wszystkich kierunkach
2 stany w których samochody z przeciwnych kierunków mogą jechać na wprost i w prawo
2 stany w których samochody z przeciwnych kierunków mogę jechać w lewo

W każdym kroku symulacji algorytm oblicza w którym stani największa liczba samochodów będzie miała zielone światło, jeżeli jest to aktualny tryb świateł, nic się nie dzieje, w przeciwnym wypadku światła zmianiają się zgodnie z nowym stanem (następuje jednen krok ze stanem przejściowym- żółtymi światłami).

Komenda make all kompiluje program napisany w C w plik wykonywalny sim.
Sim korzysta z formatu danych przetwarzanego przez simulation.py
Sim sczytuje dane ze standardowego wyjscia, na standardowe wyjscie wypisuje wyłącznie dane do przetworzenia na json, na standardowe wyjscie diagnostyczne wypisuje wizualizację skrzyżowania.
Wizualizacja nie obsługuje samochodów które chcą zawrócić, ale sam algorytm uwzględnia je w symulacji.

commands.py Generuje przykładowy plik wejsciowy .json

make test_runner tworzy plik wykonywalny test_runner który uruchamia testy jednostkowe.

Do projektu dołączony jest plik Doxyfile który umożliwia wygenerowanie dokumentacji za pomocą komendy `doxygen Doxyfile`

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