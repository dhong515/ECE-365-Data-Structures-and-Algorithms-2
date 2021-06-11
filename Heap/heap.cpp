//Danny Hong DSA 2 Project 2 

#include "heap.h"
#include <iostream>

using namespace std;

// heap-The constructor allocates space for the nodes of the heap and mapping (hash table) based on specified capacity.
heap::heap(int capacity){
	data.resize(capacity+1);
	mapping=new hashTable(2*capacity);
	this->capacity=capacity;
	filled=0;
}

//insert-Inserts a new node into a binary heap.
//
//Inserts a node with the specified id string, key,
// and optionally a pointer. They key is used to
// determine the final position of the new node.
//
// Returns:
//   0 on success
//   1 if the heap is already filled to capacity
//   2 if a node with the given id already exists (but the heap
//     is not filled to capacity) 
int heap::insert(const string &id, int key, void *pv){
	if(filled<capacity){
		if(mapping->contains(id)==false){
			filled=filled+1;
			data[filled].id=id;
			data[filled].key=key;
			data[filled].pData=pv;
			mapping->insert(id, &data[filled]);
                        percolateUp(filled);
			}
		else{
			return 2;
			}
		}
	else{
		return 1;
		}
	return 0;
}

// setKey - set a new key for a node specified by ID. 
int heap::setKey(const string &id, int key){
	if(!(mapping->contains(id))){
		return 1;
	}
	int loc=0;
	int old=0;
	node *pn=static_cast<node*>(mapping->getPointer(id));
	loc=getPos(pn);
	old=pn->key;
	pn->key=key; 
	
	if(old>key){
		percolateUp(loc);
	}
	else if(old<key){
		percolateDown(loc);
	}
	return 0;
}

// deleteMin - return the data associated with the smallest key
//             and delete that node from the binary heap
//
// If pId is supplied (i.e., it is not NULL), write to that address
// the id of the node being deleted. If pKey is supplied, write to
// that address the key of the node being deleted. If ppData is
// supplied, write to that address the associated void pointer.
//
// Returns:
//   0 on success
//   1 if the heap is empty
int heap::deleteMin(string *pId, int *pKey, void *ppData){
	if(filled>0){
		if(pId!=nullptr){
			*pId=data[1].id;
		}
		if(pKey!=nullptr){
			*pKey=data[1].key;
		}
		if(ppData!=nullptr){
			*(static_cast<void **> (ppData)) = data[1].pData;	
		}
		remove(data[1].id);
		return 0;
	}
	else{
		return 1;
	}
}

// remove - delete the node with the specified id from the binary heap
//
// If pKey is supplied, write to that address the key of the node
// being deleted. If ppData is supplied, write to that address the
// associated void pointer.
//
// Returns:
//   0 on success
//   1 if a node with the given id does not exist
int heap::remove(const string &id, int *pKey, void *ppData){
	int original=0;
        int pos=0; 
        if(mapping->contains(id)==true){
                node *pn=static_cast<node *>(mapping->getPointer(id));
                if (pKey!=nullptr){
                        *pKey=pn->key;
			}
                if (ppData!=nullptr){
                        *(static_cast<void **> (ppData)) = pn->pData;
			}
                pos = getPos(pn);
                mapping->remove(id);
                original=data[pos].key;
                swap(data[pos], data[filled]); // Swaps node with last node
                mapping->setPointer(data[pos].id, &data[pos]); // Sets pointer to the new node in that position
                filled=filled-1;
                if (original>data[pos].key){ // Percolates up or down
                        percolateUp(pos);
                } 
		else if (original<data[pos].key) {
                        percolateDown(pos);
                }
                return 0;
        } 
	else{
		return 1;
	}
}

// percolateUp-moves a node up a binary heap
void heap::percolateUp(int posCur){
        while(posCur>1 && data[posCur/2].key > data[posCur].key) {
                swap(data[posCur/2], data[posCur]);
                mapping->setPointer(data[posCur].id, &data[posCur]);
                mapping->setPointer(data[posCur/2].id, &data[posCur/2]);
                posCur=0.5*posCur;
        }
}

// percolateDown - move a node down a binary heap
void heap::percolateDown(int posCur){
	int child1=0;
	int child2=0;
	int smallerChild=0;
	
	while(2*posCur<=filled){
		child1=2*posCur;
		child2=child1+1;
		smallerChild=child1;
		
		if(filled>child1 && data[smallerChild].key>data[child2].key){
                        smallerChild=child2;
                }
		if(data[posCur].key>data[smallerChild].key){
			swap(data[posCur], data[smallerChild]);
                        mapping->setPointer(data[posCur].id, &data[posCur]);
                        mapping->setPointer(data[smallerChild].id, &data[smallerChild]);
                        posCur = smallerChild;
		}
		else{
			break;
		}
	}
}

// Returns the position of a node in a data vector
int heap::getPos(node *pn){
    return (pn-&data[0]);
}
