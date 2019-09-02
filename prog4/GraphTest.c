//GraphTest.c
//Aaron Hom
//awhom
//pa4
//Testing client for Graph ADT

#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
#include"List.h"
#include"Graph.h"

int main(void){
  Graph G = newGraph(8);
  List L = newList();
  printf("Called getOrder(G)\n");
  printf("%d\n", getOrder(G));
  printf("Called getSize(G)\n");
  printf("%d\n", getSize(G));

  printf("Adding edges\n");                               
  addEdge(G, 1, 2);
  addEdge(G, 1, 5);
  addEdge(G, 1, 6);
  addEdge(G, 2, 3);
  addEdge(G, 2, 6);
  addEdge(G, 2, 7);
  addEdge(G, 3, 4);
  addEdge(G, 3, 7);
  addEdge(G, 4, 7);
  addEdge(G, 4, 8);
  addEdge(G, 5, 6);
  addEdge(G, 6, 7);
  addEdge(G, 7, 8);

  printf("Called getOrder(G)\n");
  printf("%d\n", getOrder(G));
  printf("Called getSize(G)\n");
  printf("%d\n", getSize(G));
  printf("Called getParent(G, 5)\n");
  printf("%d\n", getParent(G, 5)); //this is 1

  printf("Called printGraph(stdout, G)\n");
  printGraph(stdout, G);
  printf("Called BFS(G, 3)\n ");
  BFS(G, 3);
  printf("Called getSource(G)\n");
  printf("%d\n", getSource(G)); //this is 3
  printf("Called getPath(L, G, 8)\n ");
  getPath(L, G, 8);
  printf("Called PrintList\n");
  printList(stdout, L);
  printf("\n");

  freeList(&L);
  freeGraph(&G);

  return(0);
}

