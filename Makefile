CC=g++
CFLAGS=-std=c++11 -g
LDFLAGS=-pthread

SERVER=sockserver
CLIENT=client

all:
	$(CC) $(CFLAGS) $(LDFLAGS) $(SERVER).c -o $(SERVER)
	$(CC) $(CFLAGS) $(LDFLAGS) $(CLIENT).c -o $(CLIENT)

clean:
	@rm -f $(SERVER) $(CLIENT)
