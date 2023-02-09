CC = g++
CFLAGS = -Wall -pedantic -Wextra -m64 -g -no-pie


#LINK := `pkg-config --libs allegro-5.0 allegro_image-5.0` 
#LINK := `allegro-config --libs`
#LINK := -lallegro
#LINK := -I/usr/include/allegro5 -L/usr/lib -lallegro
LINK := -lsfml-graphics -lsfml-window -lsfml-system

all:	main.o fun.o
	$(CC) $(CFLAGS) main.o fun.o -o app $(LINK)


main.o:	main.cpp
	$(CC) $(CFLAGS) -c main.cpp -o main.o

fun.o:	fun.s
	nasm -f elf64 fun.s -o fun.o


clean:
	rm -f *.o app
