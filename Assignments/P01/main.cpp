/*
* Course: CMPS 2143 - OOP
*
* Purpose: Dynamically allocate an array that can grow and shrink exponentially
* depending on how many items are currentlly in it. 
*
* @author Evan Jackson
* @version 1.0 09/13/2018
*/
#include <iostream>
#include <fstream>
#include "myVector.h"

// added in so that code is easily changeable for different starting values
const int originalSize = 10;

using namespace std;

void printHeader(ofstream & outfile);

/*
* Executes the code and calls functions to create and array, input items
* and prints 
*
* @param {N/A}
* @return {0}
*/
int main() {
	ifstream infile;
	ofstream outfile;
	outfile.open("BigBoyOutput.txt");
	infile.open("BigBoyNumbers.txt");

	printHeader(outfile);

	int item;
	//myVector *original;
	//int *copy;

	// creates vector
	myVector V(originalSize);

	//checks for error if there is nothing in array
	V.pop_back(originalSize);


	for (int i = 0; i <= 2; i++)
	{
		infile >> item;
		V.push_back(item, originalSize);
	}


	V.print(outfile);

	// adds in items from infile
	for (int i = 0; i <= 1000; i++)
	{
		//item = rand() %1000;
		infile >> item;
		V.push_back(item, originalSize);
	}

	// how much memory is allocated currently
	outfile << "\nMemory locations Allocated: " << V.getvSize() << "\n\n"
		<< "Popping objects from Array!\n";

	// remove items from array
	for (int i = 0; i <= 998; i++)
		V.pop_back(originalSize);

	// how much memory is available now that it has been shrunk
	outfile << "\nMemory locations Allocated: " << V.getvSize() << endl;

	// outfile full array
	V.print(outfile);

	outfile.close();
	infile.close();

	return 0;

}

/*
* prints header for outfile
*
* @param {outfile}
* @return {void}
*/
void printHeader(ofstream & outfile)
{
	outfile << "Program by: Evan Jackson \n9/14/2018\n\n";
}