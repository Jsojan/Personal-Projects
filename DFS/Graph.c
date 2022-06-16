/******************************************************************************
*
* Joel Sojan, jsojan
* 2022 Spring CSE101 PA3
* Graph.c
* C file for Graph ADT
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Graph.h"

// Create the private GraphObj type.

typedef struct GraphObj {
    List *adj;
    int *color;
    int *parent;
    int *discover;
    int *finish;
    int order;
    int size;
} GraphObj;

// Constructors and Destructors. This implementation is directly borrowed from
// my own implementation of newGraph() and freeGraph from pa2 which follows
// the same syntax.

Graph newGraph(int n) {
    // Check if n is valid.
    if (n <= 0) {
        printf("Error: Called newGraph() wih size n less than or equal to 0.\n");
	exit(EXIT_FAILURE);
    }

    // Allocate space to Graph G from GraphObj.
    Graph G = malloc(sizeof(GraphObj));

    if (G != NULL) {
        int np = n + 1;
	int x = 1;

	// Allocate memory to adjacency list first.
	G->adj = calloc(np, sizeof(List));

	// Allocate memory to the color array.
	G->color = calloc(np, sizeof(int));

	// Allocate memory to the parent array.
	G->parent = calloc(np, sizeof(int));

	// Allocate memory to the discover array.
	G->discover = calloc(np, sizeof(int));

	// Allocate memory to the finish array.
	G->finish = calloc(np, sizeof(int));

	// Set the default attributes of the Graph for order, size and source.
	G->order = n;
	G->size = 0;
	
	// Create while loop from index 1 all the way to n + 1 elements to
	// create each list of the vertices in G, and set default values of
	// color, parent, discover and finish arrays for each valid vertex
	// index.
	
	while (x < np) {
	    G->adj[x] = newList();
	    G->color[x] = NIL;
	    G->parent[x] = NIL;
	    G->discover[x] = UNDEF;
	    G->finish[x] = UNDEF;

	    // Increment x for each iteration.
	    x += 1;
        }
        
	// Return G if memory allocation was succeful.
	return(G);
    }

    // Else, return G as NULL since memory could not be allocated.
    return(G);
}

// Create destructor function for Graph.

void freeGraph(Graph *pG) {
    if (pG != NULL && *pG != NULL) {
	// Define maximum number of elements to be reset/ freed as order of
	// G plus one since this is equal to n+1 from newGraph().
	
	int tot = (*pG)->order + 1;
	int x = 0;

	// Create while loop to free each list in the adjacency list array 
	// and reset other array values to default values.
	
	while (x < tot) {
	    // Check each adjaceny list ist not NULL before calling freeList().
	    if (&((*pG)->adj[x]) != NULL) {
		// Call freeList() to free List from the adjacency list at
		// index x.

		freeList(&((*pG)->adj[x]));
	    }
            
	    // Increment x regardless of whether List at index x was freed.
	    x += 1;
        }

	// Free remaing attributes of the Graph.
	
	free((*pG)->adj);
	free((*pG)->parent);
	free((*pG)->color);
	free((*pG)->discover);
	free((*pG)->finish);

	// Then free the Graph and set the Graph pointer to NULL.
	
	free(*pG);
	*pG = NULL;
        
	// Return upon succeful freeing of the Graph and its attributes.
	return;
    }

    // Else return if freeing was not successful.
    return;
}

// Access functions.

// This function returns the order of Graph G. The precondition is that Graph
// G is not NULL.

int getOrder(Graph G) {
    if (G == NULL) {
	printf("Error: Called getOrder() on NULL Graph reference.\n");
	exit(EXIT_FAILURE);
    }
    
    // Return the order of Graph G if it's not NULL.
    return(G->order);
}

// This function returns the size of Graph G. The precondition is that Graph
// G is not NULL.

int getSize(Graph G) {
    if (G == NULL) {
	printf("Error: Called getSize() on NULL Graph reference.\n");
	exit(EXIT_FAILURE);
    }

    // Return the size of Graph G if it's not NULL.
    return(G->size);
}

// This function returns the parent of Graph. The preconditions are that Graph
// G is not NULL and 1 <= u <= (n = getOrder(G)).

int getParent(Graph G, int u) {
    if (G == NULL) {
	printf("Error: Called getParent() on NULL Graph reference.\n");
	exit(EXIT_FAILURE);
    }

    if (u > getOrder(G) || u < 1) {
	printf("Error: Called getParent() when vertex u was either greater thanorder of Graph or less than 1.\n");
	exit(EXIT_FAILURE);
    }

    // Return the parent of vertex u in Graph G if G is not NULL and vertex
    // u is in range of the Graph.
    return(G->parent[u]);
}

// This function returns the discovered vertex of u in Graph G. The
// preconditions are that Graph G is not NULL and 1 <= u <= (n = getOrder(G)).

int getDiscover(Graph G, int u) {
    if (G == NULL) {
	printf("Error: Called getDiscover() on NULL Graph reference.\n");
	exit(EXIT_FAILURE);
    }

    if (u > getOrder(G) || u < 1) {
	printf("Error: Called getDiscover() when vertex u was either greater than order of Graph or less than 1.\n");
	exit(EXIT_FAILURE);
    }

    // Return the discovered vertex u in Graph G if G is not NULL and vertex
    // u is in range of the Graph.
    return(G->discover[u]);
}

// This function returns the finished vertex of u in Graph G. The
// preconditions are that Graph G is not NULL and 1 <= u <= (n = getOrder(G)).

int getFinish(Graph G, int u) {
    if (G == NULL) {
	printf("Error: Called getFinish() on NULL Graph reference.\n");
	exit(EXIT_FAILURE);
    }

    if (u > getOrder(G) || u < 1) {
	printf("Error: Called getFinish() when vertex u was either greater than order of Graph or less than 1.\n");
	exit(EXIT_FAILURE);
    }

    // Return the finished vertex of u in Graph G if G is not NULL and vertex
    // u is in range of the Graph.
    return(G->finish[u]);
}

// Manipulation procedures

// Note the implentation of addArc() and addEdge() functions are borrowed from
// my own implementation of these functions from pa2 since they serve the same
// purpose in both assignments so I am citing my own code borrowed from pa2
// for these two functions.

// Create addArc function which adds a direct edge to graph G by adding vertex // v to the adjacency list of u but not vise versa. Preconditions fro this 
// graph are that graph G is not NULL, 1 <= u <= getOrder(G) and 
// 1 <= v <= getOrder(G).

void addArc(Graph G, int u, int v) {
    // Check that the graph G is not NULL.
    if (G == NULL) {
	printf("Error: Called addArc() on NULL Graph reference.\n");
	exit(EXIT_FAILURE);
    }
    // Check if vertex u is in range.
    if (u > getOrder(G) || u < 1) {
	printf("Error: Called addArc() when vertex u was less than 1 or greater than order of graph.\n");
	exit(EXIT_FAILURE);
    }
    // Check if vertex v is in range.
    if (v > getOrder(G) || v < 1) {
	printf("Error: Called addArc() when vertex v was less than 1 or greater than order of graph.\n");
	exit(EXIT_FAILURE);
    }

    // Check if the adjacency list of u is empty then append v if it is.

    if (length(G->adj[u]) == 0) {
	append(G->adj[u], v);
    }

    // Perform a partial insertion sort when appending vertex v to the 
    // ajacency list of u since the adjacency list must be sorted in ascending
    // order for a unique solution.

    else {
	// Move cursor to the back and set a boolean flag.
	moveBack(G->adj[u]);
	bool check = false;

	// Create while loop for each cursor element in the ajacency list
	// until the cursor becomes undefined.
	while(index(G->adj[u]) != -1) {
	    // Check if vertex v is already in the adjacency list of u 
	    // then return if it is.
	    if (get(G->adj[u]) == v) {
		check = true;
		return;
	    }
            
            // Check if vertex v is greater than current cursor element and
	    // insert v after the cursor if it is.

	    if (get(G->adj[u]) < v) {
		insertAfter(G->adj[u], v);
		check = true;

		// break upon inserting the element.
		break;
            }
	    
            // Then move cursor one step towards the front and continue the
	    // loop iteration.
            movePrev(G->adj[u]);
	}

	// Check if element has not been added since the loop. If it hasn't
	// this implies the element must come at the front of the list so 
	// prepend vertex v to the adjacency list of u.
	
	if (check != true) {
	    prepend(G->adj[u], v);
	}
    }
    
    // Increment the Graph G's Edge count by 1.
    G->size += 1;
    return;
}

// Create addEdge function which adds and edge to Graph G by adding u to
// the adjacency list of v and vise versa. The preconditions for this
// function are that the Graph G is not NULL, 1 <= u <= getOrder(G), 
// 1 <= v <= getOrder(G).

void addEdge(Graph G, int u, int v) {
    // Check if Graph G is NULL.
    if (G == NULL) {
	printf("Error: Called addEdge() on NULL Graph reference.\n");
	exit(EXIT_FAILURE);
    }

    // Check if vertex u is in range.
    if (u > getOrder(G) || u < 1) {
	printf("Error: Called addEdge() with vertex u less than 1 or greater than the order of G.\n");
	exit(EXIT_FAILURE);
    }

    // Check if vertex v is in range.
    if (v > getOrder(G) || v < 1) {
	printf("Error: Called addEdge() with vertex v less than 1 or greater than the order of G.\n");
	exit(EXIT_FAILURE);
    }

    // Call addArc twice since this is the same as adding an edge by adding
    // an Arc going to both vertices.

    addArc(G, v, u);
    addArc(G, u, v);

    // Decrement the Graph G's edge count by 1 since calling addArc() twice
    // increases the edges by 2 instead of 1.

    G->size -= 1;
    return;
}

// Perform DFS (Depth First Search) with the function DFS(). A helper function
// called Visit() will also be written and this function is used to vist() 
// a vertex and finish it. Note this implementation of DFS() is credited to the
// DFS algorithm psuedocode provided on the class website under
// Examples/Pseudo-Code/GraphAlgorithms which I borrowed for my own
// implementation. DFS() has the precondition that the
// length(S) == (n = (getOrder(G)).

void Visit(Graph G, List L, int x, int *time) {
    *time += 1;
    G->discover[x] = *time;
    G->color[x] = 1;
    
    // Move cursor to the front of the adjacency list.
    moveFront(G->adj[x]);

    for (int y = 0; y < length(G->adj[x]); y++) {
	if (G->color[get(G->adj[x])] == NIL) {
	    G->parent[get(G->adj[x])] = x;
	    
	    // Recursive Call.
	    Visit(G, L, get(G->adj[x]), time);
	}

	// Move cursor one step back for next iteration.
	moveNext(G->adj[x]);
    }
    
    // Finish the vertex of x at this point.
    G->color[x] = 2;

    // Increment time and then set the finish of vertex x to time.
    *time += 1;

    G->finish[x] = *time;

    // Prepend x to the stack as list L.
    prepend(L, x);

    return;
}

// This is the main DFS function. Preconditions are graph G is not NULL
// and length(S) == (n = getOrder(G)).

void DFS(Graph G, List S) {
    // Check if G is null.
    if (G == NULL) {
        printf("Called DFS() on NULL graph reference.\n");
	exit(EXIT_FAILURE);
    }
    // Check if length(s) == getOrder(G).
    if (length(S) != getOrder(G)) {
	printf("Called DFS() when length of list S was not equal to order of graph.\n");
	exit(EXIT_FAILURE);
    }
    
    // Loop through the adjacency list and set default values. 
    for (int x = 1; x < (getOrder(G) + 1); x++) {
	G->color[x] = NIL;
	G->parent[x] = NIL;
    }

    // Create a new List.
    List M = newList();
    
    // Set time variable at 0.
    int time = 0;

    // Move to the Front of List S.
    moveFront(S);
    
    // Loop through every vertex.
    for (int x = 1; x < (getOrder(G) + 1); x++) {
	if (G->color[get(S)] == NIL) {
	    Visit(G, M, get(S), &time);
	}

        // Move cursor back for next iteration.
        moveNext(S);	
    }

    // Clear List S to update it into the correct order.

    clear(S);
    
    // Move the cursor to the front of M.
    moveFront(M);
    
    // Copy Order of List M into List S.
    for (int x = 0; x < getOrder(G); x++) {
	append(S, get(M));

	// Move cursor every iteration.
	moveNext(M);
    }

    // Free list M.
    freeList(&M);
    return;
}

// Other Functions.

// Create transpose() function which returns a reference to a new graph T
// that is a transpose of the input Graph G. Precondition is that 
// Graph G is not NULL.

Graph transpose(Graph G) {
    // Check if Graph G is NULL.
    if (G == NULL) {
	printf("Error: Called transpose() on NULL Graph reference.\n");
	exit(EXIT_FAILURE);
    }
    
    // Create Transpose Graph T and initialize needed variables.
    Graph T = newGraph(G->order);

    int tot = G->order + 1;
    int x = 1;

    // Create initial while loop to iterate over every vertex.

    while ( x < tot) {
	if (G->adj[x] != NULL) {
	    // Move cursor to the front of current vertex adjacency list.
	    moveFront(G->adj[x]);

	    // Loop through every adjacent vertex in the current vertex
	    // list and add an arc to Graph T in the reverse order, thus
	    // transposing the graph G.
	    
	    for (int y = 1; y < (length(G->adj[x]) + 1); y++) {
		addArc(T, get(G->adj[x]), x);
		moveNext(G->adj[x]);
	    }
	}

	// Increment x regardless.
	x += 1;
    }

    return(T);
}

// Create copyGraph() function which copies the current Graph G into a new
// Graph and preserves the adjacency lists present for each index in the new
// graph. This function also has the precondition that the graph G should not
// be NULL.

Graph copyGraph(Graph G) {
    // Check that G is not NULL.
    if (G == NULL) {
	printf("Error: Called copyGraph() on NULL Graph reference.\n");
	exit(EXIT_FAILURE);
    }

    // Create new Graph with the same order as graph G.
    Graph H = newGraph(G->order);

    // Create needed loop variables.
    int x = 1;
    int tot = G->order + 1;

    // Create while loop which loops through every vertex in Graph G and 
    // copies its adjacency list for each vertex to the same list (same index)
    // in the new Graph to effectively copy the Graph.

    while ( x < tot) {
        if (G->adj[x] != NULL) {
	    // Call freeList on this and then set 
	    freeList(&((H)->adj[x]));
	    ((H)->adj[x]) = copyList(G->adj[x]);
	}

	// Increment x regardless.
	x += 1;
    }
    
    // return H as the new copied Graph.
    return(H);
}

// Create printGraph()  function which prints out the adjacency list 
// representation of the Graph. The precondition of this function is
// that the graph G is not NULL. Note this implementation of printGraph()
// follows my own implementation of printGraph from pa2.

void printGraph(FILE* out, Graph G) {
    // Check that the graph G is not Null.
    if (G == NULL) {
	printf("Error: Called printGraph() on NULL Graph reference.\n");
	exit(EXIT_FAILURE);
    }
    
    // Start Loop with variables for index 1 all the way to the order of
    // the graph G.
    int x = 1;
    int tot = getOrder(G) + 1;

    while (x < tot) {
        fprintf(out, "%d: ", x);

	// Then print out the adjacency list of the current index x.
	printList(out, G->adj[x]);
	fprintf(out, "\n");

	// Increment x by 1.
	x += 1;
    }

    return;
}
