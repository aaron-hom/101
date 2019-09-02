//FindComponents.c
//Aaron Hom
//pa5
//Determines strong components and prints to out file topologically 

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

  List S = newList();
  for(int k = 1; k <= size; k++){
    append(S, k);
  }

  Graph G = newGraph(size);
  while(fgets(words, MAX_LEN, in) != NULL){ //scans until end of file
    int x = 0, y = 0;
    sscanf(words, "%d %d", &x, &y);
    if(x == 0 && y == 0){
      break;
    }
    addArc(G, x, y); //adds undirected edge between x and y
  }

  DFS(G, S); //performs DFS on G
  Graph trans = transpose(G); //transposes G
  int StrConComp = 0; //int to keep track of strongly connected components 
  DFS(trans, S); //performs DFS on trans(G) 
  moveFront(S); 
  while(index(S) >= 0){ //finds strongly connected components
    if(getParent(trans, get(S)) == NIL){
      StrConComp++;
    }
    moveNext(S);
  } 
  List Strong[StrConComp]; //makes new list for strongly connected components 
  for(int i = 0; i < StrConComp; i++){
    Strong[i] = newList();  
  }
  moveFront(S);
  int temp = StrConComp; 
  while(index(S) >= 0){ 
    if(getParent(trans, get(S)) == NIL){  
      temp--;
    }
    if(temp == StrConComp){
      break;
    }
    append(Strong[temp], get(S));
    moveNext(S);
  }

  fprintf(out, "Adjacency list representation of G:\n");
  printGraph(out, G); //prints adj list of G
  fprintf(out, "\nG contains %d strongly connected components:", StrConComp); //reports how many SCCs were found
  for(int j = 0; j < StrConComp; j++){
    fprintf(out, "\nComponent %d: ", (j+1));
    printList(out, Strong[j]);
    freeList(&(Strong[j]));
  }
  fprintf(out, "\n"); //new line
  freeGraph(&G); //free graphs and lists
  freeGraph(&trans);
  freeList(&S);

  fclose(in); //close in file
  fclose(out); //close out file
  return(0);
}
