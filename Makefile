CXX := g++

SRC := src
OBJ := obj
BIN := bin
INC := include

CXXFLAGS := -Wall -g -Wextra -pedantic -std=c++11 -I$(INC) -pg

SRCS := $(wildcard $(SRC)/*.cpp)

OBJS := $(patsubst $(SRC)/%.cpp,$(OBJ)/%.o,$(SRCS))

TARGET := $(BIN)/main

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -pg $^ -o $@

$(OBJ)/%.o: $(SRC)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(OBJ)/*.o $(BIN)/main