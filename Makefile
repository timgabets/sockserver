CC=g++
CFLAGS=-std=c++11
TARGET=sockserver

all:
	$(CC) $(CFLAGS) $(TARGET).c -o $(TARGET)

clean:
	@rm -f $(TARGET)
