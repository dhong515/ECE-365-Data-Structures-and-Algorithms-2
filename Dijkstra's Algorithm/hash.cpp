//Danny Hong DSA 2 Project 2 

#include <iostream> 
#include "hash.h"

using namespace std;

int primeNumbers[] = {11, 100003, 200003, 400009, 800011, 1600033, 3200003, 6400013, 12800009, 25600013, 51200027};

//Makes the hash table vector with null data. 
hashTable::hashTable(int size){ 
	capacity=getPrime(size);
	filled=0;
	data.resize(capacity); 
	for(int i=0; i<data.size(); i++){
		data[i].isOccupied=data[i].isDeleted=false;
	}
}

//Looks for an item that has the specified key and returns its position if it's found or -1 if not found.
int hashTable::findPos(const string &key){
    int pos=hash(key);
    while(data[pos].isOccupied){
        if(data[pos].key==key && data[pos].isDeleted==false){
            return pos;
        }
        else{
            pos=pos+1;
            if(pos==capacity){
                pos=0;
		}
        }
    }
    return -1;
}

//Checks if the specified key is present in the hash table. Returns true if it's present  and false if it's not present. 
bool hashTable::contains(const string &key){
	if(findPos(key)!=-1){
		return true;
	}
	else{
		return false; 
	}
}

//Hash function which uses SDBM for hashing since it has a low rate of collusion.
int hashTable::hash(const string &key){
	unsigned int i=0;
	unsigned int hash=0;
	unsigned int len=key.length();
        for (i=0; i<len; i++){
		hash=(key[i])+(hash<<6)+(hash<<16)-hash;
	}
	return hash%capacity;
}

//Inserts the specified key into hash table. If an optional pointer is included, that pointer is related to a key. Returns 1 if keyis already present in the hash table, 2 if the rehash fails, and 0 if successful. 
int hashTable::insert(const string &key, void *pv){
	int pos=hash(key);
	if (capacity<=(filled*2)){
		if(rehash()==false){
			return 2;
		}
	}
	while(data[pos].isOccupied){
		if(data[pos].key==key){
			if (data[pos].isDeleted){
				data[pos].isDeleted=false;
				data[pos].pv = pv;
				return 0;
				}
			else{
				return 1;
				}
			}
		if(pos!=capacity-1){
                        pos=pos+1;
                }
		else{
			pos=0;
		}		
	}
	filled=filled+1;
	data[pos].key = key;
        data[pos].isOccupied = true;
        data[pos].isDeleted = false;
        data[pos].pv = pv;
        return 0;
}

//Returns a prime number that is greater than or equal to size. Makes use of a precalculated set of prime numbers. 
unsigned int hashTable::getPrime(int size){
	for(int i=0; i<(sizeof(primeNumbers)/sizeof(int)); i++){
		if(size<=primeNumbers[i]){
                        return primeNumbers[i];
		}        
	}
}

//Rehash function makes the hash table larger. Returns true on success and false if memory allocation is unsuccessful.  
bool hashTable::rehash(){
	vector<hashItem> oldData=data;
	int newPrime=getPrime(capacity*2);
	capacity=newPrime;
	filled=0;
	try{
		data.resize(newPrime);
	}
	catch(const bad_alloc){
		return false;
	}
	for(int i=0; i<data.size(); i++)
        	data[i].isOccupied=data[i].isOccupied=false;

	for(int i=0; i<oldData.size();i++)
		if(oldData[i].isOccupied && !oldData[i].isDeleted)
			insert(oldData[i].key, oldData[i].pv);
	return true;
}

//Looks for the position of a hashItem by its key if the position exists. The function returns the item's pv if the position exists, else; it returns NULL. 
void *hashTable::getPointer(const string &key, bool *b){
	int pos=findPos(key);
	if(pos!=1){
		if(b!=nullptr){
			*b=true;
		}
		return data[pos].pv;
	}
	if(b!=nullptr){
		*b=false;
	}
	return nullptr;
}
//Looks for the position of a hashItem by its key if the position exists. The function returns 0 and sets hashItem's pv if it exists; else, it returns 1. 
int hashTable::setPointer(const string &key, void *pv){
	int pos=findPos(key);
	if(pos!=1){
		data[pos].pv=pv;
		return 0;
	}
	return 1;
}
//Sets a hashItem's isDeleted value to be true (lazy deletion).
bool hashTable::remove(const string &key){
	int pos=findPos(key);
	if(pos!=-1){
		data[pos].isDeleted=true;
		return true;
	}
	return false; 
}
