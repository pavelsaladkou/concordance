/*-- Queue.h contains the declaration of the template class Queue --------------
   Basic operations:
     Constructor:      Constructs an empty queue
	 copy constructor: Creates a copy of the queue
     empty:       Checks if a queue is empty
     enqueue:     Modifies a queue by adding a value at the back
     front:       Accesses the front queue value; leaves queue unchanged
     dequeue:     Modifies a queue by removing the value at the front
     display:     Displays the queue elements from front to back
	 =:           Assignment operator overloaded
	 <<:          Insertion operator overloaded
	 
	 Written by: Pavel Saladkou
	 Written for: CSCI 1107, Anoka-Ramsey Community College
------------------------------------------------------------------------------*/
#pragma once
#include <iostream>
using namespace std;

template <typename T>
class Queue
{
 public:
  /* Constructor */
  Queue();
  /*-----------------------------------------------------------------------
    Construct a Queue object.

    Precondition:  None.
    Postcondition: An empty Queue object has been constructed; myFront 
        and myBack are initialized to -1 and myArray is an array with
        QUEUE_CAPACITY elements of type QueueElement.
   ----------------------------------------------------------------------*/
  
  /* Destructor */
  ~Queue();
  /*-----------------------------------------------------------------------
	Destruct a Queue object.

	Precondition:  None.
	Postcondition: Queue object has been destroyed
   ----------------------------------------------------------------------*/

  /* Copy Constructor */
  Queue(const Queue<T> &original);
  /*-----------------------------------------------------------------------
  Create a deep copy of a Queue object.

  Precondition:  None.
  Postcondition: a copy of Queue has been created
 ----------------------------------------------------------------------*/

  /* empty function */
  bool empty() const;
  /*-----------------------------------------------------------------------
    Check if queue is empty.

    Precondition: None.
    Postcondition: True is returned if the queue is empty and false is
        returned otherwise.
   ----------------------------------------------------------------------*/

  /* enqueue function */
  void enqueue(const T & value);
  /*-----------------------------------------------------------------------
    Add a value to a queue.

    Precondition:  value is to be added to this queue.
    Postcondition: value is added to back of queue provided there is space;
        otherwise, a queue-full message is displayed and execution is
        terminated.
   -----------------------------------------------------------------------*/

  /* dequeue function */
  void dequeue();
  /*-----------------------------------------------------------------------
	Remove value at front of queue (if any).

	Precondition:  Queue is nonempty.
	Postcondition: Value at front of queue has been removed, unless queue
		is empty; in that case, an error message is displayed and
		execution is terminated.
   ----------------------------------------------------------------------*/

  /* display function */
  void display(ostream & out) const;
  /*-----------------------------------------------------------------------
    Output the values stored in the queue.

    Precondition:  ostream out is open.
    Postcondition: Queue's contents, from front to back, have been output 
        to out.
   -----------------------------------------------------------------------*/

  /* front function */
  T front() const;
  /*-----------------------------------------------------------------------
    Retrieve value at front of queue (if any).

    Precondition:  Queue is nonempty.
    Postcondition: Value at front of queue is returned, unless queue is
        empty; in that case, an error message is displayed and a "garbage
        value" is returned.
   ----------------------------------------------------------------------*/

  /* assignment operator */
  void operator = (const Queue<T> &rhs);
  /*-----------------------------------------------------------------------
	Assignment operator overloaded for Queue objects.

	Precondition:  rhs is a valid Queue object
	Postcondition: rhs has been assigned to the left hand side object
   ----------------------------------------------------------------------*/

 private:
   class Node
   {
   public:
	   T data;
	   Node *next;
	   // -- Node constructor
	   Node(T value, Node * link = NULL)
		   : data(value), next(link)
	   {}
   };

   typedef Node * NodePointer;
   NodePointer myBack;

}; // end of class declaration

//--- Definition of Queue constructor
template <typename T>
Queue<T>::Queue() {	myBack = NULL; }

//--- Definition of destructor
template <typename T>
Queue<T>::~Queue()
{
	while (!empty())
	{
		dequeue();
	}
	delete myBack; // remove the last Node
}

//--- Definition of copy constructor
template <typename T>
Queue<T>::Queue(const Queue<T> &orig)
{
	myBack = NULL;                           //initialize a new Queue
	if (!orig.empty())
	{
		NodePointer ptr = orig.myBack->next; //start at the front
		do 
		{
			enqueue(ptr->data);              //insert a Node
			ptr = ptr->next;
		} 
		while (ptr != orig.myBack->next);    //and traverse the original Queue
	}
}

//--- Definition of empty()
template <typename T>
inline bool Queue<T>::empty() const 
{ 
	return (myBack == NULL); 
}

//--- Definition of dequeue()
template <typename T>
inline void Queue<T>::dequeue()
{
	if (!empty())
	{
		if (myBack == myBack->next)    //if only one Node is in the Queue
		{
			delete myBack;
			myBack = NULL;             //make it an empty Queue
		}
		else                          
		{
			NodePointer cur = myBack->next;
			myBack->next = cur->next;
			delete cur;                //otherwise, delete the front
		}
	}
	else
		cout << "Queue is already empty\n";
}

//--- Definition of enqueue()
template <typename T>
inline void Queue<T>::enqueue(const T & value)
{
	NodePointer newptr = new Node(value);
	if (empty())
		myBack->next = myBack = newptr; //create first Node
	else
	{
		newptr->next = myBack->next;    //insert the Node
		myBack->next = newptr;          //and point to it from the back
		myBack = newptr;                //and to itself
	}
}

//--- Definition of display()
template <typename T>
inline void Queue<T>::display(ostream & out) const
{
	NodePointer cur = myBack->next; //start at the front
	if (!empty())
	{
		while (cur != myBack)      
		{
			out << cur->data << " ";
			cur = cur->next;
		}
		out << cur->data;          //display the last element
	}
	else
		out << "Queue is empty\n";
	//out << endl;
}

//--- Definition of front()
template <typename T>
inline T Queue<T>::front() const
{
	if (!empty())
		return (myBack->next->data);
	else
	{
		cerr << "*** Queue is empty -- returning garbage value ***\n";
		T * temp = new(T);
		T garbage = *temp;
		delete temp;
		return garbage;
	}
}

//--- Definition of assignment operator
template <typename T>
void Queue<T>::operator = (const Queue<T> &rhs)
{
	if (this != &rhs)     //check for self assignment
	{
		this->~Queue();   //free up the memory
		if (!rhs.empty())
		{
			myBack = new Node(rhs.myBack->data); //start creating a Queue
			NodePointer orig = rhs.myBack,       //keep track of the original
			            cur = myBack;            //keep track of the new
			while(orig->next != rhs.myBack)      //run through the original 
			{
				orig = orig->next;               //switch to the next in orig
				cur->next = new Node(orig->data);//and copy the Node
				cur = cur->next;                 //switch to the next in new
			}
			cur->next = myBack;                  //close the curcuit
		}
	}
}

/*------------------------------------------------------------------------------
	Insertion operator overloaded for Queue objects.

	Precondition:  q is the Queue to be inserted
	Postcondition: q has been inserted into out
 -----------------------------------------------------------------------------*/
template<typename T>
ostream & operator << (ostream &out, const Queue<T> &q)
{
	if (!q.empty())
		q.display(out);	
	else
		out << "- Queue is empty -\n";
	return out;
}