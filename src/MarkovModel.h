#include <String>
#include <map>

#ifndef MARKOVMODEL_H
#define MARKOVMODEL_H

using namespace std;

class MarkovModel{
public:
	//Constructor for a Markov Model
	//namesPath - the location of the file from which the model will be made
	MarkovModel(string filePath);

	//Deconstructor
	~MarkovModel();

	string makeFirstOrderItem();
	string makeSecondOrderItem();
private:

	string namesPath;
	ifstream namesFile;
	map <string, map <char, double>> probabilityModel;

	//Opens the file
	void openFile();
	//Closes the file
	void closeFile();
	//Makes the whole Markov Chain model, the 2D array of probabilities
	void makeFirstOrderModel();
	void makeSecondOrderModel();
	
	void readData();
	void countChars(string& name);
	void printModel();
	string adjustKeyToPrint(char key);
	void instantiate2DMap();
	void normalize();
	char findCorrelatingLetter(double& letterChance, string prevState);

};

#endif