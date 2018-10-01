/*
* Course: CMPS 2143 - OOP
*
* Purpose: Overload operators, as well as functions, to give extra utility
* to the myVector Class
*
* @author Evan Jackson
* @version 1.0 10/01/18
*/
#include <iostream>
#include "myVector.h"

using namespace std;


int main() {
  myVector v(20);
  myVector v2(15);
  //myVector V3(50);

  v.pushBack(8);
  //V1 containts : [8]

  v2.pushBack(10);
  v2.pushBack(20);
  v2.pushBack(30);
  //V2 contain: [10,20,30]

  // Declare some int array
  int A[] = { 1,2,3,4,5};

  v.pushBack(A, 5);
  //v contains: [8,1,2,3,4,5]

  v = v + v2;
  //v contains [18,21,32,3,4,5]

  cout << v << endl;
  //would print: [18,21,32,3,4,5] to standard out

  cout << v[2] << endl;
  //would print: 32 to standard out

  v2 = v2 * 3;
  //v2 contains: [30,60,90]

  v2 = v2 * v;
  //v2 contains: [540,1260,2880]

  v2[2] = 100;
  //v2 contains: [540,1260,100]

  (v - v2).print();
  //would print: [-522,-1239,-68,3,4,5]

  (v / v2).print();
  //would print: [0,0,0,3,4,5]
	// double to int conversion causes the 0's

  (v2 / v).print();
  //would print: [30,60,3]

  // created to test equality as well as inequality
  myVector tester(20);
  tester = v;

  if (tester == v)
	  cout << "The equality test was a success\n";
  else
	  cout << "The equality test was a failure\n";
  //should print that it was a success

  if (v == v2)
	  cout << "The equality test was a failure\n";
  else
	  cout << "The equality test was a success\n";
  //should print that it was a success

  system("pause");
  return 0;

}
