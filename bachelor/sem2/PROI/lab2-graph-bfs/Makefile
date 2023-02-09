CPPFLAGS := -Wall -g -Iinclude -Isrc

INCLUDE := include
SRC := src
BIN := bin
BUILD := build
MKDIR_P := mkdir -p
TEST:= test

$(BIN)/program: $(BUILD) $(BIN) $(BUILD)/vertex.o $(BUILD)/graph.o $(BUILD)/graph_manager_interface.o $(BUILD)/main.o
	g++ $(BUILD)/main.o -o $(BIN)/program

$(BUILD):
	$(MKDIR_P) $(BUILD)

$(BIN):
	$(MKDIR_P) $(BIN)

$(BUILD)/main.o: $(SRC)/main.cpp $(BUILD)/graph_manager_interface.o
	g++ $(CPPFLAGS) -c $(SRC)/main.cpp -o $(BUILD)/main.o

$(BUILD)/graph_manager_interface.o: $(SRC)/graph_manager_interface.tcc $(INCLUDE)/graph_manager_interface.h $(BUILD)/graph.o
	g++ $(CPPFLAGS) -c $(INCLUDE)/graph_manager_interface.h -o $(BUILD)/graph_manager_interface.o

$(BUILD)/graph.o: $(BUILD)/vertex.o $(SRC)/graph.tcc $(SRC)/bfs.tcc $(INCLUDE)/graph.h
	g++ $(CPPFLAGS) -c $(INCLUDE)/graph.h -o $(BUILD)/graph.o

$(BUILD)/vertex.o: $(SRC)/vertex.cpp $(INCLUDE)/vertex.h
	g++ $(CPPFLAGS) -c $(SRC)/vertex.cpp -o $(BUILD)/vertex.o


#####
clean:
	rm -f $(BUILD)/*.o
	rm -f $(BIN)/program
	rm -f $(BIN)/test
#####
test: $(BUILD) $(BIN) $(BUILD)/vertex.o $(BUILD)/graph.o $(BUILD)/test.o
	g++ $(BUILD)/test.o -o $(BIN)/test

$(BUILD)/test.o: $(TEST)/test.cpp $(BUILD)/graph.o
	g++ $(CPPFLAGS) -c $(TEST)/test.cpp -o $(BUILD)/test.o
#####
