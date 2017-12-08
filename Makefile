CC=g++
CFLAGS=-std=c++11 -g
LDFLAGS=-pthread

SRV=sockserver
MAIN=tests-main
TESTS=tests

all: test

test: $(MAIN).o $(SRV).o $(TESTS).c
	$(CC) $(LDFLAGS) $(MAIN).o $(SRV).o $(TESTS).c -o $(TESTS)
	time ./$(TESTS)


$(MAIN).o: $(MAIN).c
	$(CC) $(MAIN).c -c

$(SRV).o: $(SRV).c
	$(CC) $(CFLAGS) $(LDFLAGS) $(SRV).c -c


clean:
	@rm -f *.o $(TESTS)
