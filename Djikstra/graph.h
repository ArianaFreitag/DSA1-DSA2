#ifndef _GRAPH_H
#define _GRAPH_H

#include <fstream>
#include <vector>
#include <list>
#include <string>
#include <climits>
#include "heap.h"

class graph {

  public:
    graph();
    // create a graph with a new hashTable

    bool dijkstra(const std::string &start);
    // apply dijkstra's algorithm on a graph
    // pass in the starting point

    bool nodeExists(const std::string &node);
    // check if node has been found
    // pass in node to find

    void insert(const std::string &line);
    // insert the node into graph
    // pass in line of input file

    void returnGraph(std::ofstream &out);
    // output the graph
    // pass in output file path

  private:
    int capacity; // size of graph
    class edge;
    class node;

    class edge {
      public:
        int cost;  // edge cost
        node *dest;  // destination node
    };

    class node {
      public:
        std::string name;  // name of vertix
        std::list<edge> adj;  // list full of edges from node
        bool known; // if node has been found
        int dist; // distance
        std::list<std::string> path;
    };

    // list of nodes
    std::list<node*> nodeList;
    // hashtable of nodes
    hashTable * graphHashTable;
};

#endif
