CPPFLAGS := -Wall -Wextra -g

main: main.o
	g++ $(CPPFLAGS) main.o -o main

main.o: main.cpp
	g++ $(CPPFLAGS) -c main.cpp -o main.o

clean:
	rm -f *.o
	rm main
