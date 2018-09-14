/*
* Course: CMPS 2143 - OOP
*
* Purpose: define myVector type 
*
* @author Evan Jackson
* @version 1.0 09/13/2018
*/
#pragma once
#include <iostream>

using namespace std;

class myVector{
private:
  int *theVector;
  int vSize;
  int index;
  struct arrinfo
  {
	  int *arr;
	  int size;
  };
  void changeArray(int size, int baseSize);
public:
	int getIndex();
	int getvSize();
	myVector(int size);
	void push_back(int item, int originalSize);
	int pop_back(int originalSize);
	void print(ostream & outfile);
};