
#include <iostream>
#include <fstream>
#include <String>
#include "MarkovModel.h"

using namespace std;


int main(){
	int num;
	int orderInput;
	

	cout << "Enter order number: ";
	cin >> orderInput;
	MarkovModel mm("names/male_first.dat", orderInput);
	
	num = 10;
	for(int i = 0; i < num; i++){
		//cout << mm.makeSecondOrderItem() << endl;
		cout << mm.makeItem() << endl;
	}
	return 0;
}

