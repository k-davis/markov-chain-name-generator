#include <String>
#include <sstream>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <map>
#include <vector>
#include <time.h>

#include "MarkovModel.h"



MarkovModel::MarkovModel(string filePath, int modelOrder){
	namesPath = filePath;
	order = modelOrder;
	//makeSecondOrderModel();
	makeModel();

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
}

void MarkovModel::makeFirstOrderModel(){
	openFile();
	//readData();
	string line;
	string name;

	while(getline(namesFile, line)){
		name = line.substr(0, line.find(" "));

		char prevChar = '\n';
		for(char& curChar : name){
			probabilityModel[string(1, prevChar)][curChar]++;
			prevChar = curChar;
		}
		probabilityModel[string(1, prevChar)]['\n']++;
	}

	closeFile();

	normalize();
	

}

void MarkovModel::makeSecondOrderModel(){
	openFile();

	string line;
	string name;
	vector <char> prevChars(2);
	while(getline(namesFile, line)){
		name = line.substr(0, line.find(" "));

		//char prev1Char = '\n';
		//char prev2Char = '\n';
		fill(prevChars.begin(), prevChars.end(), '\n');

		for(char& curChar : name){
			probabilityModel[makeString(prevChars)][curChar]++;
			//prev2Char = prev1Char;
			//prev1Char = curChar;
			//prevChars[1] = prevChars[0];
			//prevChars[0] = curChar;
			shiftVector(prevChars, curChar);
		}		
		probabilityModel[makeString(prevChars)]['\n']++;
	}

	closeFile();

	normalize();
}

void MarkovModel::makeModel(){
	openFile();

	string line;
	string name;

	vector <char> prevChars(order);

	while(getline(namesFile, line)){
		name = line.substr(0, line.find(" "));

		fill(prevChars.begin(), prevChars.end(), '\n');

		for(char& curChar : name){
			probabilityModel[makeString(prevChars)][curChar]++;
			shiftVector(prevChars, curChar);
		}
		probabilityModel[makeString(prevChars)]['\n']++;
	}

	closeFile();
	normalize();
}

string MarkovModel::makeString(vector <char>& myVector){
	string toReturn = "";
	for(int index = myVector.size() - 1; index >= 0; index--){
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