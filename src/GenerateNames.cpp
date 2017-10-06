
#include <iostream>
#include <fstream>
#include <String>
#include <map>
#include <cstdlib>

#include "MarkovModel.h"

using namespace std;
 
void printMenu();
int getMakeModelOrder();
void createModelOption(map<int, MarkovModel*>& modelList);
void createFromModelOption(map<int, MarkovModel*>& modelList);
void createFromStartingStringOption(map<int, MarkovModel*>& modelList);
string getStartingString();
int getModelOrderToMakeFrom(map<int, MarkovModel*>& modelList);
int getNumNamesToMake();
void outputNames(int numNames, int orderInput, map<int, MarkovModel*>& modelList);
void outputNamesFromString(int numNames, int orderInput, string starting, map<int, MarkovModel*>& modelList);
void clearBuffer();
void pause();


int main(){
	map<int, MarkovModel*> modelList;
	

	
	string input = "";
	while(input != "Q"){

		printMenu();
		
		cin >> input;
		input[0] = toupper(input[0]);

		if(input == "A"){
			createModelOption(modelList);

		} else if(input == "B"){
			createFromModelOption(modelList);

		} else if(input == "C"){
			createFromStartingStringOption(modelList);

		} else if(input != "Q"){
			cout << "Please provide a valid input." << endl;
		}
	}

	
	
	
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

// orderInput must NOT correspond with an existing model
void createModelOption(map<int, MarkovModel*>& modelList){
	int orderInput = getMakeModelOrder();

	if(modelList.find(orderInput) == modelList.end()){
		modelList.insert(pair<int, MarkovModel*>(orderInput, new MarkovModel("names/male_first.dat", orderInput)));
		cout << "Model of order " << orderInput << " created." << endl;

	} else {
		cout << "Model of order " << orderInput << " already exists." << endl;
	}
}


void createFromModelOption(map<int, MarkovModel*>& modelList){
	if(modelList.empty()){
		cout << "No models exist to make names from." << endl;
	} else {
		int order = getModelOrderToMakeFrom(modelList);
		int numNames = getNumNamesToMake();

		outputNames(numNames, order, modelList);
	}
}

void createFromStartingStringOption(map<int, MarkovModel*>& modelList){
	if(modelList.empty()){
		cout << "No models exist to make names from." << endl;
	} else {
		int order = getModelOrderToMakeFrom(modelList);
		string nameInput = getStartingString();
		int numNames = getNumNamesToMake();

		outputNamesFromString(numNames, order, nameInput, modelList);
	}
}

string getStartingString(){
	string input;

	while(true){
		clearBuffer();

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
	int input;
	
	while(true){
		clearBuffer();
		cout << "Enter model order to make names from > ";

		if(!(cin >> input)){
			cout << "Input must be an integer." << endl;
		} else if(modelList.find(input) == modelList.end()){
			cout << "No model exists with an order of " << input << "." << endl << endl;

		} else {
			return input;
		} 
	}
}

int getNumNamesToMake(){
	int input;
	cout << "Enter number of names to generate > ";
	if(cin >> input){
		if(input < 1){
			cout << "Number must be greater than one." << endl << endl;
			return getNumNamesToMake();
		} else {
			return input;
		}
	} else {
		cout << "Number of names must be an integer." << endl << endl;
		cin.clear();
		cin.ignore();
		return getNumNamesToMake();
	}
}

void outputNames(int numNames, int orderInput, map<int, MarkovModel*>& modelList){
	cout << endl;
	while(numNames > 0){
		string newName;
		
		bool retValue = modelList[orderInput]->makeItem(newName);
		if(retValue){
			cout << newName << endl;
			numNames--;
			
		} else {
			cout << "Names can not be generated using a model of this order." << endl;
		}
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
			cout << "Names can not be generated using a model of this order." << endl;
		}
	}
}

int getMakeModelOrder(){
	
	while(true){
		int input;
		clearBuffer();
		cout << "Enter model order > ";
		cin >> input;
		if(!cin.fail()){
			if(input < 1){
				cout << "Input for model order must be greater than 1." << endl;

			} else if(input >= 6){

				cout << "Model orders greater than 5 may result in unexpected or faulty behavior." << endl;
				pause();
			}

			return input;

		} else {
			cout << "gMMO Input for model order must be an integer." << endl << endl;
	
		}
	}

	
}


void clearBuffer(){
	cin.clear();
	cin.ignore(1000, '\n');
}

void pause(){
	cout << "Press enter to continue.";
	string junk;
	cin >> junk;
	cout << endl;
}