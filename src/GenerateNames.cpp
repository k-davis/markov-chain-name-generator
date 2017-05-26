
#include <iostream>
#include <fstream>
#include <String>
#include "MarkovModel.h"

using namespace std;

/*
----To-do
Convert arrays to vectors

...the rest of it
*/

int main(){
	int num;
	
	//MarkovModel mm("names/names.csv");
	MarkovModel mm("names/male_first.dat");
	
	num = 10;
	for(int i = 0; i < num; i++){
		cout << mm.makeSecondOrderItem() << endl;
	}
	return 0;
}

