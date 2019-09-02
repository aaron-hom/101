//Graph.h
//Aaron Hom
//pa5
//Header file for Graph ADT

#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <stdio.h>
#include "List.h"

#define NIL 0
#define UNDEF -1

typedef struct GraphObj* Graph;

//Constructors-Destructors -------------------------------
//Graph()
//Creates a new graph that has n vertices and no edges
Graph newGraph(int n);

//freeGraph()
//Frees all dynamic memory associated with *pG and sets *pG to null
void freeGraph(Graph* pG);

//Access Functions ---------------------------------------
//getOrder()
//Returns number of vertices in graph
int getOrder(Graph G);

//getSize()
//Returns number of edges in graph
int getSize(Graph G);

//getParent()
//Returns parent of given vertex (u) from graph G
//Pre: 1 <= u <= n, 1 <= v <= n
int getParent(Graph G, int u);

//getDiscover()
//Returns dicovery time of target vertex (u)
//Pre: 1 <= u <= n = getOrder(G)
int getDiscover(Graph G, int u);

//getFinish()
//Returns finish time of target vertex (u)
//Pre: 1 <= u <= n = getOrder(G)
int getFinish(Graph G, int u);

//Manipulation Procedures---------------------------------
//addEdge()
//Adds an undirected edge to graph from vertex u to vertex g
//Pre: 1 <= u & v <= getOrder(G)
void addEdge(Graph G, int u, int v);

//addArc()
//Adds a directed edge to graph from vertex u to vertex g
//Pre: 1 <= u & v <= getOrder(G)
void addArc(Graph G, int u, int v);

//DFS()
//Performs DFS with vertices in List L
void DFS(Graph G, List S);

//Other operations ---------------------------------------
//transpose()
//Transposes target graph
Graph transpose(Graph G);

//copyGraph()
//Copies target graph and returns it
Graph copyGraph(Graph G);

//printGraph()
//Prints graph to an out file using iteration to print out each adjacency list
void printGraph(FILE* out, Graph G);

#endif
