

Projekt: Robot CMYK

Jakub Gałat
Konrad Kulesza


Zadanie polegało na znalezieniu i przebadaniu algorytmów rozwiązujących problem robota układającego fabry w kolejności CMYK.
Robot może wykonywać jedynie ruch polegający na przemieszczeniu czterech stojących obok siebie farbek na koniec.


Opcje uruchomienia:
- (-h), pomoc
- (-m), tryb
- (-n), rozmiar problemu
- (-k), liczba powtórzeń kroku
- (-s), krok
- (-r), liczba uruchomień
- (-d), parametr generatora oznaczający z jakim prawobodobieńswem ma się powtórzyć wygenerowana wcześniej farbka
- (-a), numer algorytmu, który ma być uruchomiony
- (-b), włącza tryb DEBUG, umożliwiający sprawdzenie, która czwórka bedzie przemieszczana


Dane wejściowe: ciąg znaków ze zbioru {C,M,Y,K}

Wyniki: wyniki prezentowane według schematu

"
Size: [liczba]
Number of moves: [liczba]
Time taken by algorithm: [liczba][ms]
[ ciąg znaków ze zbioru {C,M,Y,K} ]
"


Opis algorytmów:
- Grupowanie z ostatnim:
	Algorytm poszukuje największej grupy koloru pasującego do ostaniej farbki. Następnie przemieszcza
	taką grupę na koniec ciągu. 
- Szybkie tworzenie czwórek:
	Algorytm poszukuje najwięszej grupy przylegajacej do prawej strony czwórki (tak, 
	żeby dało się przemieścić ją na konieć i dodać do niej grupe tego samego koloru) i przemieszcz ją.
 	Następnie szuka największej groupy przylegającej do lewej strony
	czwórki, tego samego koloru.
- Sortowanie od początku:
	Algorytm sortuje kolory od lewej. Na początku koloru, który jest na (4n+1) pozycji względem ostatniego posortowanego koloru.
	Jeżeli takiego nie ma, manipuluje ciągiem w taki sposób, aby taki kolor się znalazł.
- Brutalne przeszukiwanie:
	Algorytm dodaje kolejne możliwe stany do kolejki FIFO.

Zastosowane struktury danych:
-std::vector
-std::map


Funkcjonalna dekompozycja programu:
- main.cpp: 
	Główny plik źródłowy, zawiera kod implementujący interfejs programu i obsługę opcji.

- bruteForce.cpp bruteForce.h:
	Plik źródłowy i nagłówkowy implementujący "Brutalne przeszukiwanie".

- creatingGroupsWithLast.cpp creatingGroupsWithLast.h:
	Plik źródłowy i nagłówkowy implementujący "Grupowanie z ostatnim".

- fast4Create.cpp fast4Create.h:
	Plik źródłowy i nagłówkowy implementujący "Szybkie tworzenie czwórek".

- startFromBeg.cpp startFromBeg.h:
	Plik źródłowy i nagłówkowy implementujący "Sortowanie od początku".

- utilities.cpp utilities.h:
	Plik źródłowy i nagłówkowy implementujący funkcje pomocnicze.


Decyzje projektowe:
- zdecydowaliśmy się stworzyć generator losowych ciągów farb, generujący
liczby z pewnym prawdopodobieństwem powtórzenia ostanio wygenerowanej farby,
ustalanym przez użytkownika. Pozwala to sprawdzić algorytmy w róznych warunkach
ułożenia danych.

- dodaliśmy tryb debug, który umożliwia sprawdzenie algorytmu. Pokazuje on
która grupa zostanie przeniesiona na koniec.








