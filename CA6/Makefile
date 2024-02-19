PROJECT_NAME := ImageEditor
CC := g++ --std=c++20

HEADERS_DIR := .
BUILD_DIR := build

TARGET := $(PROJECT_NAME)

all: $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR);

$(BUILD_DIR)/bmp.o: $(HEADERS_DIR)/bmp.hpp ./bmp.cpp
	$(CC) -c bmp.cpp -o $(BUILD_DIR)/bmp.o;

$(BUILD_DIR)/filter.o: $(HEADERS_DIR)/filter.hpp ./filter.cpp
	$(CC) -c filter.cpp -o $(BUILD_DIR)/filter.o;

$(BUILD_DIR)/invert.o: $(HEADERS_DIR)/invert.hpp ./invert.cpp $(BUILD_DIR)/filter.o
	$(CC) -c invert.cpp -o $(BUILD_DIR)/invert.o;

$(BUILD_DIR)/gray.o: $(HEADERS_DIR)/gray.hpp ./gray.cpp $(BUILD_DIR)/filter.o
	$(CC) -c gray.cpp -o $(BUILD_DIR)/gray.o;

$(BUILD_DIR)/command_manager.o: $(HEADERS_DIR)/command_manager.hpp ./command_manager.cpp
	$(CC) -c command_manager.cpp -o $(BUILD_DIR)/command_manager.o;

$(BUILD_DIR)/kernel.o: ./kernel.cpp $(HEADERS_DIR)/kernel.hpp
	$(CC) -c kernel.cpp -o $(BUILD_DIR)/kernel.o;

$(BUILD_DIR)/emboss.o: ./emboss.cpp $(HEADERS_DIR)/emboss.hpp $(BUILD_DIR)/kernel.o
	$(CC) -c emboss.cpp -o $(BUILD_DIR)/emboss.o;

$(BUILD_DIR)/blur.o: ./blur.cpp $(HEADERS_DIR)/blur.hpp $(BUILD_DIR)/kernel.o
	$(CC) -c blur.cpp -o $(BUILD_DIR)/blur.o;

$(BUILD_DIR)/sharpen.o: ./sharpen.cpp $(HEADERS_DIR)/sharpen.hpp $(BUILD_DIR)/kernel.o
	$(CC) -c sharpen.cpp -o $(BUILD_DIR)/sharpen.o;

$(BUILD_DIR)/main.o: ./command_manager.cpp
	$(CC) -c main.cpp -o $(BUILD_DIR)/main.o;

$(TARGET): $(BUILD_DIR) $(BUILD_DIR)/main.o  $(BUILD_DIR)/bmp.o $(BUILD_DIR)/filter.o $(BUILD_DIR)/invert.o $(BUILD_DIR)/gray.o $(BUILD_DIR)/command_manager.o $(BUILD_DIR)/kernel.o $(BUILD_DIR)/emboss.o $(BUILD_DIR)/blur.o $(BUILD_DIR)/sharpen.o
	$(CC) $(BUILD_DIR)/main.o $(BUILD_DIR)/bmp.o $(BUILD_DIR)/filter.o $(BUILD_DIR)/invert.o $(BUILD_DIR)/gray.o $(BUILD_DIR)/kernel.o $(BUILD_DIR)/command_manager.o $(BUILD_DIR)/emboss.o $(BUILD_DIR)/blur.o $(BUILD_DIR)/sharpen.o -o $(TARGET)

clean:
	rm -f $(TARGET);
	rm -rf $(BUILD_DIR);
