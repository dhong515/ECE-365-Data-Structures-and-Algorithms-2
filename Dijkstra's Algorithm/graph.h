#ifndef _GRAPH_H
#define _GRAPH_H

#include "heap.h"
#include <iterator>
#include <string>
#include <list>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <istream>

using namespace std;

class graph
{
public:
	//initializes the graph.
	graph();

	//implementing Dijkstra's algorithm to track shortest path lengths.
	int dijkstra(string &begin);

	//Checks the node(vertex) hash table to see if a specific node exists. Returns true if it does, false if it doensn't.
	bool containsNode(string &node);

	//Inserts nodes(vertices) to the hash table and graph
	void insert(string &vertex1, string &vertex2, int length);

	//Imports the nodes that are connected by a positive path cost from an ifstream. Returns true if all the nodes are imported.
	bool importGraph(ifstream &in);

	void printPaths(ofstream &out);

private:
	int size; //size of graph
	class node;
	class edge;
	hashTable *graph_nodes; //hashtable of nodes
        list<node*> node_list; //list of nodes
	
	class node 
	{
	public:
		bool known;
		int length;
		string id; //id of node
		list<string> path;
		list<edge> adj; //adjacency list	
	};
	
	class edge
	{
	public:
		node *dest; //destination node
		int cost; //edge cost
	};
};

#endif


