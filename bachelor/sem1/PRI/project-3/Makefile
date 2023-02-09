CFLAGS := -Wall -Wextra -Iinclude -Isrc

INCLUDE := include
SRC := src
BUILD := build
BIN := bin

$(BIN)/project: $(BUILD)/main.o $(BUILD)/additional.o $(BUILD)/kid.o $(BUILD)/list.o $(BUILD)/file.o $(BUILD)/menu.o
	gcc $(BUILD)/main.o $(BUILD)/additional.o $(BUILD)/kid.o $(BUILD)/list.o $(BUILD)/file.o $(BUILD)/menu.o -o $(BIN)/project

$(BUILD)/main.o: $(SRC)/main.c
	gcc $(CFLAGS) -c $(SRC)/main.c -o $(BUILD)/main.o

$(BUILD)/additional.o: $(SRC)/additional.c
	gcc $(CFLAGS) -c $(SRC)/additional.c -o $(BUILD)/additional.o

$(BUILD)/kid.o: $(SRC)/kid.c $(INCLUDE)/kid.h $(INCLUDE)/additional.h
	gcc $(CFLAGS) -c $(SRC)/kid.c -o $(BUILD)/kid.o

$(BUILD)/list.o: $(SRC)/list.c $(INCLUDE)/list.h $(INCLUDE)/additional.h $(INCLUDE)/kid.h
	gcc $(CFLAGS) -c $(SRC)/list.c -o $(BUILD)/list.o

$(BUILD)/file.o: $(SRC)/file.c $(INCLUDE)/file.h $(INCLUDE)/additional.h $(INCLUDE)/kid.h $(INCLUDE)/list.h
	gcc $(CFLAGS) -c $(SRC)/file.c -o $(BUILD)/file.o

$(BUILD)/menu.o: $(SRC)/menu.c $(INCLUDE)/menu.h $(INCLUDE)/additional.h $(INCLUDE)/kid.h $(INCLUDE)/list.h $(INCLUDE)/file.h
	gcc $(CFLAGS) -c $(SRC)/menu.c -o $(BUILD)/menu.o

clean:
	rm -f $(BUILD)/*.o
	rm -f $(BIN)/project
	
