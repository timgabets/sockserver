CC=g++
CFLAGS=-std=c++11 -g
LDFLAGS=-pthread

SRV=sockserver
MAIN=tests-main
TESTS=tests

all: test

test: $(MAIN) $(SRV) $(TESTS).c
	$(CC) $(LDFLAGS) obj/*.o $(TESTS).c -o $(TESTS)
	time ./$(TESTS)

$(MAIN): $(MAIN).c
	$(CC) -c $(MAIN).c -o obj/$(MAIN).o

$(SRV): $(SRV).c
	$(CC) $(CFLAGS) $(LDFLAGS) -c $(SRV).c -o obj/$(SRV).o

clean:
	@rm -f obj/*.o $(TESTS)
