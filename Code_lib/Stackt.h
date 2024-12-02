// Stackt.h
#ifndef STACKT_H
#define STACKT_H

#include <iostream>

template <typename T>
class Stackt {
private:
    T* arr;           // Array to store stack elements
    int top;          // Index of the top element
    int capacity;     // Maximum capacity of the stack

public:
    Stackt(int size);         // Constructor
    Stackt(const Stackt& other); // Copy constructor
    Stackt& operator=(const Stackt& other); // Assignment operator
    ~Stackt();                // Destructor

    void push(T element);     // Add an element to the stack
    T pop();                  // Remove and return the top element
    T peek() const;           // Return the top element without removing it
    int size() const;
    bool isEmpty() const;     // Check if the stack is empty
    bool isFull() const;      // Check if the stack is full
    // void display() const;     // Display the elements in the stack
};

#endif // STACKT_H