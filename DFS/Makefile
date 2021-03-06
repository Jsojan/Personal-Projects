#------------------------------------------------------------------------------
#
#  Joel Sojan, jsojan
#  Makefile for DFS Program
#  
#  make                    makes all
#  make FindComponents     makes FindComponents
#  make GraphTest          makes GraphTest
#  make clean              removes binaries
#  make checkFind          tests FindComponents for memory leaks
#  make checkTest          tests GraphTest for memory leaks
#------------------------------------------------------------------------------

BASE_SOURCES = Graph.c List.c
BASE_OBJECTS = Graph.o List.o
HEADERS      = Graph.h List.h
COMPILE      = gcc -std=c17 -Wall -c -g
LINK         = gcc -std=c17 -Wall -o 
REMOVE       = rm -f
MEMCHECK     = valgrind --leak-check=full

FindComponents: FindComponents.o $(BASE_OBJECTS)
	$(LINK) FindComponents FindComponents.o $(BASE_OBJECTS)

GraphTest: GraphTest.o $(BASE_OBJECTS)
	$(LINK) GraphTest GraphTest.o $(BASE_OBJECTS)

FindComponents.o: FindComponents.c $(HEADERS)
	$(COMPILE) FindComponents.c

GraphTest.o: GraphTest.c $(HEADERS)
	$(COMPILE) GraphTest.c

$(BASE_OBJECTS): $(BASE_SOURCES) $(HEADERS)
	$(COMPILE) $(BASE_SOURCES)

clean:
	$(REMOVE) FindComponents GraphTest FindComponents.o GraphTest.o $(BASE_OBJECTS)

checkFind: FindComponents
	$(MEMCHECK) ./FindComponents infile1.txt outfile1.txt

checkTest: GraphTest
	$(MEMCHECK) ./GraphTest
