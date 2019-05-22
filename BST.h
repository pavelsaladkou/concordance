#pragma once
#include <iostream>
#include "Queue.h"
#include <new>
using namespace std;

//struct to contain a word and a line on which it was found in a text file
struct Token
{
	string word;
	int line;

	//Default constructor
	Token() : word(""), line(0) {};

	//Explicit constructor
	Token(string x, int y) : word(x), line(y) {};
};

class BST
{
 public:
  /***** Function Members *****/
  BST();
  /*------------------------------------------------------------------------
    Construct a BST object.

    Precondition:  None.
    Postcondition: An empty BST has been constructed.
   -----------------------------------------------------------------------*/

  ~BST();
  /*------------------------------------------------------------------------
	Destroy a BST object.

	Precondition:  None.
	Postcondition: BST object has been destroyed.
   -----------------------------------------------------------------------*/

  bool empty() const;
  /*------------------------------------------------------------------------
    Check if BST is empty.

    Precondition:  None.
    Postcondition: Returns true if BST is empty and false otherwise.
   -----------------------------------------------------------------------*/
   
  void insert(Token & item);
  /*------------------------------------------------------------------------
    Insert item into BST.

    Precondition:  None.
    Postcondition: BST has been modified with item inserted at proper 
        position to maintain BST property. 
  ------------------------------------------------------------------------*/

  void inorder(ostream & out) const;
  /*------------------------------------------------------------------------
    Inorder traversal of BST.

    Precondition:  ostream out is open.
    Postcondition: BST has been inorder traversed and values in nodes 
        have been output to out.
    Note: inorder uses private auxiliary function inorderAux().
 ------------------------------------------------------------------------*/
 
 private:
  /***** Node class *****/
  class BinNode 
  {
   public:
    Token data;
	Queue<int> occurence;
    BinNode * left;
    BinNode * right;

    // BinNode constructors
    // Default -- data part is default T value; both links are null.
    BinNode()
    : left(NULL), right(NULL)
    {}

    // Explicit Value -- data part contains item; both links are null.
    BinNode(Token item)
    : data(item), left(NULL), right(NULL)
    {}

  };// end of class BinNode declaration

  typedef BinNode * BinNodePointer; 
  
  /***** Private Function Members *****/
  void inorderAux(ostream & out, 
                  BinNodePointer subtreePtr) const;
  /*------------------------------------------------------------------------
    Inorder traversal auxiliary function.

    Precondition:  ostream out is open; subtreePtr points to a subtree 
        of this BST.
    Postcondition: Subtree with root pointed to by subtreePtr has been
        output to out.
  ------------------------------------------------------------------------*/

  void destroy(BinNodePointer &subtreeRoot);
  /*------------------------------------------------------------------------
	Destroy function.

	Precondition:  A valid BST object.
	Postcondition: BST object has been deleted.
	------------------------------------------------------------------------*/
 
 /***** Data Members *****/
  BinNodePointer myRoot; 

}; // end of class template declaration

//--- Definition of constructor
inline BST::BST()
: myRoot(NULL)
{}

//--- Definition of destructor
inline BST::~BST() { destroy(myRoot); }

//--- Definition of empty()
inline bool BST::empty() const { return myRoot == NULL; }

//--- Definition of insert()
inline void BST::insert(Token & t)
{
   BST::BinNodePointer 
        locptr = myRoot,      // search pointer
        parent = NULL;        // pointer to parent of current node
   bool found = false;        // indicates if item already in BST
   while (!found && locptr != NULL)
   {
      parent = locptr;
      if (t.word < locptr->data.word)       // descend left
         locptr = locptr->left;
      else if (locptr->data.word < t.word)  // descend right
         locptr = locptr->right;
	  else 
	  {
		  found = true;						 // item found
		  locptr->occurence.enqueue(t.line); //insert line number into queue
	  }                                      
         
   }
   if (!found)
   {                                         // construct node containing item
      locptr = new(nothrow) BST::BinNode(t);  
      if (locptr == NULL)	
      {
          cerr << "*** Out of memory -- terminating program ***\n";
		  exit(1);
      }
	  if (parent == NULL) // empty tree
	  {
		  myRoot = locptr;
		  myRoot->occurence.enqueue(t.line); //insert line number into queue
	  }
	  else if (t.word < parent->data.word)     // insert to left of parent
	  {
		  parent->left = locptr;
		  locptr->occurence.enqueue(t.line); //insert line number into queue
	  }
	  else                                     // insert to right of parent
	  {
		  parent->right = locptr;
		  locptr->occurence.enqueue(t.line); //insert line number into queue
	  }
   }
}

//--- Definition of inorder()
inline void BST::inorder(ostream & out) const
{ 
   inorderAux(out, myRoot); 
}

//--- Definition of inorderAux()
void BST::inorderAux(ostream & out, 
                               BinNodePointer subtreeRoot) const
{
   if (subtreeRoot != 0)
   {
      inorderAux(out, subtreeRoot->left);    // L operation
	  out << subtreeRoot->data.word << "  "
		  << subtreeRoot->occurence;         // V operation
	  cout << endl;
      inorderAux(out, subtreeRoot->right);   // R operation
   }
}

//--- Definition of destroy()
inline void BST::destroy(BinNodePointer &subtreeRoot)
{
	if (subtreeRoot != NULL)
	{
		destroy(subtreeRoot->left);
		destroy(subtreeRoot->right);
		delete subtreeRoot;
	}
}