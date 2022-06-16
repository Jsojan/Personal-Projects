/******************************************************************************
*
* Joel Sojan, jsojan
* 
* GraphTest.c
* C file for testing the Graph ADT functions.
******************************************************************************/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Graph.h"

int main(int argc, char* argv[]) {
    int n = 10;
    int o = 5;
    int i;

    // Call newGraph and newList G and S.

    Graph G = newGraph(n);
    List L = newList();

    for (int i = 1; i <= n; i++) {
	append(L, i);
    }

    addEdge(G, 1, 2);
    addArc(G, 2, 5);
    addArc(G, 5, 4);
    addArc(G, 4, 5);
    addArc(G, 1, 8);
    addArc(G, 1, 6);
    addArc(G, 6, 6);
    addArc(G, 6, 8);
    addArc(G, 3, 8);
    addArc(G, 7, 8);
    addArc(G, 10, 7);
    addEdge(G, 9, 10);
    addArc(G, 9, 3);
    addArc(G, 3, 5);
    addArc(G, 3, 2);
    addArc(G, 2, 8);
    addArc(G, 9, 4);
    
    // Print the adjacency list representation.
    printGraph(stdout, G);

    // Check CopyGraph works by printing it.
    Graph C = copyGraph(G);
    
    printf("This is the copied graph from Graph G.\n");

    printGraph(stdout, C);

    // Check if getOrder, getSize, and getParent function works.
    printf("This is the value of the order of the Graph: %d\n", getOrder(G));

    printf("This is the value of the size of the Graph: %d\n", getSize(G));

    // Call DFS Function on Graph G with list L for the first time.

    DFS(G, L);
    printf("\n");
    printf("x: distance finish  parent\n");
    for (i=1; i <=n; i++) {
	printf("%d: %2d  %2d  %2d\n", i, getDiscover(G, i), getFinish(G, i), getParent(G, i));
    }
    printf("\n");

    printf("This is the topological sort of the stack S.\n");
    printList(stdout, L);
    printf("\n");

    // Check that the Transpose Graph and DFS on transpose works.
    Graph T = transpose(G);

    DFS(T, L);

    printf("\n");
    printf("This is the transpose of Graph G.\n");
    printGraph(stdout, T);
    printf("x: distance finish  parent\n");

    for (int x = 1; x <=n; x++) {
        printf("%d: %2d  %2d  %2d\n", x, getDiscover(G, x), getFinish(G, x), getParent(G, x));
    }
    printf("\n");
    printf("This is the topological sort of the stack S after DFS() on transpose.\n");
    printList(stdout, L);
    printf("\n");

    printf("Begin next test on a different but simpler graph.\n");
    
    Graph H = newGraph(o);
    List M = newList();
    
    for (int i = 1; i <= o; i++) {
        append(M, i);
    }

    addArc(H, 1, 2);
    addArc(H, 1, 3);
    addArc(H, 2, 3);
    addEdge(H, 3, 4);
    addArc(H, 1, 4);
    addEdge(H, 2, 5);
    addArc(H, 3, 5);
    addArc(H, 4, 3);

    printf("\n");
    printf("This is the current graph of H.\n");
    printGraph(stdout, H);

    // Check the order and size of the new graph are correct.

    printf("This is the value of the order of the Graph H: %d\n", getOrder(H));

    printf("This is the value of the size of the Graph H: %d\n", getSize(H));
    
    // Check DFS works for a smaller example.

    DFS(H, M);
    printf("\n");
    printf("x: distance finish  parent\n");
    for (i=1; i <= o; i++) {
        printf("%d: %2d  %2d  %2d\n", i, getDiscover(H, i), getFinish(H, i), getParent(H, i));
    }
    printf("\n");

    printf("This is the topological sort of the stack S.\n");
    printList(stdout, M);
    printf("\n");

    // Create transpose of the current Graph and debug this.
    
    printf("Call transpose to test the functions again.\n");
    Graph R = transpose(H);
    
    // Call DFS function on the function.
    DFS(R, M);

    printf("Begin testing transpose function on smaller graph.\n");
    for (i=1; i <= o; i++) {
        printf("%d: %2d  %2d  %2d\n", i, getDiscover(R, i), getFinish(R, i), getParent(R, i));
    }
    printf("\n");

    printf("This is the topological sort of the stack S.\n");
    printList(stdout, M);
    printf("\n");

    // Check the properties of the transpose of Graph H.

    printf("This is the value of the order of the transpose Graph R: %d\n", getOrder(R));

    printf("This is the value of the size of the transpose Graph R: %d\n", getSize(R));
    
    // End the tests.
    printf("This should be the end of the GraphTest.c\n");

    
    // Free extra memory
    freeGraph(&G);
    freeGraph(&H);
    freeGraph(&R);
    freeGraph(&C);
    freeGraph(&T);
    freeList(&L);
    freeList(&M);

    return(0);
}
