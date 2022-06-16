//---------------------------------------------------------------------------- 
//
// Joel Sojan, jsojan
// 2022 Spring CSE101 PA6
// PA6 README.md
// This is the README for PA6 on how to build and run the program.
//-----------------------------------------------------------------------------

## CSE 101 Programming Assignment 6 (README.md)

## Short Description
    This program will perform numeric operations that include addition, subtracction and multiplication of very large numbers using a list representation of said large numbers where the elements are of type long. Thus, this assignment utilizes a BigInteger ADT and the List ADT utilized from programming assignment 5for its implementation. Furthermore, for the add, subtract and multiplication operations involve the need of helper functions such as sum List, normalize, scalarmult and negate List which will be used extensively for the main operations of this assignment. The main file that returns a result of operations given two Big Integers A and B to a specified output file from a valid input file is Arithmetic.cpp.

## Build
    To manually build this program, first type "make" which will make all the needed objects for compiling this program. Also "make checkList" will run the ListTest programa and check if it has memory leaks in the program. Furthermore, "make checkTest" will run the BigIntegerTest.cpp and check that it has no memory leaks using valgrind. Moreover, "make checkArithmetic" will run the main file for any memory leaks using valgrind. In addiiton, "make clean" removes any created files or executables made from the Makefile as a way to clean up the program.

## Running
    ./Arithmetic (valid input file) (valid output file)
    ./BigIntegerTest
    ./ListTest
    
    Note that running the Arithmetic program requires a valid input file that can be opened and has exactly three lines where the first line is a valid integer, the second is an empty line, and the last line is also a valid integer. Furthermore, the output file must also be opened else the program will return an error if it can't open the file.

## Credit
    Note I attended TA Andrew Gavgavians TA sections on Wednesday and Friday on 5/11/22 and 5/13/22 for help with certain functions and operator overloading. Furthermore, I attended TA Norton's tutoring session on 5/13/22 on Zoom for help with my sumList, normalize and scalarMult helper functions which are used extensively in this program.

## Error Handling
    This program should not return any errors since it has been thoroughly tested using the provided grading script from the CSE101 class Ed discussion post. For further checking, running valgrind on Arithmetic.cpp for any valid input file and output file, BigIntegerTest.cpp and ListTest.cpp should also not return any errors.

## Cleaning
    For cleaning the files, type "make clean" to remove any additional files that were created by the Makefile to clean it.
