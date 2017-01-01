TARGET = ps10-4
SRC = $(TARGET).cpp
OBJ = $(TARGET).o
FLAGS = -g -Wall -std=c++11

all:$(TARGET)

$(OBJ) : $(SRC)
	g++ -c $(SRC) $(FLAGS)

$(TARGET): $(OBJ)
	g++ $(FLAGS) -o $(TARGET) $(OBJ)
        
clean:
	$(RM) $(TARGET)
	$(RM) $(TARGET).o 
