//GraphTest.c
//Aaron Hom
//awhom
//pa5
//Testing client for Graph ADT

#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
#include"List.h"
#include"Graph.h"

int main(void){
  Graph G = newGraph(8);
  Graph trans = NULL;
  Graph dupe = NULL;
  List L = newList();

  printf("Called getOrder(G)\n");
  printf("%d\n", getOrder(G));
  printf("Called getSize(G)\n");
  printf("%d\n", getSize(G));

  for(int i = 1; i <= 8; i++){
    append(L, i);
  }

    addArc(G, 1, 2);
    addArc(G, 1, 5);
    addArc(G, 1, 6);
    addArc(G, 2, 3);
    addArc(G, 2, 6);
    addArc(G, 2, 7);
    addArc(G, 3, 4);
    addArc(G, 3, 7);
    addArc(G, 4, 7);
    addArc(G, 4, 8);
    addArc(G, 5, 6);
    addArc(G, 6, 7);
    addArc(G, 7, 8);
    addArc(G, 8, 5);

    printf("Called getOrder(G)\n");
    printf("%d\n", getOrder(G));
    printf("Called getSize(G)\n");
    printf("%d\n", getSize(G));

    printf("Called printGraph(stdout, G)\n");
    printGraph(stdout, G);

    printf("Called DFS(G, L)\n");
    DFS(G, L);

    printf("Called getDiscover(G, 4)\n");
    printf("%d\n", getDiscover(G, 4));

    printf("Called getFinish(G, 4)\n");
    printf("%d\n", getFinish(G, 4));

    printf("Called PrintList\n");
    printList(stdout, L);

    dupe = copyGraph(G);
    trans = transpose(G);
  
    printf("Called printGraph(dupe)\n");
    printGraph(stdout, dupe);

    printf("Called printGraph(trans)\n");
    printGraph(stdout, trans);

    freeList(&L);
    freeGraph(&G);

    return(0);
  }
