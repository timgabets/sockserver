CC=g++
CFLAGS=-std=c++11 -g
LDFLAGS=-pthread

SERVER=sockserver

all:
	$(CC) $(CFLAGS) $(LDFLAGS) $(SERVER).c -o $(SERVER)

clean:
	@rm -f $(SERVER) $(CLIENT)
