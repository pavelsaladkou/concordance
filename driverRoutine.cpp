/* -----------------------------------------------------------------------------
   BST concordance.
   Constructs a concordance for a document stored in a file.

   Written by: Pavel Saladkou
   Written for: CSCI 1107, Anoka-Ramsey Community College
------------------------------------------------------------------------------*/
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <cassert>
#include "BST.h"
using namespace std;

const int ENGLISH = 26; //number of letters in English alphabet

/* -----------------------------------------------------------------------------
   azcheck() predicate function to check if the symbol is alpha

   Precondition: none
   Postcondition: true have been returned is the symbol is not alpha
------------------------------------------------------------------------------*/
bool azcheck(const char &c) { return !(isalpha(c)); }

/* -----------------------------------------------------------------------------
   Outputs concordance in alphabetical order with line numbers

   Precondition: valid BST concordance
   Postcondition: concordance has been output in alphabetical order with 
                  line numbers on which every word occured in txt file
------------------------------------------------------------------------------*/
void output(BST []);

/* -----------------------------------------------------------------------------
   Reads file through the file removing non alpha characters and constructs 
   concordance of all words stored in it

   Precondition:  fstream has been opened, valid BST object
   Postcondition: txt file have been extracted from the input stream and 
                  concordance has been created and saved in the BST object
------------------------------------------------------------------------------*/
void readFile(fstream &, BST []);

int main()
{
	BST concordance[ENGLISH];
	fstream inFile("concord.txt"); //open
	assert(inFile.good());         //check
	readFile(inFile, concordance); //read and format
	output(concordance);           //output
	inFile.close();                //close
	return 0;
}

//--- Definition of readFile()
void readFile(fstream &inFile, BST concordance[])
{
	string dataIn;
	int lineNumber = 1; //start counting lines in txt file from 1
	char newLine;       //keep track of new line character

	while (inFile >> dataIn)
	{
		//remove non alphanumeric characters (predicate azcheck is used)
		dataIn.erase(remove_if(dataIn.begin(), dataIn.end(), azcheck),
			dataIn.end());
		//convert to upper case
		transform(dataIn.begin(), dataIn.end(), dataIn.begin(), toupper);

		//create and insert Token into BST at a position [first_letter - 'A']
		if (!dataIn.empty())
		{
			Token x(dataIn, lineNumber);
			concordance[dataIn[0] - 'A'].insert(x);
		}

		newLine = inFile.peek(); //check for a new line 
		if (newLine == '\n')     //and increment if encountered
			lineNumber++;
	}
}

//--- Definition of output()
void output(BST concordance[])
{
	for (int i = 0; i < ENGLISH; i++)
	{
		cout << "Concordance [" << char(65 + i) << "]" << ":\n\n";
		if (!concordance[i].empty())
			concordance[i].inorder(cout);
		else
			cout << "<- EMPTY ->\n";
		cout << endl;
	}
}

