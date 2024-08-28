// What: Header file for Graph class
// When: April 2024
// Author: Filippa Getzner
// ID: 21124839

#ifndef GRAPH_H
#define GRAPH_H

#include "Matrix10.h"
#include "Vector10.h"

class Graph{
private:
    unsigned int num_Vertices;
    Matrix AdjacencyMatrix;
    int *colours; //for greedy colouring
    int *colours_bip; //for bipartite testing
public:
    Graph (unsigned int num_Vertices);
    ~Graph (void);
    void add_edge(unsigned int vi, unsigned int vj);
    Matrix Adj_Matrix_from_edges(double edges[][2], int NumEdges);
    bool dfsBipartite(unsigned int vi, int colour);
    bool BipartiteTest();
    int greedyColouring(Matrix AdjacencyMatrix);
    int getcolour(unsigned int v){return colours[v];};
    int size(void) {return num_Vertices;};
};

#endif


