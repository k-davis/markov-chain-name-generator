
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

	modelList.insert(pair<int, MarkovModel*>(orderInput, new MarkovModel("names/male_first.dat", orderInput)));

	cout << "Model of order " << orderInput << " created." << endl;
}

void createFromModelOption(map<int, MarkovModel*>& modelList){
	int input;
	cout << "Enter model order to make names from > ";

	if(cin >> input){
		if(modelList[input] == nullptr){
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
	while(numNames >= 0){
		string newName;
		int retValue = modelList[orderInput]->makeItem(newName);
		if(retValue == 1){
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
		input =  getOrderInput();
	}

	return input;	
}