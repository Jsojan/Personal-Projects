/*******************************************************************************
* Joel Sojan, jsojan
* 
* Graph.h
* Header file for Graph ADT
******************************************************************************/

#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#include "List.h"

// Include Macro definition for UNDEF and NIL.

#define UNDEF -1
#define NIL 0

// Graph ADT creation.

typedef struct GraphObj* Graph;

// Constructors-Destructors

// This function constructs a new graph.
Graph newGraph(int n);

// This function serves as the destructor for the Graph
// and sets the pointer to the Graph to NULL.
void freeGraph(Graph* pG);

// Access functions

// Returns the order of graph G. Precondition is that Graph G is not
// NULL.
int getOrder(Graph G);

// Returns the size of Graph G. Precondition is that Graph G is not
// NULL.
int getSize(Graph G);

// Returns the Parent of Graph G. Preconditions are that the Graph G is
// not NULL and 1 <= u <= (n = getOrder(G)).
int getParent(Graph G, int u);

// Returns the Discovered vertex of Graph G. Preconditions are that the
// Graph G is not null and 1 <= u <= (n = getOrder(G)).
int getDiscover(Graph G, int u);

// Returns the Finished vertex of Graph G. Preconditions are that the
// Graph G is not null and 1 <= u <= (n = getOrder(G)).
int getFinish(Graph G, int u);

// Manipulation procedures

// Add an Arc to graph G by adding vertex v to the adjacency list of u but
// not vise versa. Preconditions are that the Graph G is not NULL
// and 1 <= u <= (n = getOrder(G)) and 1 <= v <= (n = getOrder(G)).

void addArc(Graph G, int u, int v);

// Add an Edge to graph G by adding vertex v to the adjacency list of u
// and vise versa. Preconditions are that the Graph G is not NULL
// and 1 <= u <= (n = getOrder(G)) and 1 <= v <= (n = getOrder(G)).

void addEdge(Graph G, int u, int v);

// Perform Depth First Search in this function. Preconditions are that
// the Graph G is not NULL and the length(S) == getOrder(G).

void DFS(Graph G, List S);

// Other functions.

// Creates the transpose of Graph G. Precondition is that Graph G is
// not NULL.

Graph transpose(Graph G);

// Copies the graph G into a new graph. Precondition is that Graph G is
// not NULL.

Graph copyGraph(Graph G);

// Prints out the Graph G as an adjacency list representation. Precondition
// is that Graph G is not NULL.

void printGraph(FILE* out, Graph G);

