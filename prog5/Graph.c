//Graph.c
//Aaron Hom
//awhom
//pa5
//Graph ADT used to perform operations on graphs

#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "Graph.h"

//Color scale for DFS
#define white 1
#define gray 2
#define black 3

struct GraphObj{
  List *adj;
  int *color;
  int *parent;
  int *discover;
  int *finish;
  int order;
  int size;
};

//Constructors-Destructors -------------------------------
//Graph()
//Creates a new graph that has n vertices and no edges
Graph newGraph(int n){
  Graph G = malloc(sizeof(struct GraphObj)); //allocate memory for all parts of graph
  G->adj = calloc(n + 1, sizeof(List));
  G->color = calloc(n + 1, sizeof(int));
  G->parent = calloc(n + 1, sizeof(int));
  G->discover = calloc(n + 1, sizeof(int));
  G->finish = calloc(n + 1, sizeof(int));;
  G->order = n;
  G->size = 0;
  for(int i = 0; i < (n+1); i++){ //makes graph
    G->adj[i] = newList();
    G->color[i] = white;
    G->parent[i] = NIL;
    G->discover[i] = UNDEF;
    G->finish[i] = UNDEF;
  }
 return G;
}

//freeGraph()
//Frees all dynamic memory associated with *pG and sets *pG to null
void freeGraph(Graph* pG){
  Graph useless = *pG;
  for(int i = 0; i < (useless->order + 1); i++){
    freeList(&(useless->adj[i]));
  }
  free(useless->adj);
  free(useless->color);
  free(useless->parent);
  free(useless->discover);
  free(useless->finish);
  free(*pG);
  *pG = NULL;
}

//Access Functions ---------------------------------------
//getOrder()
//Returns number of vertices in graph
int getOrder(Graph G){
  return G->order;
}

//getSize()
//Returns number of edges in graph
int getSize(Graph G){
  return G->size;
}

//getParent()
//Returns parent of given vertex (u) from graph G
//Pre: 1 <= u <= n, 1 <= v <= n
int getParent(Graph G, int u){
  if(u > getOrder(G) || u < 1){
    printf("Graph Error: called getParent() with out of bounds vertex\n");
    exit(1);
  }
  return G->parent[u];
}

//getDiscover()
//Returns dicovery time of target vertex (u)
//Pre: 1 <= u <= n = getOrder(G)
int getDiscover(Graph G, int u){
  if(u > getOrder(G) || u < 1){
    printf("Graph Error: called getDiscover() with out of bounds vertex\n");
    exit(1);
  }
  return G->discover[u];
}

//getFinish()
//Returns finish time of target vertex (u)
//Pre: 1 <= u <= n = getOrder(G)
int getFinish(Graph G, int u){
  if(u > getOrder(G) || u < 1){
    printf("Graph Error: called getFinish() with out of bounds vertex\n");
    exit(1);
  }
  return G->finish[u];
}

//Manipulation Procedures---------------------------------
//addEdge()
//Adds an undirected edge to graph from vertex u to vertex g
//Pre: 1 <= u & v <= getOrder(G)
void addEdge(Graph G, int u, int v){
  if(u > getOrder(G)||v > getOrder(G)||u < 1|| v < 1){
    printf("Graph Error: called addEdge() with out of bounds vertice(s)\n");
    exit(1);
  }
  addArc(G, u, v); //adds directed edges in both directions to link vertices
  addArc(G, v, u);
  G->size--; //decrease # of edges
}

//addArc()
//Adds a directed edge to graph from vertex u to vertex g
//Pre: 1 <= u & v <= getOrder(G)
void addArc(Graph G, int u, int v){
  if(u > getOrder(G)||v > getOrder(G)||u < 1|| v < 1){
    printf("Graph Error: called addEdge() with out of bounds vertice(s)\n");
    exit(1);
  }
  List L = G->adj[u];
  moveFront(L);
  while(index(L) > -1 && v > get(L)){
    moveNext(L); //move through list
  }
  if(index(L) == -1){ //once out of bounds
    append(L, v); //add v to beginning of list
  }else{
    insertBefore(L, v);
  }
  G->size++; //increase # of edges
}

//Visit()
//Adds directed edge in G from u to v (helper function for DFS())
//Pre: 1 <= u <= getOrder(G), 1 <= v <= getOrder(G)
void Visit(Graph G, List S, int u, int *t){
  G->color[u] = gray;
  G->discover[u] = ++*t;
  moveFront(G->adj[u]);
  while(index(G->adj[u]) >= 0){
    int v = get(G->adj[u]);
    if(G->color[v] == white){
      G->parent[v] = u;
      Visit(G, S, v, t);
    }
    moveNext(G->adj[u]);
  }
  G->color[u] = black;
  G->finish[u] = ++*t;
  prepend(S, u);
}

//DFS()
//Performs DFS with vertices in List L
void DFS(Graph G, List S){
  if(length(S) != getOrder(G)){
    printf("Graph Error: called DFS() with mismatched sizes of list/graph");
    exit(1);
  }
  for(int i = 1; i <= getOrder(G); i++){
    G->color[i] = white;
    G->parent[i] = NIL;
    G->discover[i] = UNDEF;
    G->finish[i] = UNDEF;
  }
  int t = 0;
  moveFront(S);
  while(index(S) >= 0){
    int u = get(S);
    if(G->color[u] == white){
      Visit(G, S, u, &t);
    }
    moveNext(S);
  }
  for(int size = length(S)/2; size > 0; size--){
    deleteBack(S);
  }
}

//Other operations ---------------------------------------
//transpose()
//Transposes target graph
Graph transpose(Graph G){
  Graph trans = newGraph(getOrder(G));
  for(int i = 1; i <= getOrder(G); i++){
    moveFront(G->adj[i]);
    while(index(G->adj[i]) >= 0){
      addArc(trans, get(G->adj[i]), i);
      moveNext(G->adj[i]);
    }
  }
  return trans;
}

//copyGraph()
//Copies target graph and returns it
Graph copyGraph(Graph G){
  Graph dupe = newGraph(getOrder(G));
  for(int i = 1; i <= getOrder(G); i++){
    moveFront(G->adj[i]);
    while(index(G->adj[i]) >= 0){
      addArc(dupe, i, get(G->adj[i]));
      moveNext(G->adj[i]);
    }
  }
  return dupe;
}

//printGraph()
//Prints graph to an out file using iteration to print out each adjacency list
void printGraph(FILE* out, Graph G){
  if(G == NULL||out == NULL){
    printf("Graph Error: called printGraph() on null reference(s)\n");
    exit(1);
  }
  for(int i = 1; i <= getOrder(G); i++){
    fprintf(out, "%d: ", i);
    printList(out, G->adj[i]);
    fprintf(out, "\n");
  }
}
