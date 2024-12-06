// Stackt.h
#ifndef STACKT_H
#define STACKT_H

#include <iostream>

template <typename T>
class Stackt {
private:
    T* array;           //array to act as container
    int top;          //holds the index of the top element
    int capacity;     //capacity of the stack

public:
    Stackt(int size);         // Constructor
    Stackt(const Stackt& other); // Copy constructor
    Stackt& operator=(const Stackt& other); // Assignment operator
    ~Stackt();                //destructor to free up memory
    bool isEmpty() const;     //checks if the stack is empty and returns true if so
    bool isFull() const;      //check if the stack is full
    int size() const;          //returns the number of elements in the stack
    void push(T element);     //add an element to the stack
    T pop();                  //remove the top element
    T peek() const;           //returns the top element without removing it



};

#endif // STACKT_H