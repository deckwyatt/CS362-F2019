CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc --coverage -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

unittest1: dominion.o unittest1.c
	gcc -o unittest1 unittest1.c -g dominion.o rngs.o $(CFLAGS) -ftest-coverage -fprofile-arcs

unittest2: dominion.o unittest2.c
	gcc -o unittest2 unittest2.c -g dominion.o rngs.o $(CFLAGS) -ftest-coverage -fprofile-arcs

unittest3: dominion.o unittest3.c
	gcc -o unittest3 unittest3.c -g dominion.o rngs.o $(CFLAGS) -ftest-coverage -fprofile-arcs

unittest4: dominion.o unittest4.c
	gcc -o unittest4 unittest4.c -g dominion.o rngs.o $(CFLAGS) -ftest-coverage -fprofile-arcs

unittest5: dominion.o unittest5.c
	gcc -o unittest5 unittest5.c -g dominion.o rngs.o $(CFLAGS) -ftest-coverage -fprofile-arcs

runut1: unittest1
	./unittest1
	gcov -bf unittest1

runut2: unittest2
	./unittest2
	gcov -bf unittest2

runut3: unittest3
	./unittest3
	gcov -bf unittest3

runut4: unittest4
	./unittest4
	gcov -bf unittest4

runut5: unittest5
	./unittest5
	gcov -bf unittest5

unittests: unittest1 unittest2 unittest3 unittest4 unittest5
	./unittest1
	./unittest2
	./unittest3
	./unittest4
	./unittest5
	gcov -bf unittest1
	gcov -bf unittest2
	gcov -bf unittest3
	gcov -bf unittest4
	gcov -bf unittest5

runrt1: randomtest1
	./randomtestcard1
	gcov -bf randomtestcard1

runrt2: randomtest2
	./randomtestcard2
	gcov -bf randomtestcard2

runrt3: randomtest3
	./randomtestcard3
	gcov -bf randomtestcard3

random: randomtest1 randomtest2 randomtest3
	./randomtestcard1
	./randomtestcard2
	./randomtestcard3
	gcov -bf randomtestcard1
	gcov -bf randomtestcard2
	gcov -bf randomtestcard3

randomtest1: dominion.o randomtestcard1.c
	gcc -o randomtestcard1 randomtestcard1.c -g dominion.o rngs.o $(CFLAGS) -ftest-coverage -fprofile-arcs

randomtest2: dominion.o randomtestcard2.c
	gcc -o randomtestcard2 randomtestcard2.c -g dominion.o rngs.o $(CFLAGS) -ftest-coverage -fprofile-arcs

randomtest3: dominion.o randomtestcard3.c
	gcc -o randomtestcard3 randomtestcard3.c -g dominion.o rngs.o $(CFLAGS) -ftest-coverage -fprofile-arcs

unittestresults: unittest1 unittest2 unittest3 unittest4 unittest5 randomtest1 randomtest2 randomtest3
	./unittest1
	./unittest2
	./unittest3
	./unittest4
	./unittest5
	./randomtestcard1
	./randomtestcard2
	./randomtestcard3
	gcov -bf unittest1
	gcov -bf unittest2
	gcov -bf unittest3
	gcov -bf unittest4
	gcov -bf unittest5
	gcov -bf randomtestcard1
	gcov -bf randomtestcard2
	gcov -bf randomtestcard3

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player

clean:
	rm -f *.o *.exe playdom player  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
