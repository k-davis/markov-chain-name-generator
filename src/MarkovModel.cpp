#include <String>
#include <iostream>
#include <fstream>
#include <cstdlib>

#include "MarkovModel.h"



MarkovModel::MarkovModel(string filePath){
	//namesPath = filePath;
	//openFile();
	cout << convertCharToModelIndex('A') << endl;
	cout << convertCharToModelIndex('C') << endl;
	cout << convertCharToModelIndex('Z') << endl;
	cout << convertCharToModelIndex('\n') << endl;
}

MarkovModel::~MarkovModel(){

}

void MarkovModel::openFile(){
	namesFile.open(namesPath);

	if(namesFile.fail()){
        cout << "Error opening file." << endl;
        exit(1);
    }
}

void MarkovModel::closeFile(){
	namesFile.close();
}

void MarkovModel::makeModel(){
	//For each letter (including an end-of-name character) to store each probability to connect
	// to every other letter, we need a 27 by 27 array
	modelArray = new double*[27];
	for(int i = 0; i < 27; i++){
		modelArray[i] = new double[27];
	}
	
}

int MarkovModel::convertCharToModelIndex(char charToConvert){
	//'\n' signifies the end of a name, and so it is given the last index in the array
	if(charToConvert == '\n'){
		return 26;
	//If the character is between A and Z, then it is a valid character
	} else if('A' <= charToConvert && charToConvert <= 'Z'){
		//We want the returned index to be the number of the letter with A as zero
		return charToConvert - 'A';
	} else {
		cout << "Error: Unexpected character index requested." << endl;
		exit(1);
	}
}