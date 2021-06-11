/* Danny Hong DSA 2 Project 1 */

#include "hash.h"
#include <string>
#include <string.h>
#include <ctime>
#include <fstream>
#include <iostream>

using namespace std;

void throwError(string msg, string file, int type);

int main(){
	char c;
	int i;
	bool ignore;
	unsigned long lineNumber=0;
	string line, word, dictfile, infile, outfile;
	clock_t start;
	clock_t end;
	ifstream input;
	ofstream output;
	
	hashTable *dictHash= new hashTable(50000);
	cout << "Enter name of dictionary: ";
	cin >> dictfile;
	start=clock();
	//Proceeds to open and read the file and then counts the number of bytes contained. The number of bytes determines an approximate word count. Data is then put into the hash table and the file is closed.
	ifstream dict;
	dict.open(dictfile);

	if(dict.fail()){
		throwError("Failed to open the dictionary file", dictfile, 1);
	}

	while(getline(dict, line)){
		for(i=0; i<=line.length(); i++){
			line[i]=tolower(line[i]);
		}
		dictHash->insert(line, NULL);
	}
	dict.close();
	
	end=clock();
	cout << "Total time (in seconds) to load dictionary: " << ((double)(end-start))/(CLOCKS_PER_SEC) << endl;
	cout << "Enter name of input file: ";
    	cin >> infile;
	cout<<"Enter name of output file: ";
	cin >> outfile;
	start=clock();
	input.open(infile);
	if(input.fail()){
		throwError("Failed to open input file.", infile, 1);
	}
	output.open(outfile);
	if(output.fail()){
		throwError("Failed to open output file.", outfile, 1);
	}
	while(getline(input, line)){
		lineNumber=lineNumber+1;
		for(i=0; i<=line.length(); i++){
			c=tolower(line[i]);
			int asciic=c;
			if(isalnum(c)||(asciic==45)||(asciic==39)){
				word=word+c;
				if(isdigit(c)){
					ignore=true;
				}
			}
			else if((word.length()>0) && (ignore==false)){
				if(word.length()>20){
					output << "Long word at line " << lineNumber << ", starts: " << word.substr(0,20) << endl;
 				}
				else if(!dictHash->contains(word)){
					output<<"Unknown word at line " << lineNumber<< ": " << word << endl;
				}
				word="";
			}
			else{
				word="";
				ignore=false;
			}
			
		}
	}

	input.close();
	output.close();
	end=clock();
	cout << "Total time (in seconds) to check document: " << ((double)(end - start))/(CLOCKS_PER_SEC) << endl;
	
	return 0;
}

//Returns an error message if unable to open file.
void throwError(string msg, string file, int type){
        if(type!=1){
		cerr << "ERROR: " << msg << strerror(errno) << endl;
        }
        else{
                cerr << "ERROR: " << msg << ": " << file << ". " << strerror(errno) << endl;
        }
        exit(-1);
}   

