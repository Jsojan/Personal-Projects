/******************************************************************************
*
* Joel Sojan, jsojan
* 2022 Spring CSE101 PA3
* FindComponents.c
* Main program for PA3 which uses the Graph ADT
******************************************************************************/

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Graph.h"

// Note my implemenation of checking the input and output files can be opened
// and nonNULL as well as reading in the lines from the input file to an
// integer buffer are borrowed from my own implementation of the same 
// task in FindPath.c from pa2. Furthermore, printing the adjacency list is
// very similar to pa2 FindPath.c which also printed the adjacency list of
// graph G in the exact same manner. Thus, that was also borrowed from my
// own implementation of printing the adjacency list in FindPath.c in pa2.

// Create main function.
int main(int argc, char *argv[]) {
    // Declare need variables.
    char c;
    int size;
    int linecount = 0;
    int counter = 0;
    int n;
    int i = 0;
    int x;
    int y;
    FILE *in;
    FILE *out;
    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");
    
    // Check that there are only three arguments in the function.
    if (argc != 3) {
	printf("Error: Too many or too little arguments given for FindComponents program.\n");
	exit(EXIT_FAILURE);
    }

    // Check the input file for FindComponents program is valid.
    if (argv[1] == NULL || in == NULL) {
	printf("Error: Could not read input file %s or input file is NULL.\n", argv[1]);
	if (out != NULL) {
	    fclose(out);
	}
	exit(EXIT_FAILURE);
    }

    // Check the output file for FindComponents program is valid.
    if (argv[2] == NULL || out == NULL) {
	printf("Error: Could not write to output file %s or output file is NULL.\n", argv[2]);
	if (in != NULL) {
	    fclose(in);
	}
	exit(EXIT_FAILURE);
    }

    // Next, count the number of lines in the input file.
    while ((c = fgetc(in)) != EOF) {
	if (c == '\n') {
	    linecount  += 1;
	}
    }
    
    // Check if input file has no lines.
    if (linecount == 0) {
	printf("Error: Input file was empty and nothing could be read.\n");
	exit(EXIT_FAILURE);
    }

    // Set the size of buffer array for FindComponents.
    size = (2 * linecount) - 1;
    
    int buf[size];

    // Set the position in the file back to the start of the file.

    fseek(in, 0, SEEK_SET);

    // Scan in the first number of input file.
    fscanf(in, "%d\n", &n);

    buf[0] = n;

    // Create a new Graph and list to be used for DFS.

    Graph G = newGraph(buf[0]);
    List S = newList();

    // Create initial stack from 1-n for first stack in DFS() call.

    for (int z = 1; z <= buf[0]; z++) {
	append(S, z);
    }

    // Create a while loop and scan in the edges until 0 0 are read in.

    while (i < size) {
	// Scan in the first two numbers and check if both are not 0 0.
	fscanf(in, "%d %d", &x, &y);

	// Break condition.
	if (x == 0 && y == 0) {
	    break;
	}

	// Store x and y into the buffer only if not 0.
	buf[i] = x;
	buf[i+1] = y;

	addArc(G, x, y);

	// Increment i by 2 since scanning in 2 elements at a time.
	i += 2;
    }
    
    // Print the adjacency list to output file.
    fprintf(out, "Adjacency list representation of G:\n");
    printGraph(out, G);

    // Call DFS twice and initialize transpose of graph G.
    Graph T = transpose(G);

    DFS(G, S);
    DFS(T, S);

    // Check the number of strongly connected components.

    for (int z = 1; z <= n; z++) {
	// Only increment counter if parent is NIL since this
	// implies a Strongly Connected Component of Graph G.
	if (getParent(T, z) == NIL) {
	    counter += 1;
	}
    }
    
    fprintf(out, "\n");
    // Print the number of strongly connected components.
    fprintf(out, "G contains %d strongly connected components:\n", counter);

    // Print out the stronly connected components.
    
    // Move cursor back in List S and create a new List to print out
    // the strongly connectec components.
    moveBack(S);
    List O = newList();
    
    for (int z = 1; z <= counter; z++) {
	fprintf(out, "Component %d: ", z);
        
	// Prepend to List O if the parent of the current vertex is not NIL.
	while (getParent(T, get(S)) != NIL) {
	    prepend(O, get(S));
	    movePrev(S);
	}

	// Otherwise, prepend to the List then print the list since this
	// is the last vertex of the current strongly connected component.
	
	prepend(O, get(S));
	printList(out, O);

	// Then print a new line and clear the List O. Furthermore move
	// the cursor one step towards the Front for next iteration of the 
	// loop.
	
	fprintf(out, "\n");
	clear(O);
	movePrev(S);
    }

    // Free remaining memory.
    freeGraph(&G);
    freeGraph(&T);
    freeList(&S);
    freeList(&O);
    fclose(in);
    fclose(out);

    return(0);
}
