//Danny Hong DSA 2 Project 3

#include <chrono>
#include <algorithm>
#include <string>
#include <iostream>
#include <fstream>
#include "graph.h"

using namespace std::chrono;
using namespace std;

int main(int argc, char **argv){
	string infile, outfile, startingNode;
	ifstream inFile;
	ofstream outFile;
	graph g;
	while (!inFile.is_open()){
        	cout<<"Enter a valid graph input file: ";
        	cin >> infile;
        	inFile.open(infile, ifstream::in);
	}

	g.importGraph(inFile);
	inFile.close();

	while(!g.containsNode(startingNode)){
        	cout<<"Enter a valid starting vertex: ";
        	cin>>startingNode;
	}

	clock_t begin=clock();
	g.dijkstra(startingNode);
	clock_t end=clock();
	double runtime=((double)(end - begin))/(CLOCKS_PER_SEC);
    	cout<<"Total time (in seconds) to apply Dijkstra's algorithm: "<<runtime<<endl;

	while (!outFile.is_open()){
        	cout<<"Enter an output file: ";
        	cin>>outfile;
        	outFile.open(outfile, ofstream::out | ofstream::trunc);
	}
	g.printPaths(outFile);
	outFile.close();
	return 0;
}
