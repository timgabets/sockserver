CC=g++
CFLAGS=-std=c++11 -g
LDFLAGS=-pthread

SRV=sockserver
MAIN=tests-main
TESTS=tests

all: test

test: $(MAIN).o $(SRV).o $(TESTS).c
	$(CC) $(LDFLAGS) *.o $(TESTS).c -o $(TESTS)
	time ./$(TESTS)

$(MAIN).o: $(MAIN).c
	$(CC) -c $(MAIN).c -o $(MAIN).o

$(SRV).o: $(SRV).c
	$(CC) $(CFLAGS) $(LDFLAGS) -c $(SRV).c -o $(SRV).o

clean:
	@rm -f *.o $(TESTS)
