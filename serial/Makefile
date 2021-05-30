CC=g++
STD=-std=c++11
CF=$(STD) -pedantic -W
BUILD_DIR=build


all: $(BUILD_DIR) serial.out

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

serial.out: $(BUILD_DIR)/main.o $(BUILD_DIR)/utils.o
	$(CC) $(CF) -o serial $(BUILD_DIR)/main.o $(BUILD_DIR)/utils.o

$(BUILD_DIR)/main.o: main.cpp utils.hpp
	$(CC) $(CF) -c -o $(BUILD_DIR)/main.o main.cpp

$(BUILD_DIR)/utils.o: utils.cpp utils.hpp
	$(CC) $(CF) -c -o $(BUILD_DIR)/utils.o utils.cpp


.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) *.out &> /dev/null