/*
* Course: CMPS 2143 - OOP
*
* Purpose: Define functions of myVector type
*
* @author Evan Jackson
* @version 1.0 09/13/2018
*/
#include <iostream>
#include "myVector.h"

using namespace std;

/*
* constructs the Vector 
*
* @param {int} the size of the array
* @return {N/A}
*/
myVector::myVector(int size)
{
	int i;
  vSize = size;
  theVector = new int[vSize];
  for (i = 0; i < vSize; i++)
	  theVector[i] = 0;
  //just so we have stuff to print!!!!!
  //for(i=0;i<vSize;i++){
  //  theVector[i] = i*2;
  //}
  index = 0;
}

/*
* Returns the index (amount of items + 1) of the Array
*
* @param {N/A}
* @return {int} index
*/
int myVector::getIndex ()
{
	return index;
}

/*
* Returns the size of the Array
*
* @param {N/A}
* @return {int} index
*/
int myVector::getvSize()
{
	return vSize;
}

/*
* Recieves item and puts it at end of array. Also checks if array neede so grow 
* Also passes originalSize for the changeArray function
* 
* @param {int, int} item to push, original size of Array
* @return {void}
*/
void myVector::push_back(int item, int originalSize)
{
	theVector[index] = item;
	if (index == vSize - 1)
	{
		//could not use *1.5, so did *1 + *.5
		vSize += (vSize/2);
		//pass original size to make sure it never becomes smaller than the
		//base size given
		changeArray(vSize, originalSize);
	}

	//index is equal to the next open space, therefore it must be incrimented
	//after the check for growth
	index++;
}


/*
* pops the item off of the end of the list and check if array needs to shrink
* Also passes originalSize for the changeArray function
*
* @param {int} originalSize
* @return {int} item from the array
*/
int myVector::pop_back(int originalSize)
{
	if (index == 0)
		return false;

	// more math to avoid double which kept messing up. Used for simplicity
	double percentChecker = vSize * .4;

	int arrayItem = theVector[index];
	index--;

	// this is when the array is smaller than the original size, When there is 
	// room to shrink there is no need to change them to 0 sense they will be 
	// deleted in the process of shrinking
	if (index <= originalSize)
	{
		theVector[index + 1] = 0;
		return arrayItem;
	}
	
	//Check if the array would shrink below 10
	if (percentChecker < originalSize)
	{
		vSize = originalSize;
		changeArray(vSize, originalSize);
	}

	// Shrinks the Array in half
	else if (index <= percentChecker)
	{
		vSize /= 2;
		changeArray(vSize, originalSize);
	}
	// while not used in this program, would be nice in most cases to have
	return arrayItem;
}


/*
* Makes new array of correct size, whether grow or shrink, and copy previous
* array into new array.
* 
* @param {int, int} size of new array, original size of Array
* @return {void}
*/
void myVector::changeArray(int size, int originalSize)
{
	//cout << "\nSIZE IS: " << size << endl;

	// must create new pointer for new array and deletion of the last one
	int *newArray;
	int *temp;

	newArray = new int [size];

	//initialize new array with zeros
	for (int i = 0; i < size; i++)
		newArray[i] = 0;
	
	//used if the array grows
	if (index < size)
	{
		for (int i = 0; i <= index; i++)
			newArray[i] = theVector[i];
	}

	//used if the Array shrinks
	else
	{
		for (int i = 0; i < size; i++)
			newArray[i] = theVector[i];
	}

	// Make sure index resets to 10, since the shrink was not congruent with the
	// removal
	if (size == originalSize)
		index = originalSize;

	// Temp used to theVector pointer isnt lost
	temp = theVector;
	theVector = newArray;
	delete[] temp;
	
}


/*
* Prints the entire Array
* 
* @param {outfile} file to print to
* @return {void}
*/
void myVector::print(ostream & outfile)
{
	outfile << endl;
	for (int i = 0; i < vSize; i++)
	{
		outfile << theVector[i] << " ";
		if (i % 10 == 0 && i != 0)
			outfile << endl;
	}
	outfile << endl;
}