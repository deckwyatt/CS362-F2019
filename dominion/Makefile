CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

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

randomtest1: dominion.o randomtestcard1.c
	gcc -o randomtestcard1 randomtestcard1.c -g dominion.o rngs.o $(CFLAGS) -ftest-coverage -fprofile-arcs

randomtest2: dominion.o randomtestcard2.c
	gcc -o randomtestcard2 randomtestcard2.c -g dominion.o rngs.o $(CFLAGS) -ftest-coverage -fprofile-arcs

randomtest3: dominion.o randomtestcard3.c
	gcc -o randomtestcard3 randomtestcard3.c -g dominion.o rngs.o $(CFLAGS) -ftest-coverage -fprofile-arcs

randomtestresults: randomtest1 randomtest2 randomtest3
	./randomtestcard1
	./randomtestcard2
	./randomtestcard3
	gcov -bf randomtestcard1
	gcov -bf randomtestcard2
	gcov -bf randomtestcard3

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player

clean:
	rm -f *.o *.exe playdom player *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
