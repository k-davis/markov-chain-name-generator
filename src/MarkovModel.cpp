#include <String>
#include <sstream>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <map>
#include <time.h>

#include "MarkovModel.h"



MarkovModel::MarkovModel(string filePath){
	namesPath = filePath;
	cout << "Constructed" << endl;

	makeSecondOrderModel();

	srand(time(NULL));
}

MarkovModel::~MarkovModel(){

}

void MarkovModel::openFile(){
	namesFile.open(namesPath);

	if(namesFile.fail()){
       
        exit(1);
    }
}

void MarkovModel::closeFile(){
	namesFile.close();
}

void MarkovModel::makeFirstOrderModel(){
	openFile();
	readData();
	closeFile();

	normalize();
	

}

void MarkovModel::makeSecondOrderModel(){
	openFile();

	string line;
	string name;
	int cycleNum = 0;
	while(getline(namesFile, line)){
		name = line.substr(0, line.find(" "));

		char prev1Char = '\n';
		char prev2Char = '\n';
		for(char& curChar : name){
			probabilityModel[string(1, prev2Char).append(string(1, prev1Char))][curChar]++;
			prev2Char = prev1Char;
			prev1Char = curChar;
		}		
		probabilityModel[string(1, prev2Char).append(string(1, prev1Char))]['\n']++;
	}

	closeFile();

	normalize();
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

void MarkovModel::printModel(){
	for(auto &firstMap : probabilityModel){
		//cout << adjustKeyToPrint(firstMap.first) << " ";
		for(auto &value : firstMap.second){
			//cout << adjustKeyToPrint(value.first) << "|" << value.second << ", ";
		}
		cout << endl;
	}
}

string MarkovModel::adjustKeyToPrint(char key){
	stringstream ss;
	string toReturn;
	if(key == '\n'){
		return "\\n";
	} else {
		ss << key;
		ss >> toReturn;
		return toReturn;
	}
}



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

string MarkovModel::makeFirstOrderItem(){
	string name;
	char prevChar = '\n';
	char curChar;
	double letterChance;

	do {
		letterChance = ((double)rand())/RAND_MAX;
		curChar = findCorrelatingLetter(letterChance, string(1, prevChar));
		if(curChar != '\n'){
			name += curChar;
		}

		prevChar = curChar;
	} while (prevChar != '\n');
	return name;
}

string MarkovModel::makeSecondOrderItem(){
	string name;
	char prev2Char = '\n';
	char prev1Char = '\n';
	char curChar;
	double letterChance;

	do{
		letterChance = ((double)rand())/RAND_MAX;
		curChar = findCorrelatingLetter(letterChance, string(1, prev2Char).append(string(1, prev1Char)));
		if(curChar != '\n'){
			name += curChar;
		}

		prev2Char = prev1Char;
		prev1Char = curChar;
	} while (prev1Char != '\n');
	return name;
}

char MarkovModel::findCorrelatingLetter(double& letterChance, string prevState){
	for(auto &value : probabilityModel[prevState]){
		letterChance -= value.second;
		if(letterChance <= 0){
			return value.first;
		}
	}
}