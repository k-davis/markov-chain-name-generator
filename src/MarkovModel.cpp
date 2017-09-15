#include <String>
#include <sstream>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <map>
#include <vector>
#include <time.h>
#include <cassert>
#include <set>
#include <algorithm>

#include "MarkovModel.h"

/*
To Do
change 'auto' data types to what is actually returned
swap out vector for something that doesn't need shift

*/

MarkovModel::MarkovModel(string filePath, int modelOrder){
	namesPath = filePath;
	order = modelOrder;
	makeModel();

	//Comment out for debugging
	srand(time(NULL));
	rand();
}

MarkovModel::~MarkovModel(){

}

void MarkovModel::openFile(){
	namesFile.open(namesPath);

	if(namesFile.fail()){
       cout << "Could not open file." << endl;
        exit(1);
    }
}

void MarkovModel::closeFile(){
	namesFile.close();
	delete namesFile;
}



void MarkovModel::makeModel(){
	openFile();

	string line;
	string name;

	//The order of the model determines how far back the program should look when selecting
	// the next character
	vector <char> prevChars(order);

	while(getline(namesFile, line)){
		//Take the name from each line of the file into variable 'name'
		name = line.substr(0, line.find(" "));
		setOfNames.insert(name);

		//Since the first character in a name is preceded by 'nothing', newline's take their place
		fill(prevChars.begin(), prevChars.end(), '\n');

		for(char& curChar : name){
			//The markov model holds every preceding state and the count of the next possible states
			probabilityModel[makeString(prevChars)][curChar]++;

			//We then change what the preceding state consists of
			shiftVector(prevChars, curChar);
		}

		//A next possible state of a newline indicate the end of a name
		probabilityModel[makeString(prevChars)]['\n']++;
	}

	closeFile();

	//The contents of probabilityModel must be changed from a count of
	//	each possible state to the probability
	normalize();
}

//Turns a vector (list) of characters into a string
string MarkovModel::makeString(vector <char>& myVector){
	string toReturn = "";
	for(int index = 0; index < myVector.size(); index++){
		toReturn += myVector[index];
	}
	return toReturn;
}


void MarkovModel::shiftVector(vector <char>& myVector, char newChar){
	for(int index = myVector.size(); index >= 1; index--){
		myVector[index] = myVector[index - 1];
	}
	myVector[0] = newChar;
}

void MarkovModel::readData(){
	string line;
	string name;

	while(getline(namesFile, line)){
		name = line.substr(0, line.find(" "));
		countChars(name);
	}
}

void MarkovModel::countChars(string& name){
	char prevChar = '\n';
	for(char& curChar : name){
		probabilityModel[string(1, prevChar)][curChar]++;
		prevChar = curChar;
	}
	probabilityModel[string(1, prevChar)]['\n']++;

}



//Takes the model and changes the scale of the numbers to be between 0 and 1
//The model starts having the quantities of character occurences and ends with percentage of the occurence
void MarkovModel::normalize(){
	int sum;
	for(auto &firstMap : probabilityModel){
		sum = 0;
		for(auto &value : firstMap.second){
			sum += value.second;
		}

		for(auto &value : firstMap.second){
			value.second /= sum;
		}
	}
}




string MarkovModel::makeItem(){
	string name;
	vector <char> prevChars(order);
	fill(prevChars.begin(), prevChars.end(), '\n');
	char curChar;
	double letterChance;

	do{
		letterChance = ((double)rand())/RAND_MAX;
		//cout << letterChance;
		curChar = findCorrelatingLetter(letterChance, makeString(prevChars));
		//cout << "\t " << curChar << endl;
		if(curChar != '\n'){
			name += curChar;
		}

		shiftVector(prevChars, curChar);
		
	} while (prevChars[0] != '\n');
	
	if(binary_search(setOfNames.begin(), setOfNames.end(), name)){
		return makeItem();
	} else {
		return name;
	}

}



char MarkovModel::findCorrelatingLetter(double& letterChance, string prevState){
	for(auto &value : probabilityModel[prevState]){
		letterChance -= value.second;
		if(letterChance <= 0){
			return value.first;
		}
	}
	cout << "letterChance: " << letterChance << endl;
	cout << "Oh crap, we have a problem" << endl;
	exit(1);

}