#include <String>
#include <sstream>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <map>

#include "MarkovModel.h"



MarkovModel::MarkovModel(string filePath){
	namesPath = filePath;
	cout << "Constructed" << endl;
	makeModel();
	
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

void MarkovModel::makeModel(){
	openFile();
	readData();
	closeFile();

	normalize();
	printModel();

}

void MarkovModel::readData(){
	

	string line;
	string name;

	getline(namesFile, line);

	while(getline(namesFile, line) && line.find("ALL OTHER NAMES") == string::npos){
		name = line.substr(0, line.find(","));
		
		countChars(name);
	}
	
}

void MarkovModel::countChars(string& name){
	char prevChar = '\n';
	for(char& curChar : name){
		probabilityModel[prevChar][curChar]++;
		prevChar = curChar;
	}
	probabilityModel[prevChar]['\n']++;

}

void MarkovModel::printModel(){
	for(auto &firstMap : probabilityModel){
		cout << adjustKeyToPrint(firstMap.first) << " ";
		for(auto &value : firstMap.second){
			cout << adjustKeyToPrint(value.first) << "|" << value.second << ", ";
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

void MarkovModel::instantiate2DMap(){
	for(char firstKey = 'A'; firstKey < 'Z'; firstKey++){
		for(char secondKey = 'A'; secondKey < 'Z'; secondKey++){
			probabilityModel[firstKey][secondKey] = 0;
		}
		
	}
	for(char letter = 'A'; letter < 'Z'; letter++){
			probabilityModel[letter]['\n'] = 0;
			probabilityModel['\n'][letter] = 0;
	}
	probabilityModel['\n']['\n'] = 0;
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