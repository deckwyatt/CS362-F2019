CFLAGS= -Wall -fpic -coverage -lm -std=c99

testme: testme.c
	gcc -o testme testme.c -g $(CFLAGS) -ftest-coverage -fprofile-arcs
	./testme
	gcov -bf testme

clean:
	rm -f *.o *.exe  *.gcov *.gcda *.gcno *.so *.out
