// What: Graph class
// When: April 2024
// Author: Filippa Getzner
// ID: 21124839


#include <iostream>
#include <unordered_set> //for greedy algorithm, storing the colours
#include "Vector10.h"
#include "Matrix10.h"
#include "Graph.h"

// need to use an initializer list to get this going (johannes)
// the initialiser list directly initialises data members of the class
// these are the members of the class ie here: the private elements
// need to initialise array colours in the constructor!!
Graph::Graph(unsigned int numVertices): num_Vertices(numVertices),AdjacencyMatrix(numVertices)
{
    colours = new int[numVertices];
    // Initialize all colours to -1
    for (unsigned int i = 0; i < numVertices; ++i)
    {
        colours[i] = -1;
    }
    colours_bip = new int[num_Vertices];
    // set all colours to -1
    for (unsigned int i = 0; i< num_Vertices; i++)
        colours_bip[i] = -1;
    // we set all entries of the Adjacency Matrix to 0
    for (unsigned int i = 0; i < numVertices; ++i)
    {
        for (unsigned int j = 0; j < numVertices; ++j)
        {
            AdjacencyMatrix.setij(i, j, 0);
        }
    }
}


Graph::~Graph()
{
    delete[] colours;
    delete[] colours_bip;
}

Matrix Graph::Adj_Matrix_from_edges(double edges[][2], int numEdges)
{
    for (int i = 0; i < numEdges; ++i)
    {
        int vi = edges[i][0];
        int vj = edges[i][1];
        AdjacencyMatrix.setij(vi, vj, 1);
        AdjacencyMatrix.setij(vj, vi, 1); //need this line to make it symmetric
        if (vi == vj)
            AdjacencyMatrix.setij(vi,vj,0);
    }

    return AdjacencyMatrix;
}


void Graph::add_edge(unsigned int vi, unsigned vj)
{
    std::cout << "Adding edge between: " << vi << " and " << vj << std::endl;
    AdjacencyMatrix.setij(vi, vj, 1);
    AdjacencyMatrix.setij(vj, vi, 1);
}

bool Graph::BipartiteTest()
{
    // loop through each vertex of the graph
    for (unsigned int i = 0; i<num_Vertices; i++)
    {
        if (colours_bip[i]==-1) //ie if we haven't assigned a colour to that vertex
        {
            //use dfs to find out if the graph can be coloured in a
            // bipartite way
            if (! dfsBipartite(i,0))
            {
                //ie if the graph cannot be coloured using 2 colours
                // delete memory and return false
                delete[] colours_bip;
                return false;
            }
        }
    }
    //else if (dfsBipartite(i,0)
    //clean up memory and return true
    delete[] colours_bip;
    return true;
}

bool Graph::dfsBipartite(unsigned int vi, int colour)
{
    colours_bip[vi] = colour;
    for (unsigned j = 0; j< num_Vertices; j++)
    {
        // iterate through all adjacent vertices of
        if ( AdjacencyMatrix.getij(vi, j) == 1)
        {
            //if the vertex next to vi hasn't been coloured yet
            if (colours_bip[j] == -1)
            {
                //recursive step: call the dfsBipartite function with the opposite colour of the vertex vi
                if (!dfsBipartite(j, 1-colour))
                {
                    // if we can't colour the vertex j with the colour 1-colour then
                    return false;
                }
            }
            else if (colours_bip[j]== colour) //adjacent vertices have the same colour
            {
                return false;
            }
        }
    }
    //all vertices have been seen and no 2 adjacent vertices have the same colour then
    return true;
}


int Graph::greedyColouring(Matrix AdjacencyMatrix)
{
    int n = AdjacencyMatrix.size();

    //for (unsigned i = 0; i<n; i++)
        //colours[i] = -1;

    for (unsigned int v = 0; v < n; ++v)
    {
        std::unordered_set<int> usedColours;
        // find neighbours and add their colours to the used colour set
        for (int j = 0; j < n; ++j)
        {
            if (AdjacencyMatrix.getij(v, j) == 1 && colours[j] != -1)
            {
                usedColours.insert(colours[j]);
            }
        }

        int colour = 0; //we use count to count the number of times a colour appears in the usedColour set
        while (usedColours.count(colour))
        {
            colour++;
        }

        colours[v] = colour;
    }
    // find the largest number in the array colours
    int maxColour = -1;
    for (unsigned int i = 0; i<n; i++)
    {
        if (colours[i]>maxColour)
            maxColour = colours[i];
    }

    int chromaticNumber = maxColour+1; //+1 to fix indexing
    return chromaticNumber;
}
