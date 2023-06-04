Celem zadania piątego jest zaimplementowanie metody aproksymacji opartej o wielomiany Hermite'a.

- Program ma dawać do wyboru kilka funkcji: 
	liniowa, 
	|x|,
	wielomian, 
	trygonometryczna, 
	ich złożenia

- Użytkownik w pierwszej kolejności wybiera aproksymowaną funkcję

- Przedział aproksymacji

- Stopień wielomianu aproksymującego

- Parametry związane z wykorzystywaną metodą całkowania (zad4)

- Następnie program wyznacza wielomian aproksymacyjny podanego stopnia

- Rysuje jego wykres (wraz z wykresem funkcji oryginalnej) i oblicza błąd aproksymacji

//- Bardziej zaawansowana wersja programu 
//	- dla osób chcących uzyskać 5 
//	- powinna posiadać również tryb pracy, w którym użytkownik określa oczekiwany błąd aproksymacji

- Wartości wielomianów należy obliczać używając schematu Hornera.

- Program iteracyjnie dobiera stopień wielomianu aproksymacyjnego (zaczynając od wielomianu stopnia 1)

# UWAGA
- Wartości współczynników wielomianów aproksymacyjnych należy wyliczać w sposób iteracyjny i 
	zapamiętywać w tablicy tak, aby możliwe było wykorzystanie tych współczynników w schemacie Hornera.

- Korzystanie z rekurencji do wyliczania wartości wielomianów bądź zakodowanie współczynników na 
	sztywno nie jest dopuszczalne.
