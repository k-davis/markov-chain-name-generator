#include <String>

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
private:

	string namesPath;
	ifstream namesFile;
	double** modelArray;
	int** modelCountArray;
	
	//Opens the file
	void openFile();
	//Closes the file
	void closeFile();
	//Makes the whole Markov Chain model, the 2D array of probabilities
	void makeModel();
	//Takes a character and finds what index in the model array it corresponds with
	int convertCharToModelIndex(char charToConvert);
};

#endif