#include <String>
#include <map>
#include <vector>
#include <set>

#ifndef MARKOVMODEL_H
#define MARKOVMODEL_H

using namespace std;

class MarkovModel{
public:
	//Constructor for a Markov Model
	//namesPath - the location of the file from which the model will be made
	MarkovModel(string filePath, int modelOrder);

	
	~MarkovModel();

	bool makeItem(string& nameOutput);
	bool makeItemFromString(string& nameOutput, string nameInput);



private:

	string namesPath;
	int order;
	ifstream namesFile;
	map <string, map <char, double>> probabilityModel;
	set<string> setOfNames;

	
	void openFile();
	void closeFile();

	void makeModel();
	string makeString(vector <char>& myVector);
	void shiftVector(vector <char>& myVector, char newChar);	
	void readData();
	void countChars(string& name);
	void normalize();
	char findCorrelatingLetter(double& letterChance, string prevState);
	string makeItemHelper(string name, vector<char> prevChars);
	bool makeItemTimer(string& nameOutput, string nameInput, vector<char> prevChars);


};

#endif