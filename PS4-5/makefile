TARGET = ps4-5

all:$(TARGET)

$(TARGET):$(TARGET).o
	g++ -std=c++11 -g -Wall -o $(TARGET) $(TARGET).cpp
	
clean:
	$(RM) $(TARGET)
	$(RM) $(TARGET).o
