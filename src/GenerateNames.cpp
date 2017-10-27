
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <cstdlib>

#include "MarkovModel.h"

using namespace std;
 
void printMenu();
int getMakeModelOrder();
void createModelOption(map<int, MarkovModel*>& modelList);
void createFromStartingStringOption(map<int, MarkovModel*>& modelList, bool isFromString = false);
string getStartingString();
int getModelOrderToMakeFrom(map<int, MarkovModel*>& modelList);
int getNumNamesToMake();
void outputNames(int numNames, int orderInput, map<int, MarkovModel*>& modelList);
void outputNamesFromString(int numNames, int orderInput, string starting, map<int, MarkovModel*>& modelList);
bool strToInt(string inputStr, int& outputInt);
void pause();


int main(){
	map<int, MarkovModel*> modelList;
	
	
	
	string input = "";

	while(input != "Q"){

		printMenu();
		
		getline(cin, input);
		
		input[0] = toupper(input[0]);

		if(input == "A"){
			createModelOption(modelList);

		} else if(input == "B"){
			createFromStartingStringOption(modelList);

		} else if(input == "C"){
			createFromStartingStringOption(modelList, true);

		} else if(input != "Q"){
			cout << "Please provide a valid input." << endl;
		}


		
	
	}

	cout << "Goodbye" << endl;

	return 0;
}

void printMenu(){
	cout << endl << "Markov Chain Name Generator" << endl;
	cout << "A. Create a model" << endl;
	cout << "B. Create names from existing model" << endl;
	cout << "C. Create names from starting string" << endl;
	cout << "Q. Quit" << endl;
	cout << "> ";
}


void createModelOption(map<int, MarkovModel*>& modelList){
	int orderInput = getMakeModelOrder();

	if(modelList.find(orderInput) == modelList.end()){
		modelList.insert(pair<int, MarkovModel*>(orderInput, new MarkovModel("names.dat", orderInput)));
		cout << "Model of order " << orderInput << " created." << endl;

	} else {
		cout << "Model of order " << orderInput << " already exists." << endl;
	}
	
}



void createFromStartingStringOption(map<int, MarkovModel*>& modelList, bool isFromString){
	if(modelList.empty()){
		cout << "No models exist to make names from." << endl;
	} else {
		int order = getModelOrderToMakeFrom(modelList);
		int numNames = getNumNamesToMake();

		string nameInput;
		if(isFromString){
			nameInput = getStartingString();
		} else {
			nameInput = "";
		}

		outputNamesFromString(numNames, order, nameInput, modelList);
	}
}

string getStartingString(){
	string input;

	while(true){
		

		cout << "Enter the beginning of the name > ";
		getline(cin, input);
		bool goodName = true;

		for(char c : input){
			if(!('A' <= c && c <= 'z')){
				cout << "Name beginning must only contain letters." << endl;
				goodName = false;
			}
		}

		if(goodName){
			return input;
		}
	}
}


int getModelOrderToMakeFrom(map<int, MarkovModel*>& modelList){
	string inputStr;
	int inputInt;
	bool okInput;
	
	while(true){
		
		cout << "Enter model order to make names from > ";
		getline(cin, inputStr);
		okInput = strToInt(inputStr, inputInt);

		if(!okInput){
			cout << "Input must be an integer." << endl;
		} else if(modelList.find(inputInt) == modelList.end()){
			cout << "No model exists with an order of " << inputInt << "." << endl << endl;

		} else {
			return inputInt;
		} 
	}
}

int getNumNamesToMake(){
	string inputStr;
	int inputInt;
	bool okInput;

	cout << "Enter number of names to generate > ";
	getline(cin, inputStr);
	okInput = strToInt(inputStr, inputInt);

	if(okInput){
		if(inputInt < 1){
			cout << "Number must be greater than one." << endl << endl;
			return getNumNamesToMake();
		} else {
			return inputInt;
		}
	} else {
		cout << "Number of names must be an integer." << endl << endl;
		
		return getNumNamesToMake();
	}
}



void outputNamesFromString(int numNames, int orderInput, string starting, map<int, MarkovModel*>& modelList){
	cout << endl;
	while(numNames > 0){
		string newName;
		
		bool retValue = modelList[orderInput]->makeItemFromString(newName, starting);
		if(retValue){
			cout << newName << endl;
			numNames--;
			
		} else {
			cout << "Names can not be generated using a model of this order or with current input." << endl;
			numNames = -1;
		}
	}
}

int getMakeModelOrder(){
	
	while(true){
		string inputStr;
		int inputInt;
		bool okInput;

		

		cout << "Enter model order > ";

		getline(cin, inputStr);
		okInput = strToInt(inputStr, inputInt);

		if(okInput){
			if(inputInt < 1 ){
				cout << "Input for model order must be greater than 1." << endl;
			} else if(inputInt > 20){
				cout << "A model order that high just isn't going to work. It's to have a working order over about 8." << endl;
			
			} else {
				if(inputInt >= 6){

					cout << "Model orders greater than 5 may result in unexpected or faulty behavior." << endl;
					pause();
				}
				
				return inputInt;
			}

			

		} else {
			cout << "gMMO Input for model order must be an integer." << endl << endl;
			
		}
	}
}


bool strToInt(string inputStr, int& outputInt){
	const char* charString = inputStr.c_str();
	outputInt = atoi(charString);
	if(outputInt == 0 && inputStr[0] != '0'){
		return false;
	} else {
		return true;
	}
}


void pause(){
	cout << "Press enter to continue.";
	cin.ignore();
	cout << endl;
}

void deleteMapList(map<int, MarkovModel*>& modelList){
	for(auto const& element: modelList){
		delete element.second;
	}
}