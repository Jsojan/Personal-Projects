## Depth First Search (DFS) Program (README.md)

## Short Description
    This program will perform DFS (Depth First Search) on a created graph G by passing in the size of the graph, its directed edges (arcs) and a List S that serves as the stack for DFS. From the input file, the adjacency list representation of the Graph G will be printed, the number of strongly connected componentsand each strong connect components of graph G by calling DFS() on the graph G and the transpose of Graph G. 

## Build
    To manually build this program, first type "make" which will build the necessaery objects for compiling and executing the program. Next run "make FindComponents" to build the main file as FindComponents.c. Also, "make GraphTest" will build the necessary objects for running GraphTest.c which is a file that testsall the Graph ADT functions. Furthermore, "make clean" removes any created files or executables made from the Makefile as a way to clean up the program. Next,"make checkFind" runs valgrind on FindComponents for a default input and output file for checking memory leaks. Also "make checkTest" runs valgrind and checks if the GraphTest file has memory leaks when executing the program.

## Running
    ./FindComponents (input file name here) (output file name here)
    ./GraphTest

    Note, running the FindComponents program requires an input file and an output file where the input file has the first line be an integer stating the size of the graph and the proceeding lines for creating edges be numbers between 1 and the first line of the input file's range of numbers inclusive. This is then followed by a 0 0 to signify the end of the input file. The output file should be opened without failure so that FindComponents.c can perform the correct operations and return the strongly connected Components of Graph G into the output file.

## Error Handling
    This program should not return errors since it has been thoroughly tested. For further checking run 'make checkFind' and 'make checkTest' to show that the program runs exactly as intended an no errors are thrown from valgrind.

## Cleaning
    For cleaning the files, type "make clean" to remove any additional files that were created by the Makefile to clean it.
