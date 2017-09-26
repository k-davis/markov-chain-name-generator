
#include <iostream>
#include <fstream>
#include <String>
#include <map>
#include <cstdlib>

#include "MarkovModel.h"

using namespace std;
 
void printMenu();
int getOrderInput();

int main(){
	map<int, MarkovModel*> modelList;
	int num;
	int orderInput;
	
	string input = "";
	while(input != "Q"){

		printMenu();
		
		cin >> input;
		input[0] = toupper(input[0]);

		if(input == "A"){
			string newName;
			orderInput = getOrderInput();

			modelList.insert(pair<int, MarkovModel*>(orderInput, new MarkovModel("names/male_first.dat", orderInput)));

			num = 10;
			
			cout << endl;
			while(num >= 0){
				
				int retValue = modelList[orderInput]->makeItem(newName);
				if(retValue == 1){
					cout << newName << endl;
					num--;
					
				} else {
					cout << "Names can not be generated using a model of this order." << endl;
					num = -1;
				}
			}


		} else if(input == "B"){


		} else if(input != "Q"){
			cout << "Please provide a valid input." << endl;
		}
	}

	
	
	
	return 0;
}

void printMenu(){
	cout << endl << "Markov Chain Name Generator" << endl;
	cout << "A. Create a model" << endl;
	cout << "B. Create names from starting string" << endl;
	cout << "Q. Quit" << endl;
	cout << "> ";
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
			getchar();
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