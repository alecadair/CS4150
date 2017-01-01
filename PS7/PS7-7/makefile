TARGET = ps7-7

all:$(TARGET)

$(TARGET):$(TARGET).o
	g++ -std=c++11 -stdlib=libc++ -g -Wall -o $(TARGET) $(TARGET).cpp
	
clean:
	$(RM) $(TARGET)
	$(RM) $(TARGET).o
