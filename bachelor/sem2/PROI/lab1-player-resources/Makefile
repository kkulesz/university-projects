CPPFLAGS := -Wall -g -Iinclude

INCLUDE := include
SRC := src
BIN := bin
BUILD := build
MKDIR_P := mkdir -p
TEST:= test

$(BIN)/app: $(BUILD) $(BIN) $(BUILD)/main.o $(BUILD)/buildings.o $(BUILD)/saw.o $(BUILD)/goldmine.o $(BUILD)/worker.o $(BUILD)/player.o $(BUILD)/managers.o $(BUILD)/building_manager.o $(BUILD)/worker_manager.o $(BUILD)/interface.o $(BUILD)/logic.o
	g++ $(BUILD)/main.o $(BUILD)/buildings.o $(BUILD)/saw.o $(BUILD)/goldmine.o $(BUILD)/worker.o $(BUILD)/player.o $(BUILD)/managers.o $(BUILD)/building_manager.o $(BUILD)/worker_manager.o $(BUILD)/interface.o $(BUILD)/logic.o -o $(BIN)/app

$(BUILD)/main.o: $(SRC)/main.cpp $(BUILD)/interface.o
	g++ $(CPPFLAGS) -c $(SRC)/main.cpp -o $(BUILD)/main.o

$(BUILD)/buildings.o: $(SRC)/buildings.cpp $(INCLUDE)/buildings.h $(BUILD)/worker.o
	g++ $(CPPFLAGS) -c $(SRC)/buildings.cpp -o $(BUILD)/buildings.o

$(BUILD)/saw.o: $(SRC)/saw.cpp $(INCLUDE)/saw.h $(BUILD)/buildings.o
	g++ $(CPPFLAGS) -c $(SRC)/saw.cpp -o $(BUILD)/saw.o

$(BUILD)/goldmine.o: $(SRC)/goldmine.cpp $(INCLUDE)/goldmine.h $(BUILD)/buildings.o
	g++ $(CPPFLAGS) -c $(SRC)/goldmine.cpp -o $(BUILD)/goldmine.o

$(BUILD)/worker.o: $(SRC)/worker.cpp $(INCLUDE)/worker.h
	g++ $(CPPFLAGS) -c $(SRC)/worker.cpp -o $(BUILD)/worker.o

$(BUILD)/player.o: $(SRC)/player.cpp $(INCLUDE)/player.h $(BUILD)/buildings.o $(BUILD)/saw.o $(BUILD)/goldmine.o
	g++ $(CPPFLAGS) -c $(SRC)/player.cpp -o $(BUILD)/player.o

$(BUILD)/managers.o: $(SRC)/managers.cpp $(INCLUDE)/managers.h $(BUILD)/player.o
	g++ $(CPPFLAGS) -c $(SRC)/managers.cpp -o $(BUILD)/managers.o

$(BUILD)/building_manager.o: $(SRC)/building_manager.cpp $(INCLUDE)/building_manager.h $(BUILD)/managers.o
	g++ $(CPPFLAGS) -c $(SRC)/building_manager.cpp -o $(BUILD)/building_manager.o

$(BUILD)/worker_manager.o: $(SRC)/worker_manager.cpp $(INCLUDE)/worker_manager.h $(BUILD)/managers.o
	g++ $(CPPFLAGS) -c $(SRC)/worker_manager.cpp -o $(BUILD)/worker_manager.o

$(BUILD)/interface.o: $(SRC)/interface.cpp $(INCLUDE)/interface.h $(BUILD)/logic.o
	g++ $(CPPFLAGS) -c $(SRC)/interface.cpp -o $(BUILD)/interface.o

$(BUILD)/logic.o: $(SRC)/logic.cpp $(INCLUDE)/logic.h $(BUILD)/managers.o $(BUILD)/building_manager.o $(BUILD)/worker_manager.o
	g++ $(CPPFLAGS) -c $(SRC)/logic.cpp -o $(BUILD)/logic.o

$(BUILD):
	$(MKDIR_P) $(BUILD)
$(BIN):
	$(MKDIR_P) $(BIN)



###############################################
clean:
	rm -f $(BUILD)/*.o
	rm -f $(BIN)/app
	rm -f $(TEST)/test
	rm -f $(TEST)/test.o

###############################################
test: $(BUILD) $(BIN) $(TEST)/test.o $(BUILD)/buildings.o $(BUILD)/saw.o $(BUILD)/goldmine.o $(BUILD)/worker.o $(BUILD)/player.o $(BUILD)/managers.o $(BUILD)/building_manager.o $(BUILD)/worker_manager.o $(BUILD)/interface.o $(BUILD)/logic.o
	g++ $(TEST)/test.o $(BUILD)/buildings.o $(BUILD)/saw.o $(BUILD)/goldmine.o $(BUILD)/worker.o $(BUILD)/player.o $(BUILD)/managers.o $(BUILD)/building_manager.o $(BUILD)/worker_manager.o $(BUILD)/interface.o $(BUILD)/logic.o -o $(TEST)/test

$(TEST)/test.o: $(TEST)/test.cpp $(BUILD)/interface.o
	g++ $(CPPFLAGS) -c $(TEST)/test.cpp -o $(TEST)/test.o

