#include <String>
#include <map>
#include <vector>

#ifndef MARKOVMODEL_H
#define MARKOVMODEL_H

using namespace std;

class MarkovModel{
public:
	//Constructor for a Markov Model
	//namesPath - the location of the file from which the model will be made
	MarkovModel(string filePath, int modelOrder);

	//Deconstructor
	~MarkovModel();

	string makeFirstOrderItem();
	string makeSecondOrderItem();
	string makeItem();
private:

	string namesPath;
	int order;
	ifstream namesFile;
	map <string, map <char, double>> probabilityModel;

	//Opens the file
	void openFile();
	//Closes the file
	void closeFile();
	//Makes the whole Markov Chain model, the 2D array of probabilities
	void makeFirstOrderModel();
	void makeSecondOrderModel();
	void makeModel();
	string makeString(vector <char>& myVector);
	void shiftVector(vector <char>& myVector, char newChar);	
	void readData();
	void countChars(string& name);
	void printModel();
	string adjustKeyToPrint(char key);
	void instantiate2DMap();
	void normalize();
	char findCorrelatingLetter(double& letterChance, string prevState);

};

#endif