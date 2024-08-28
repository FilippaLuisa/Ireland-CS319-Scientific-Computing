// What: main file to test the Graph class
// When: April 2024
// Author: Filippa Getzner
// ID: 21124839

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <time.h>
#include "Vector10.h"
#include "Matrix10.h"
#include "Graph.h"

void WriteVertexColouringCSV(Graph graph, std::string FileName);

int main()
{
    // -----------READ IN CSV FILE -----------
    std::string InFileName =  "graph_data.csv";

    std::ifstream InFile(InFileName.c_str());
    std::string line;
    unsigned int numVertices = 0;
    int edgeCount=0;

    if (InFile.fail())
    {
        std::cerr << "Error - can't open " << InFileName << std::endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        if (std::getline(InFile,line))
        {
            std::istringstream iss(line);
            iss >> numVertices;
        }
        while(std::getline(InFile,line))
        {
            ++edgeCount;
        }
        double (*edges)[2]= new double[edgeCount][2];

        InFile.clear();
        InFile.seekg(0, std::ios::beg);

        std::getline(InFile, line);

        int i = 0;
        while (std::getline(InFile, line))
        {
            std::istringstream iss(line);
            double vi, vj;
            if(iss >> vi >> vj)
            {
                edges[i][0] = vi;
                edges[i][1] = vj;
                i++;
            }
        }

        // ---------CREATE GRAPH AND PRINT ADJACENCY MATRIX -----------------

        Graph graph(numVertices);
        Matrix adjacencyMatrix = graph.Adj_Matrix_from_edges(edges, edgeCount);
        adjacencyMatrix.print();

        // ----------- TEST THE ADD EDGE FUNCTION----------------------

        unsigned int vk, vl;
        bool valid_input = false;

        while (!valid_input)
        {
            std::cout << "Enter two vertices (between 0 and " << numVertices-1 << "): "<<std::endl;
            std::cout << "\nVertex vi: ";
            std::cin >> vk;
            std::cout <<"\nVertex vj: ";
            std::cin >> vl;
            if ((vk<0) || (vl<0) || (vl > numVertices-1) || (vl > numVertices-1) || (vk==vl))
            {
                valid_input = false;
                std::cout << "Invalid input!" ;
            }
            else
                valid_input = true;
        }
        Graph graph1(numVertices);
        graph1.add_edge(vk,vl);
        Matrix adjacencyMatrix1 = graph1.Adj_Matrix_from_edges(edges, edgeCount+1);
        adjacencyMatrix1.print();

        // ---------------BIPARTITE TESTING --------------------------

        bool isBipartite = graph.BipartiteTest();
        if (isBipartite)
        {
            std::cout<< "\nThe graph is bipartite.";
        }
        else
            std::cout<< "\nThe graph isn't bipartite.";

        // ---------------CALCULATING THE CHROMATIC NUMBER -------------
        //clock_t start;
        //start=clock();
        int chromatic_number = graph.greedyColouring(adjacencyMatrix);
        //double diff = (float)(clock()-start);
        //double Time = diff/CLOCKS_PER_SEC;
        //std::cout << "\nTime: " << Time << "\n" << std::endl;
        std::cout << "\nThe upper bound for the chromatic number of the graph is: " << chromatic_number;

        //----------------GETTING THE COLOURING--------------------------

        std::string outFileName = "colouring.csv";
        WriteVertexColouringCSV(graph, outFileName);
        delete[] edges;
    }
    return (0);
}

void WriteVertexColouringCSV(Graph graph, std::string FileName)
{
    std::ofstream OutputFile;

    OutputFile.open(FileName.c_str());
    if (OutputFile.fail())
    {
        std::cerr<< "Error - can't open " << FileName << std::endl;
        exit(1);
    }

    unsigned int numVertices = graph.size();
    for (unsigned v = 0; v < numVertices; ++v) {
        OutputFile << v << "," << graph.getcolour(v) << "\n";
    }
    OutputFile.close();
}
