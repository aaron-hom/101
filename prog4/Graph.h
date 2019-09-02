//Graph.h
//Aaron Hom
//pa4
//Header file for Graph ADT

#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <stdio.h>
#include "List.h"

#define NIL -1
#define INF -2

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

//getSource()
//Returns most recent source from using BFS(G, s)
int getSource(Graph G);

//getParent()
//Returns parent of given vertex (u) from graph G
//Pre: 1 <= u <= getOrder(G)
int getParent(Graph G, int u);

//getDistance()
//Returns distance from the source of a graph to a given vertex
//Pre: 1 <= u <= getOrder(G)
int getDist(Graph G, int u);

//getPath()
//Returns the path from source to vertex
//Pre: 1 <= u <= getOrder(G)
void getPath(List L, Graph G, int u);

//Manipulation Procedures---------------------------------
//makeNull()
//Clears all adjacency lists for graph
void makeNull(Graph G);

//addEdge()
//Adds an undirected edge to graph from vertex u to vertex g
//Pre: 1 <= u & v <= getOrder(G) 
void addEdge(Graph G, int u, int v);

//addArc()
//Adds a directed edge to graph from vertex u to vertex g
//Pre: 1 <= u & v <= getOrder(G)
void addArc(Graph G, int u, int v);

//BFS()
//Performs Breadth First Search on graph using s as the source 
void BFS(Graph G, int s);

//Other operations ---------------------------------------
//printGraph()
//Prints graph to an out file using iteration to print out each adjacency list 
void printGraph(FILE* out, Graph G);

#endif
