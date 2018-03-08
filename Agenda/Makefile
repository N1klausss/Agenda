CC := g++-4.8 -g
INC_DIR := include
SRC_DIR := src
BUILD_DIR := build
BIN_DIR := bin


$(BIN_DIR)/Agenda : $(BUILD_DIR)/User.o $(BUILD_DIR)/Date.o $(BUILD_DIR)/Meeting.o $(BUILD_DIR)/Storage.o $(BUILD_DIR)/AgendaService.o $(BUILD_DIR)/AgendaUI.o $(BUILD_DIR)/Agenda.o 
	$(CC) -std=c++11 -I./$(INC_DIR) $^ -o $@


$(BUILD_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(CC) -std=c++11 -I./$(INC_DIR) -c -o $@ $<

clean:
	@rm -f $(BUILD_DIR)/*.o
	@rm -f $(BIN_DIR)/Agenda
