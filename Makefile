TARGET = a.out
CC = g++
CXXFLAGS = -std=c++20 -Wall -Wextra #-O2

PREF_OBJ = ./obj/
VPATH = ..

SRC = $(wildcard *.cpp) $(wildcard ../*.cpp)
OBJ = $(addprefix $(PREF_OBJ), $(notdir $(SRC:.cpp=.o)))

$(TARGET): $(OBJ)
	$(CC) $(CXXFLAGS) $^ -o $@

$(PREF_OBJ)%.o: %.cpp | obj_dir
	$(CC) $(CXXFLAGS) -c $< -o $@ -I..

obj_dir:
	mkdir -p $(PREF_OBJ)

.PHONY: clean

clean:
	rm -r $(TARGET) $(PREF_OBJ)

