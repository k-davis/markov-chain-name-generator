
#include <iostream>
#include <fstream>
#include <list>

using namespace std;

int main(){
	ofstream ofile;
	ofile.open("all.dat");
	ifstream ffile1;
	ffile1.open("surnames.dat");
	ifstream ffile2;
	ffile2.open("female_first.dat");
	ifstream ffile3;
	ffile3.open("male_first.dat");
	list<string> mylist;

	string line;
	while(!(ffile1.eof())){
		getline(ffile1, line);
		line = line.substr(0, line.find(' '));
		mylist.emplace_back(line);
	}

	while(!(ffile2.eof())){
		getline(ffile2, line);
		line = line.substr(0, line.find(' '));
		mylist.emplace_back(line);
	}

	while(!(ffile3.eof())){
		getline(ffile3, line);
		line = line.substr(0, line.find(' '));
		mylist.emplace_back(line);
	}

	mylist.sort();
	cout << mylist.size() << endl;
	mylist.unique();
	cout << mylist.size() << endl;

	for(list<string>::iterator it = mylist.begin(); it != mylist.end(); it++){
		ofile << *it << endl;
		//cout << *it << endl;
	}
}

