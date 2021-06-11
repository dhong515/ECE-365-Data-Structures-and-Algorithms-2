//Danny Hong DSA 2 Project 4

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <string.h>
#include <ctime>
#include <fstream>

using namespace std;

int matrix[1001][1001];

int checkMerge(string wordA, string wordB, string &wordMerged){
	int indexMerged=(wordMerged.length()-1);
	int indexA=wordA.length();
	int indexB=wordB.length();
	//Assigns values based on the first letter of each word 
	if(wordA[0]==wordMerged[0]){
		matrix[1][0]++;
	}
	if(wordB[0]==wordMerged[0]){
		matrix[0][1]++;
	}
	//Fills up the matrix
	for(int i=0; i<(indexA+1); i++){
		for(int j=0; j<(indexB+1); j++){
			if(wordMerged[matrix[i][j]+1]==wordA[i] && matrix[i][j]!=-1){
				matrix[i+1][j]=matrix[i][j]+1;
			}
			if(wordMerged[matrix[i][j]+1]==wordB[j] && matrix[i][j]!=-1){
				matrix[i][j+1]=matrix[i][j]+1;
			}
		}
	}
	// Begins at the last valid matrix value and backtracks
	if(matrix[indexA][indexB]!=-1){
		while(indexMerged>=0){
			indexMerged=indexMerged-1;
			if(matrix[indexA][indexB-1]==indexMerged && indexB>0){
				indexB=indexB-1;
			}
			else{
				wordMerged[indexMerged+1]= toupper(wordMerged[indexMerged+1]);
				indexA=indexA-1;
			}
		}
		return 0;
	}
	return -1;
}

int main(){
	ifstream inFile;
	ofstream outFile;
	string wordMerged, wordA, wordB;
	string line, input, output;
	
	cout<<"Enter name of input file: ";
	cin>>input;
	inFile.open(input);
	if(!inFile){
		cout<<"Error: could not open "<<input<<endl;
		return -1;
	}
	cout<<"Enter name of output file: ";
	cin>>output;
	outFile.open(output);
	if(!outFile){
                cout<<"Error: could not open "<<output<<endl;
                return -1;
        }
	while(getline(inFile, wordA) && getline(inFile, wordB) && getline(inFile, wordMerged)){
                //Resets matrix
                for(int i=0; i<1001; i++){
                        for(int j=0; j<1001; j++){
                                matrix[i][j]=-1;
			}
		}	
                if((wordA.length()+wordB.length())!=wordMerged.length() || checkMerge(wordA, wordB, wordMerged)<0){
                        outFile<<"*** NOT A MERGE ***"<<endl;
		}
                else{
                        outFile<<wordMerged<<endl;
        	}
	}
}

