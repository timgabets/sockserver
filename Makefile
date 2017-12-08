CC=g++
CFLAGS=-std=c++11 -g
LDFLAGS=-pthread

SRV=sockserver
MAIN=tests-main
TESTS=tests

$(MAIN).o:
	$(CC) $(MAIN).cpp -c

$(SRV).o:
	$(CC) $(CFLAGS) $(LDFLAGS) $(SRV).c -c

test: $(MAIN).o $(SRV).o
	$(CC) $(LDFLAGS) $(MAIN).o $(SRV).o $(TESTS).cpp -o $(TESTS)
	time ./$(TESTS)

all: test
	
clean:
	@rm -f *.o $(TESTS)
