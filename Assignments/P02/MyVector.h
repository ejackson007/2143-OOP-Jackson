/*
* Course: CMPS 2143 - OOP
*
* Purpose: Create and define functions of myVector class
*
* @author Evan Jackson
* @version 1.0 09/13/2018
*/
#include <iostream>

using namespace std;

class myVector {
private:
	int *vPtr;      // int pointer to array
	int maxSize;    // max size of array
	int minSize;    // min size of array
	int index;      // current location to insert or remove
	int* _resize(int);

public:
	myVector(int size);
	void pushBack(int item);
	void pushBack(int A[], int size);
	int popBack();
	double percentFull();
	int* resize(double);
	int* resize(int);

	void print();
	int size();
	void size(int);
	int vSize();
	void myVector::setIndex(int x);

	// Implementation of [] operator.  This function must return a 
	// refernce as array element can be put on left side 
	int& operator[](int i)
	{
		if (i >= maxSize)
		{
			cout << "Array index out of bound, exiting\n";
			exit(0);
		}
		else if (i >= index) {
			cout << "Warning: vector[" << i << "] is undefined ...\n";
		}
		return vPtr[i];
	}

	// Implementation of << operator. This function will gp through the
	// vectors value, used for cout 
	friend ostream& operator<<(ostream& os, myVector V) {
		for (int i = 0; i < V.index; i++) {
			os << V.vPtr[i] << " ";
		}
		//os<<"test"<<endl;
		return os;
	}

	// Implementation of + operator. This function needs a return of a Vector
	// so that it can be printed, or = to another function
	myVector operator+(myVector& v1)
	{
		myVector V(maxSize);

		V.setIndex(size());


		for (int i = 0; i < V.size(); i++)
		{
			if (i < size() && i < v1.size())
				V[i] = vPtr[i] + v1[i];
			else if (i >= v1.size() && i < size())
				V[i] = vPtr[i];
		}
		return V;
	}

	// Implementation of - operator. This function needs a return of a Vector
	// so that it can be printed, or = to another function
	myVector operator-(myVector& v1)
	{
		myVector V(maxSize);

		V.setIndex(size());

		for (int i = 0; i < V.size(); i++)
		{
			if (i < size() && i < v1.size())
				V[i] = vPtr[i] - v1[i];
			else if (i >= v1.size() && i < size())
				V[i] = vPtr[i];
		}
		return V;
	}

	// Implementation of * operator. This version of the function multiples
	// two vectors
	myVector operator*(myVector& v1)
	{
		myVector V(maxSize);

		V.setIndex(size());


		for (int i = 0; i < V.size(); i++)
		{
			if (i < size() && i < v1.size())
				V[i] = vPtr[i] * v1[i];
			else if (i >= v1.size() && i < size())
				V[i] = vPtr[i];
		}
	 return V;
  }

	// Implementation of * operator. This version of the function takes a vector
	// and multiplies all the integers in it by a constant int.
  myVector operator*(int x)
  {

	 myVector V(maxSize);

	 V.setIndex(size());

	  for (int i = 0; i < size(); i++)
		  V[i] = vPtr[i] * x;

	  return V;

  }

  // Implementation of / operator. This function needs a return of a Vector
	// so that it can be printed, or = to another function
 myVector operator/(myVector& v1)
  {
	myVector V(maxSize);

	V.setIndex(size());


	for (int i = 0; i < V.size(); i++)
		{
			if (i < size() && i < v1.size())
				V[i] = vPtr[i] / v1[i];
			else if (i >= v1.size() && i < size())
				V[i] = vPtr[i];
		}
	 return V;
  }

 // Implmentation of = operator. This function takes one vector, and sets
 // it equal to another vector, This si done by refernece, so return Vector
 // is a place holder and has no purpose
  myVector& operator=(myVector& v1)
  {
	  int vectorSize;

	  if (maxSize < v1.size())
	  {
		  size(v1.size());
	  }
	  else
		  vectorSize = maxSize;

	//just a place holder as something to pass back		
	  myVector V(10);

	  for (int i = 0; i < v1.size(); i++)
	  {

		  vPtr[i] = v1[i];
	  }

	  setIndex(v1.size());
	  
	  return V;

  }

  // Implmentation of == operator. It takes two vectors and compares the two
  // returning a boolean true or false.
 bool operator==(myVector& rhs)
 {
	 if (size() != rhs.size())
		 return false;

	 for (int i = 0; i < size(); i++)
	 {
		 if (vPtr[i] != rhs[i])
			 return false;
	 }

	 return true;

 }
};


/**
* Function constructor
*   Sets up the vector
* @param {int} size : initial size of vector 
* @return void
*/
myVector::myVector(int size){
  maxSize = size;
  minSize = size;
  // create the array of vSize
  vPtr = new int[maxSize];
  index = 0;
}

/**
* Function print
*   Prints the current values in the vector
* @param void  
* @return void
*/
void myVector::print(){
  for(int i=0;i<index;i++){
    cout<<vPtr[i]<<" ";
  }
  cout<<endl;
}

/**
* Function pushBack
*   Adds value to vector
* @param {int} item : integer value  
* @return void
*/
void myVector::pushBack(int item){
  if(index >= maxSize){
    vPtr = resize(1.5);
  }
  vPtr[index++] = item;
}

/**
* Function pushBack
*	Adds an array to the end of a vector
* @param {int} item : int A[], int size  
* @return void
*/
void myVector::pushBack(int A[], int size)
{
	for (int i = 0; i < size; i++)
		pushBack(A[i]);
}

/**
* Function popBack
*   Returns value from vector
* @param none 
* @return {int} : last item on vector
*/
int myVector::popBack(){

  index--;

  if(index < 0){
    //dammit
  }

  if(percentFull() <= .4){
    vPtr = resize(.5);
  }

  return vPtr[index];
}

/**
* Function resize
*   Resizes our vector based on passed in ratio
* @param {double} ratio : new array size 
* @return {int*} : pointer to new array
*/
int* myVector::resize(double ratio){
  // figure out what our new size is, bigger or smaller
  int newSize = maxSize * ratio;

  return _resize(newSize);
}

int* myVector::resize(int size){

  return _resize(size);
  
}

int* myVector::_resize(int newSize){
  // Lets keep our vector above some minimum size
  if(newSize < minSize){
    newSize = minSize;
  }

  // allocate new bigger vector
  int* vBigger = new int[newSize];

  //copy everything over
  for(int i=0;i<index;i++){
    vBigger[i] = vPtr[i];
  }

  // update new max size
  maxSize = newSize;

  // delete old memory
  delete [] vPtr;

  //return ptr to new memory
  return vBigger;
}

/**
* Function percentFull
*   helper function to calculate how full vector is
* @param none
* @return {double} : how full vector is
*/
double myVector::percentFull(){
  return double(index) / double(maxSize);
}

/**
* Function size
*    Returns number of current items in vector
* @param none
* @return {int} : num items
*/
int myVector::size(){
  return index;
}

/**
* Function size
*    Returns number of current items in vector
* @param none
* @return {int} : num items
*/
void myVector::size(int newSize){
  vPtr = _resize(newSize);
}

/**
* Function vSize
*    Returns actual size of allocated memory
* @param none
* @return {int} : mem size
*/
int myVector::vSize(){
  return maxSize;
}

void myVector::setIndex(int x)
{
	index = x;
}

