CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to enter: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard

#Assignment 3 Tests below
UT1: unittest1.c dominion.o rngs.o
	gcc -o unittest1 -g unittest1.c dominion.o rngs.o $(CFLAGS)
runUT1: unittest1
	./unittest1 >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out

UT2: unittest2.c dominion.o rngs.o
	gcc -o unittest2 -g unittest2.c dominion.o rngs.o $(CFLAGS)
runUT2: unittest2
	./unittest2 >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out

UT3: unittest3.c dominion.o rngs.o
	gcc -o unittest3 -g unittest3.c dominion.o rngs.o $(CFLAGS)
runUT3: unittest3
	./unittest3 >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out

UT4: unittest4.c dominion.o rngs.o
	gcc -o unittest4 -g unittest4.c dominion.o rngs.o $(CFLAGS)
runUT4: unittest4
	./unittest4 >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out

CT1: cardtest1.c dominion.o rngs.o
	gcc -o cardtest1 -g cardtest1.c dominion.o rngs.o $(CFLAGS)
runCT1: cardtest1
	./cardtest1 >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out

CT2: cardtest2.c dominion.o rngs.o
	gcc -o cardtest2 -g cardtest2.c dominion.o rngs.o $(CFLAGS)
runCT2: cardtest2
	./cardtest2 >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out

CT3: cardtest3.c dominion.o rngs.o
	gcc -o cardtest3 -g cardtest3.c dominion.o rngs.o $(CFLAGS)
runCT3: cardtest3
	./cardtest3 >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out

CT4: cardtest4.c dominion.o rngs.o
	gcc -o cardtest4 -g cardtest4.c dominion.o rngs.o $(CFLAGS)
runCT4: cardtest4
	./cardtest4 >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out

UTCTs: UT1 UT2 UT3 UT4 CT1 CT2 CT3 CT4

unittestresults.out: 
	make UTCTs
	rm -f dominion.gcda
	make runUT1 
	rm -f dominion.gcda
	make runUT2 
	rm -f dominion.gcda
	make runUT3 
	rm -f dominion.gcda
	make runUT4 
	rm -f dominion.gcda
	make runCT1 
	rm -f dominion.gcda
	make runCT2 
	rm -f dominion.gcda
	make runCT3 
	rm -f dominion.gcda
	make runCT4
#End Assignment 3 tests

#Assignment 4 tests below
RTC1: randomtestcard1.c dominion.o rngs.o
	gcc -o randomtestcard1 -g randomtestcard1.c dominion.o rngs.o $(CFLAGS)
runRTC1: randomtestcard1
	./randomtestcard1 >> randomtestcard1.out
	gcov dominion.c -b >> randomtestcard1.out

RTC2: randomtestcard2.c dominion.o rngs.o
	gcc -o randomtestcard2 -g randomtestcard2.c dominion.o rngs.o $(CFLAGS)
runRTC2: randomtestcard2
	./randomtestcard2 >> randomtestcard2.out
	gcov dominion.c -b >> randomtestcard2.out

RTAd: randomtestadventurer.c dominion.o rngs.o
	gcc -o randomtestadventurer -g randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
runRTAd: randomtestadventurer
	./randomtestadventurer >> randomtestadventurer.out
	gcov dominion.c -b >> randomtestadventurer.out

RTs: RTC1 RTC2 RTAd

runRTs:
	make RTs
	rm -f dominion.gcda
	make runRTC1
	rm -f dominion.gcda
	make runRTC2
	rm -f dominion.gcda
	make runRTAd
#End Assignment 4 tests

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe badTestDrawCard
	rm -f unittest1 unittest2 unittest3 unittest4
	rm -f cardtest1 cardtest2 cardtest3 cardtest4
	rm -f randomtestcard1 randomtestcard2 randomtestadventurer

