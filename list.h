#ifndef MYLIST_
#define MYLIST_
#include "node.h"

#include <iostream>
using namespace std;

template <class T>
class myList {
 private:
   int size;
   node<T> * head;
  public:
    myList() 
    { head = nullptr; size=0;  } 
    ~myList(); 
    void insert (T item);
    bool find (T item, long long int & compare);
    void remove();
    void printList();
    T front();
    int getSize() { return size;}
    bool isEmpty() { return size==0;}
};

/*
template <class T>
void myList<T>::insert(T item) {
    // Create a new node with the item
    node<T>* tmp = new node<T>(item);

    // If the list is empty, the new node becomes the head
    if (head == nullptr || head->data > item) {
        tmp->next = head;
        head = tmp;

    } else {
        // Otherwise, find the correct position in the list
        node<T>* current = head;
        while (current->next != nullptr && current->next->data < item) {
            current = current->next;
        }
        
        // Insert the new node at the correct position
        tmp->next = current->next;
        current->next = tmp;
    }

    // Increment size
    size++;
} */

template <class T>
void myList<T>:: insert (T item) {

  //first create a new node object with the item
  node<T> * tmp = new node<T>(item);

  //So what is the code that goes here?
  tmp->next = head;
  head = tmp;

  size++;  
}

/*
template <class T>
bool myList<T>::find(T item, long long int& compare) {
    // Traverse the list, checking each element
    node<T>* current = head;
    int compareValue;

    while (current != nullptr) {
        compare++; // Increment the comparison count
        compareValue = current->data.compare(item); // Stores the .compare value

        // Since the list is sorted, if current->data > item, we can stop
        if (compareValue == 0) {
            return true; // Item found
        }

        if (compareValue > 0) {
            return false; // Item not found (because the list is sorted)
        }

        current = current->next; // Move to the next node
    }

    return false; // Item not found after traversing the list
} */

template <class T>
bool myList<T>:: find (T item, long long int & compare) {

  //so search through the list and see if it exists
  //if yes, return true
  for (node<T>* tmp = head; tmp != nullptr; tmp = tmp->next) {
    compare++; // Increment the comparison count
    if (tmp->data == item) {
        return true;
    }
  }

  return false;
}



template <class T>
void myList<T>:: remove() {
  if (head != nullptr)  {
    //something in the list.  move to the next node.

    //Deletes the head
    node <T> * tmp = head;
    head = head->next;
    delete tmp;


    //decrement size
    size--;
  }
}

template <class T>
myList<T>:: ~myList() {

 while(!isEmpty())
   remove(); 
}

template <class T>
T myList<T>:: front () {
  if (head != nullptr) {
	return head->data;
  } else {
	return T(0);  //return the zero case here.
  }
}
template <class T>
void myList<T>::printList() {
    node<T>* current = head;
    while (current != nullptr) {
        cout << current->data << endl; // Print each word
        current = current->next; // Move to the next node
    }
}



#endif