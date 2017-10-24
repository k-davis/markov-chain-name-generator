#include <String>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <map>
#include <vector>
#include <set>
#include <algorithm>
#include <ctime>


#include "MarkovModel.h"



MarkovModel::MarkovModel(string filePath, int modelOrder){
	namesPath = filePath;
	order = modelOrder;
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



void MarkovModel::makeModel(){
	openFile();

	string line;
	string name;

	//The order of the model determines how far back the program should look when selecting the next character
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

	//The contents of probabilityModel must be changed from a count of each possible state to the probability
	normalize();
}

//Turns a vector (list) of characters into a string
string MarkovModel::makeString(vector <char>& myVector){
	string toReturn = "";
	for(unsigned int index = 0; index < myVector.size(); index++){
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


bool MarkovModel::makeItem(string& nameOutput){
	string name = "";
	vector<char> prevChars(order);
	fill(prevChars.begin(), prevChars.end(), '\n');

	return makeItemTimer(nameOutput, name, prevChars);
}

bool MarkovModel::makeItemFromString(string& nameOutput, string nameInput){
	string name = nameInput;
	vector<char> prevChars(order);

	transform(name.begin(), name.end(), name.begin(), ::toupper);
	fill(prevChars.begin(), prevChars.end(), '\n');

	if(name.size() > order){
		for(int i = 0; i <= order; i++){
			prevChars[i] = name[name.size()-1 - i];
		}
	} else {
		for(int i = 0; i < name.size(); i++){
			prevChars[i] = name[name.size() - 1 - i];
		}
	}

	if(probabilityModel.find(makeString(prevChars)) == probabilityModel.end()) {
		return false;
	}

	return makeItemTimer(nameOutput, name, prevChars);
}



bool MarkovModel::makeItemTimer(string& nameOutput, string nameInput, vector<char> prevChars){

	nameOutput = makeItemHelper(nameInput, prevChars);
	clock_t startTime;
	
	startTime = clock();
	while(binary_search(setOfNames.begin(), setOfNames.end(), nameOutput)){
		
		nameOutput = makeItemHelper(nameInput, prevChars);

		// If a name cannot be generated
		if( ((clock() - startTime) / (double)CLOCKS_PER_SEC) > 5.0){
			return false;
		}

	} 

	setOfNames.insert(nameOutput);
	//The capitalization is made propper
	transform(nameOutput.begin(), nameOutput.end(), nameOutput.begin(), ::tolower);
	nameOutput[0] = toupper(nameOutput[0]);

	return true;
}



string MarkovModel::makeItemHelper(string name, vector<char> prevChars){
	char curChar;
	double letterChance;
	
	
	do{

		letterChance = ((double)rand())/RAND_MAX;
		while(letterChance == 1){
			letterChance = ((double)rand())/RAND_MAX;
		}

		curChar = findCorrelatingLetter(letterChance, makeString(prevChars));
		
		//A name simply shouldn't include a newline character. Newlines characters aren't letters
		if(curChar != '\n'){
			name += curChar;
		}

		// The new character is added to the *beginning* (index 0) of the vector
		shiftVector(prevChars, curChar);
	
	//So, when the most recent character selected is '\n', the name is done being made
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
	
	cout << "Fatal Error: new character could not be calculated." << endl;
	exit(1);

}