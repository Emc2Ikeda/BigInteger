// Name: DoublyLinkedList.cpp
// Date: 11/2/22
// Author: Ema Ikeda
// Description: cpp file for DoublyLinkedList generic class

#include "DoublyLinkedList.h"
#include "IllegalArgumentException.h"

// default no-argument constructor
template <class T>
DoublyLinkedList<T>::DoublyLinkedList() : first(nullptr), last(nullptr), iterator(nullptr), length(0)
{
}

template <class T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>& other)
{
    first = NULL;
    last = NULL;
    length = 0;
    Node<T>* temp = other.first; // temporary pointer to the first node in other

    // fill this with nodes from other's nodes' data using while loop
    // set iterator to first of other
    int data;
    iterator = other.first;
    while (iterator != NULL) {
        data = iterator->data;
        // next();
        insertLast(data);
        iterator = iterator->next;
    }
}

//destructor  
template <class T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
    clear();
}

template <class T>
bool DoublyLinkedList<T>::isEmpty()
{
    return length == 0;
}

//returns the number of items in the list
template <class T>
int DoublyLinkedList<T>::getLength() const
{
    return length;
}

//inserts a new item to the beginning of the list
template <class T>
void DoublyLinkedList<T>::insertFirst(const T& item)
{
    Node<T>* newNode = new Node<T>;
    newNode->data = item; // new node with item

    newNode->next = nullptr;
    newNode->prev = nullptr;

    if (isEmpty()) {
        first = newNode;
        last = newNode;
    }
    else {
        first->prev = newNode; // make newNode first and place ahead of the old first
        newNode->next = first;
        first = newNode;
    }
    length++;
}

//inserts a new item at the end of the list
template <class T>
void DoublyLinkedList<T>::insertLast(const T& item) throw (IllegalArgumentException)
{
    // check if item's type is the same as that of DLL
    bool ableToInsert = typeid(item).name() == typeid(T).name();
    if (ableToInsert) {
        Node<T>* newNode = new Node<T>;
        newNode->data = item;
        newNode->next = nullptr;
        newNode->prev = nullptr;

        if (isEmpty()) {
            first = newNode;
            last = newNode;
        }
        else {
            last->next = newNode;
            newNode->prev = last;
            last = newNode;
        }
        length++;
    }

    std::string msg = "Invalid data type\n";
    // throw IllegalArgumentException;
}

// deletes the first item from the list
template <class T>
void DoublyLinkedList<T>::deleteFirst()
{
    Node<T>* temp;
    if (!isEmpty()) {
        temp = first;
        if (first->next == nullptr) { // edge case when there is only 1 node
            first = nullptr;
        }
        else {
            first = temp->next;
            first->prev = nullptr;
        }
        delete temp;
        temp = nullptr;
        length--;
    }
}

// deletes the last item in the list
template <class T>
void DoublyLinkedList<T>::deleteLast()
{
    Node<T>* temp;
    if (!isEmpty()) {
        temp = last;
        if (length == 1) { // edge case when there is only 1 node
            last = nullptr;
        }
        else {
            last = temp->prev;
            last->next = nullptr;
        }
        delete temp;
        temp = nullptr;
        length--;
    }
}

//destroys the list and makes it empty
template <class T>
void DoublyLinkedList<T>::clear()
{
    // call deleteFirst() while length != 0
    while (!isEmpty()) {
        deleteFirst();
    }
}

 //sets the iterator to the beginning of the linked list
template <class T>
void DoublyLinkedList<T>::setIteratorFirst()
{
    iterator = first;
}

//sets the iterator to the beginning of the linked list
template <class T>
void DoublyLinkedList<T>::setIteratorLast()
{
    iterator = last;
}

//checks if the iterator has next
template <class T>
bool DoublyLinkedList<T>::hasNext()
{
    // set iterator to first if it is NULL
    if (iterator == NULL) {
        setIteratorFirst();
    }

    if (length == 0) { // empty list does not have next
        return false;
    }
    else if (iterator->next == NULL) { // if iterator is at end, then iterator is equal to last
        return false;
    }
    else {
        return true;
    }
}

//checks if the iterator has prev
template <class T>
bool DoublyLinkedList<T>::hasPrev()
{
    if (iterator == NULL) {
        setIteratorLast();
    }
    if (length == 0) { // empty list does not have next
        return false;
    }
    else if (iterator->prev == NULL) { // if iterator is at end, then iterator is equal to last
        return false;
    }
    else {
        return true;
    }
}

//sets the iterator to the next node
template <class T>
void DoublyLinkedList<T>::next() throw (NoSuchElementException)
{
    if (hasNext()) {
        iterator = iterator->next;
    } else {
        std::string message = "No next node\n";
        throw NoSuchElementException(message);
    }
}

//sets the iterator to the previous node
template <class T>
void DoublyLinkedList<T>::prev() throw (NoSuchElementException)
{
    if (hasPrev()) {
        iterator = iterator->prev;
    } else {
        std::string message = "No previous node\n";
        throw NoSuchElementException(message);
    }
}

//gets the data the iterator pointing at
template <class T>
T DoublyLinkedList<T>::getData()
{
    return iterator->data;
}

template <class T> 
Node<T>* DoublyLinkedList<T>::getFirst() {
    return first;
}

template <class T>
Node<T>* DoublyLinkedList<T>::getLast() {
    return last;
}

template <class T>
void DoublyLinkedList<T>::operator=(const DoublyLinkedList<T>& other)
{
    // fill this with nodes from other's nodes' data using while loop
    // set iterator to first of other
    if (!isEmpty()) {
        clear();
    }

    int newData;
    iterator = other.first;
    Node<T>* currentNode = first;

    while (iterator != NULL) {
        newData = getData();
        insertLast(newData);
        iterator = iterator->next;
    }
}