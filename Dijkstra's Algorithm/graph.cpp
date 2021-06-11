//Danny Hong DSA 2 Project 3

#include "graph.h"

graph::graph(){
	size=0;
	graph_nodes=new hashTable(100000);
}
//Applies Dijkstra's algorithm on a graph given root node.
int graph::dijkstra(string &root){
	node *cur;
	int newCost;
	list<node*>::const_iterator it=node_list.begin(), end=node_list.end();
	for(;it!=end; ++it){
		(*it)->length=INT_MAX;
                (*it)->known=false;
	}
	heap queue(size);
	node *begin=(node*)graph_nodes->getPointer(root);
	begin->length=0;
	begin->path.push_back(root);
	for(it=node_list.begin();it!=end;++it) {
                queue.insert((*it)->id,(*it)->length,*it);
        }
	for(int i=0;i<size;i++){
		queue.deleteMin(nullptr, nullptr, &cur);
		for(list<edge>::const_iterator it=cur->adj.begin(),end=cur->adj.end();it!=end;++it){
			newCost=it->cost+cur->length;
			auto next=it->dest;
			if(next->length>newCost && !next->known){
				queue.setKey(next->id, newCost);
				next->length=(it->cost+cur->length);
                                next->path.clear();
                                next->path.insert(next->path.begin(), cur->path.begin(), cur->path.end());
                                next->path.push_back(next->id);
			}
		}
		cur->known=true;
	}
	return 0; 
}
//Checks if a specific node exists in the hash table.
bool graph::containsNode(string &node){
	return(graph_nodes->contains(node));
}
//Ignores the node if it exists, otherwise, the node is inserted to the back of the list of nodes and added tp the node hash table. The length parameter of the node is set to INT_MAX as a result of implementing Dijkstra's algorithm. The edge is set so that it points to the second node and is inserted to the adjacency list of the first node. 	
void graph::insert(string &node1, string &node2, int length){
	node *temp1, *temp2;
	edge newEdge;
	if(!graph_nodes->contains(node1)){
        	temp1 = new node;
        	temp1->id = node1;
        	temp1->known = false;
        	temp1->length = INT_MAX;
        	node_list.push_back(temp1);
        	graph_nodes->insert(node1, temp1);
        	size=size+1;
	}
	else{
        	temp1=(node*)graph_nodes->getPointer(node1);
	}
	if(!graph_nodes->contains(node2)){
        	temp2=new node;
        	temp2->id=node2;
        	temp2->known=false;
        	temp2->length=INT_MAX;
        	node_list.push_back(temp2);
        	graph_nodes->insert(node2, temp2);
        	size=size+1;
	}
	else{
        	temp2=(node *)graph_nodes->getPointer(node2);
	}
	newEdge.dest=temp2;
	newEdge.cost=length;
	temp1->adj.push_back(newEdge);
}
//Reads the graph in line by line.
bool graph::importGraph(ifstream &in){
	string node1, node2;
	int length=0;
	while(in>>node1>>node2>>length){
        	insert(node1, node2, length);
	}
	return true;
}
//Goes through the list of nodes and prints the minimum paths in order of node entry. 
void graph::printPaths(ofstream &out){
	for(list<node *>::const_iterator it=node_list.begin(), end=node_list.end(); it!=end; ++it){
		out<<(*it)->id<<": ";
        	if ((*it)->length==INT_MAX || (*it)->length<0){
            		out<<"NO PATH"<<endl;
        	}
        	else{
            		out<<(*it)->length<<" [";
            		for(list<string>::const_iterator it2=(*it)->path.begin(), end2=(*it)->path.end(); it2!=end2; ++it2){
                		out<<*it2;
                		if(next(it2, 1)!=end2){
                    			out<<", ";
				}
            		}
            		out<<"]"<<endl;
        	}
    	}
}
