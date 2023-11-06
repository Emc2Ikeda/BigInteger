// Name: DoublyLinkedList.h
// Date: 11/2/22
// Author: Ema Ikeda
// Description: h file for DoublyLinkedList generic class, which is used in BigInteger class

#ifndef DLL
#define DLL

#include "Node.h"
#include <string>
#include <iostream>
#include <fstream>
#include <typeinfo>
#include "IllegalArgumentException.h"
#include "NoSuchElementException.h"

using namespace std;

template <class T>
class DoublyLinkedList
{
protected:
    Node<T>* first;      //a pointer to the first of the linked list
    Node<T>* last;       //a pointer to the last node of the linked list
    Node<T>* iterator;   //an internal iterator for the linked list object
    int length;          //number of items in the linked list
public:
   
   //default no-argument constructor
   DoublyLinkedList();

   //destructor  
   ~DoublyLinkedList();

   //copy constructor
   DoublyLinkedList(const DoublyLinkedList<T> &);

   //copy assignment operator
   void operator=(const DoublyLinkedList<T> &); // void return type seems to make sense. Why DLL<T>?

   //returns true if the list is empty, false otherwise
   bool isEmpty();

   //returns the number of items in the list
   int getLength() const;

   //inserts a new item to the beginning of the list
   void insertFirst(const T &);
   // void insertFirst(const T &);

   //inserts a new item at the end of the list
   void insertLast(const T &) throw (IllegalArgumentException);

   //deletes the first item from the list
   void deleteFirst();

   //deletes the last item in the list
   void deleteLast();

   //destroys the list and makes it empty
   void clear();

   //iterator functions
   //sets the iterator to the beginning of the linked list
   void setIteratorFirst();

   //sets the iterator to the beginning of the linked list
   void setIteratorLast();

   //checks if the iterator has next
   bool hasNext();

   //checks if the iterator has prev
   bool hasPrev();

   //sets the iterator to the next node
   void next() throw (NoSuchElementException);

   //sets the iterator to the previous node
   void prev() throw (NoSuchElementException);

   //gets the data the iterator pointing at 
   T getData();

   Node<T>* getFirst();

   Node<T>* getLast();
   //friend functions
   // overloading operator<<
   template <class U>
   friend ostream& operator<<(ostream& out, const DoublyLinkedList<U> &);

   //overloading operator>>
   template <class U>
   friend istream& operator>>(istream& in, DoublyLinkedList<U> &);
};

// Print all nodes in DLL without spaces
template<class T>
ostream& operator<<(ostream& out, const DoublyLinkedList<T>& other)
{
   Node<T>* iterator = other.first;
   while (iterator != NULL) {
      out << iterator->data;
      iterator = iterator->next;
   }
   return out;
}

// read from file and into program. File is read from client
template<class T>
istream& operator>>(istream& in, DoublyLinkedList<T>& dll)
{
   // get only one line from test.txt, which is accessed from client.
   std::string line;
   getline(in, line, '\n');
   // get each digit from char in line, then insert to the back of DLL
   for (char lineChar: line) {
      int digit = lineChar - '0';
      dll.insertLast(digit);
   }
   return in;
}
#endif