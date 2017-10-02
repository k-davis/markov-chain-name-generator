
#include <iostream>
#include <fstream>
#include <String>
#include <map>
#include <cstdlib>

#include "MarkovModel.h"

using namespace std;
 
void printMenu();
int getOrderInput();
void createModelOption(map<int, MarkovModel*>& modelList);
void createFromModelOption(map<int, MarkovModel*>& modelList);
void createFromStartingStringOption(map<int, MarkovModel*>& modelList);
string getStartingString();
int getModelOrderToMakeFrom(map<int, MarkovModel*>& modelList);
int getNumNamesToMake();
void outputNames(int numNames, int orderInput, map<int, MarkovModel*>& modelList);


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

void createModelOption(map<int, MarkovModel*>& modelList){
	int orderInput = getOrderInput();

	if(modelList.find(orderInput) == modelList.end()){
		modelList.insert(pair<int, MarkovModel*>(orderInput, new MarkovModel("names/male_first.dat", orderInput)));
		cout << "Model of order " << orderInput << " created." << endl;

	} else {
		cout << "Model of order " << orderInput << " already exists." << endl;
	}
}

void createFromModelOption(map<int, MarkovModel*>& modelList){
	if(modelList.empty()){
		cout << "No models yet exist." << endl;

	} else {
		int input;

		cout << "Enter model order to make names from > ";

		if(cin >> input){
			if(modelList.find(input) == modelList.end()){
				cout << "No model exists with an order of " << input << "." << endl << endl;
				createFromModelOption(modelList);
			} else {
				int numNames = getNumNamesToMake();
				outputNames(numNames, input, modelList);
			}

		} else {
			cout << "Input must be an integer." << endl << endl;
			cin.clear();
			cin.ignore();
			createFromModelOption(modelList);
		}
	}
}

void createFromStartingStringOption(map<int, MarkovModel*>& modelList){
	int order = getModelOrderToMakeFrom(modelList);
	string nameInput = getStartingString();
	string nameOutput;
	bool success = modelList[order]->makeItemFromString(nameOutput, nameInput);
	cout << nameOutput << endl;

}

string getStartingString(){
	string input;
	cout << "Enter the beginning of the name > ";
	getchar();
	getline(cin, input);
	for(char c : input){
		if(!('A' <= c && c <= 'z')){
			cout << "Name beginning must only contain letters." << endl;
			return getStartingString();
		}
	}
	return input;
}

//This sentinel might as well always be true. Fix					!!!!!!!!
int getModelOrderToMakeFrom(map<int, MarkovModel*>& modelList){
	int input;
	bool sentinel = true;

	while(sentinel){
		cout << "Enter model order to make names from > ";

		if(cin >> input){
			//cout << "No model exists with an order of " << input << "." << endl << endl;
			sentinel = false;
			return input;
		} else {
			cout << "Input must be an integer." << endl << endl;
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
			numNames = -1;
		}
	}
}

int getOrderInput(){
	int input;
	
	cout << "Enter model order > ";
	if(cin >> input){
		if(input < 1){
			cout << "Input for model order must be greater than 1." << endl;
		} else if(input >= 6){

			cout << "Model orders greater than 5 may result in unexpected or faulty behavior." << endl;
			cout << "Press enter to continue";
			char enter;
			cin.get(enter);
			cin.get(enter);
			cout << endl;
		}

	} else {
		cout << "Input for model order must be an integer." << endl << endl;
		cin.clear();
		cin.ignore();
		input = getOrderInput();
	}

	return input;	
}