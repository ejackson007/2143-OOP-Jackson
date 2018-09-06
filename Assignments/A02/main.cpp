/**
* Course: CMPS 2143 - OOP
*
* Purpose: insert numbers into a dymanically allocated
* array, and then print them back out
*
* @author Evan Jackson
* @version 1.0 09/05/2018
*/

#include <iostream>

using namespace std;

int A[100];

struct Node
{
    int x;
    Node *next;
    Node()
    {
        x = -1;
        next = NULL;
    }
    Node(int n)
    {
        x = n;
        next = NULL;
    }
};

class List
{
  private:
    Node *Head;
    Node *Tail;
    int Size;

  public:
	  /**
	  * //++constructs the list
	  *
	  * @param {N/A}
	  * @return {N/A}
	  */
    List()
    {
        Head = Tail = NULL;
        Size = 0;
    }
	/**
	  * //++pushes a value into the list
	  *
	  * @param {int} the integer value to be put into the array
	  * @return {void}
	  */
    void Push(int val)
    {
        // allocate new memory and init node
        Node *Temp = new Node(val);

        if (!Head && !Tail)
        {
            Head = Tail = Temp;
        }
        else
        {
            Tail->next = Temp;
            Tail = Temp;
        }
        Size++;
    }

	/**
	  * //++inserts a value into the list
	  *
	  * @param {int} the integer value to be put into the array
	  * @return {void}
	  */
    void Insert(int val)
    {
        // allocate new memory and init node
        Node *Temp = new Node(val);

        // figure out where it goes in the list

        Temp->next = Head;
        Head = Temp;
        if (!Tail)
        {
            Tail = Head;
        }
        Size++;
    }

	/**
	  * //++prints the tail of the list
	  * //+does not remove the tail
	  *
	  * @param {N/A} 
	  * @return {void}
	  */
    void PrintTail()
    {
        cout << Tail->x << endl;
    }

	/**
	  * //++prints the entire contents of the list
	  * //+Starts at the head
	  *
	  * @param {N/A}
	  * @return {string} the entire contents of the list
	  */
    string Print()
    {
        Node *Temp = Head;
        string list;

        while (Temp != NULL)
        {
            list += to_string(Temp->x) + "->";
            Temp = Temp->next;
        }

        return list;
    }

	/**
	  * //++removes the last item of the list
	  *
	  * @param {N/A} 
	  * @return {int} value of 0 to show completion
	  * 
	  * not implemented
	  */
    int Pop()
    {
        Size--;
        return 0; //
    }

	/**
	  * //++concatonates two lists into one list
	  *
	  * @param {List} reads list of function and list passed in
	  * @return {NewList} concatonated list
	  */
    List operator+(const List &Rhs)
    {
        // Create a new list that will contain both when done
        List NewList;

        // Get a reference to beginning of local list
        Node *Temp = Head;

        // Loop through local list and Push values onto new list
        while (Temp != NULL)
        {
            NewList.Push(Temp->x);
            Temp = Temp->next;
        }

        // Get a reference to head of Rhs
        Temp = Rhs.Head;

        // Same as above, loop and push
        while (Temp != NULL)
        {
            NewList.Push(Temp->x);
            Temp = Temp->next;
        }

        // Return new concatenated version of lists
        return NewList;
    }
	/**
	  * //++returns a value from the list as if it were an array
	  *
	  * @param {int} the index location of the value desired from the list
	  * @return {int} integer in index location
	  *
	  * Implementation of [] operator.  This function returns an
      * int value as if the list were an array.
	  */

    int operator[](int index)
    {
        Node *Temp = Head;

        if (index >= Size)
        {
            cout << "Index out of bounds, exiting";
            exit(0);
        }
        else
        {

            for (int i = 0; i < index; i++)
            {
                Temp = Temp->next;
            }
            return Temp->x;
        }
    }

	  /**
	  * //++prints out list onto outfile
	  * //+gets direct info from list with the "friend"
	  *
	  * @param {os, L} passes in file for outfile, as well as list to print
	  * @return {os} outfile
	  */
    friend ostream &operator<<(ostream &os, List L)
    {
        os << L.Print();
        return os;
    }
};

/**
	  * //++Declares 2 lists, fills them, prints the tail, concatonates the 2 and then prints the pair
	  *
	  * @param {int, char} reads list of function and list passed in
	  * @return {int} 0 to signify completion
	  */
int main(int argc, char **argv)
{
    List L1;
    List L2;

    for (int i = 0; i < 25; i++)
    {
        L1.Push(i);
    }

    for (int i = 50; i < 100; i++)
    {
        L2.Push(i);
    }

    //cout << L1 << endl;
    L1.PrintTail();
    L2.PrintTail();

    List L3 = L1 + L2;
    cout << L3 << endl;

    cout << L3[5] << endl;
    return 0;
}