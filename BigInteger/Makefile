#------------------------------------------------------------------------------
#
# Joel Sojan, jsojan
#
# This is the Makefile used for the BigInteger and List ADT program
#
# make all                        makes all neccesary objects for PA6
# make BigIntegerTest             makes BigIntegerTest
# make ListTest                   makes ListTest
# make clean                      removes all binaries
# make checkArithmetic            runs Arithmetic in valgrind on in4 junk4
# make checkBigInteger            runs BigIntegerTest in valgrind
# make checkList                  runs ListTest in valgrind
#------------------------------------------------------------------------------

all: BigIntegerTest ListTest Arithmetic

BigIntegerTest: BigIntegerTest.o BigInteger.o List.o
	g++ -std=c++17 -Wall -o BigIntegerTest BigIntegerTest.o BigInteger.o List.o -g 

ListTest: ListTest.o List.o
	g++ -std=c++17 -Wall -o ListTest ListTest.o List.o -g

Arithmetic: Arithmetic.o BigInteger.o List.o
	g++ -std=c++17 -Wall -o Arithmetic Arithmetic.o BigInteger.o List.o -g 

Arithmetic.o: Arithmetic.cpp BigInteger.h List.h
	g++ -std=c++17 -Wall -c Arithmetic.cpp -g

BigIntegerTest.o: BigIntegerTest.cpp BigInteger.cpp List.h
	g++ -std=c++17 -Wall -c BigIntegerTest.cpp -g

ListTest.o: ListTest.cpp List.h
	g++ -std=c++17 -Wall -c ListTest.cpp -g

List.o: List.cpp List.h
	g++ -std=c++17 -Wall -c List.cpp -g

BigInteger.o: BigInteger.h BigInteger.cpp
	g++ -std=c++17 -Wall -c BigInteger.cpp -g

clean:
	rm -f Arithmetic Arithmetic.o ListTest ListTest.o List.o BigIntegerTest BigIntegerTest.o BigInteger.o

checkList:
	valgrind --leak-check=full ./ListTest

checkTest:
	valgrind --leak-check=full ./BigIntegerTest

checkArithmetic:
	valgrind --leak-check=full ./Arithmetic infile4.txt junk4
