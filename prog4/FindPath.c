//FindPath.c
//Aaron Hom
//awhom 
//pa4
//Finds shortest paths using graph ADT

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "Graph.h"

#define MAX_LEN 500

int main(int argc, char* argv[]){

  FILE *in;
  FILE *out;
  char words[MAX_LEN];

  if(argc != 3){
    printf("FindPath Error: Wrong number of arguments: %s <in file> <out file>\n", argv[0]);
    exit(1);
  }

  in = fopen(argv[1], "r"); //opens file for reading
  out = fopen(argv[2], "w"); //opens file for writing
  if(in == NULL){
    printf("FindPath Error: Cannot open file %s for reading\n", argv[1]);
    exit(1);
  }
  if(out == NULL){
    printf("FindPath Error: Cannot open file %s for writing\n", argv[2]);
    exit(1);
  }

  int size = 0;
  fgets(words, MAX_LEN, in); //reads in file
  sscanf(words, "%d", &size); //scans in file

  Graph G = newGraph(size);
  while(fgets(words, MAX_LEN, in) != NULL){ //scans until end of file
    int x = 0, y = 0; 
    sscanf(words, "%d %d", &x, &y); 
    if(x == 0 && y == 0){
      break;
    }
    addEdge(G, x, y); //adds undirected edge between x and y
  }
  printGraph(out, G); //prints out graph

  int check = 0;
  while(fgets(words, MAX_LEN, in) != NULL){ //scans until end of file
    int x = 0, y = 0;
    sscanf(words, "%d %d", &x, &y); 
    if(x == 0 && y == 0){
      break;
    }
    if(check++ != 0){
      fprintf(out, "\n"); 
    }
    fprintf(out, "\n");
    BFS(G, x); //performs BFS 
    int distance = getDist(G, y); //find distance from source to y
    fprintf(out, "The distance from %d to %d is ", x, y);
    if(distance == INF){
      fprintf(out, "infinity\n");
    }else{
      fprintf(out, "%d\n", distance);
    }
    List L = newList();
    getPath(L, G, y); //finds path from source to y
    if(front(L) == NIL){
      fprintf(out, "There does not exist a %d-%d path", x, y);
    }else{
      fprintf(out, "The shortest %d-%d path is: ", x, y);
      printList(out, L);
    }
    freeList(&L);
  }
  fprintf(out, "\n"); //new line
  freeGraph(&G); //free graph G

  fclose(in); //close in file
  fclose(out); //close out file
  return(0);
}
