
#include <iostream>
#include <fstream>
#include <String>
#include "MarkovModel.h"

using namespace std;
 


int main(){
	int num;
	int orderInput;
	
	cout << "Markov Chain Name Generator" << endl;
	cout << "A. Create a model" << endl;
	cout << "B. Create names from starting string" << endl;
	cout << "Q. Quit" << endl;
	cout << "Enter order number: ";
	cin >> orderInput;
	MarkovModel mm("names/male_first.dat", orderInput);
	
	num = 10;
	for(int i = 0; i < num; i++){
		cout << mm.makeItem() << endl;
	}
	return 0;
}

