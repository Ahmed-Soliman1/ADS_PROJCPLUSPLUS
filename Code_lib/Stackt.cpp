// Stackt.cpp
#include "Stackt.h"
#include <stdexcept>
#include <iostream>
#include "TreeNode.h"

using namespace std;
// Implementations for the Stackt class template

template <typename T>
Stackt<T>::Stackt(int size) : capacity(size), top(-1) {
    // Constructor implementation is complete.
    // Initializes the stack with a given capacity.
    // Creates an array to hold the stack elements and sets the initial top index to -1.
    arr = new T[capacity];
}

template <typename T>
Stackt<T>::Stackt(const Stackt& other) : capacity(other.capacity), top(other.top) {
    // Student Task: Implement the copy constructor
    // The copy constructor should create a new array with the same capacity as 'other'
    arr = new T[capacity];
    // Then, it should copy all elements from the 'other' stack to this stack.
    // Hints:
    // - Allocate memory for 'arr' with the same capacity as 'other'
    // - Use a loop to copy each element from 'other.arr' to 'arr'
    for (int i = 0; i < capacity; i++) {
        arr[i] = other.arr[i];
    }
}

template <typename T>
Stackt<T>& Stackt<T>::operator=(const Stackt& other) {
    // Student Task: Implement the assignment operator
    // This function should copy the contents of 'other' to this stack.
    // Check if the current object is the same as 'other' to avoid self-assignment.
    // Steps:
    // - Delete the current 'arr' to free memory
    if (this != &other) {
        delete[] arr;
    }
    // - Allocate new memory for 'arr' with the same capacity as 'other'
    // - Copy 'top' and 'capacity' from 'other' to this stack
    capacity = other.capacity;
    top = other.top;

    // - Use a loop to copy each element from 'other.arr' to 'arr'
    // - Return *this to allow for chained assignment
    arr = new T[capacity];
    for (int i = 0; i < capacity; i++) {
        arr[i] = other.arr[i];
    }
    return *this;

}

template <typename T>
Stackt<T>::~Stackt() {
    // Destructor implementation is complete.
    // Frees up the dynamically allocated memory for the stack.
    delete[] arr;
}

template <typename T>
void Stackt<T>::push(T element) {
    // Student Task: Implement the push function
    // This function should add a new element to the top of the stack.
    // Steps:
    // - Check if the stack is full using the isFull() method.
    if(isFull()) {
        throw overflow_error("Stack is full");
    }
    // - If full, throw an overflow_error.
    arr[++top] = element;
    // - Otherwise, increment 'top' and add the new element at the 'top' position in 'arr'.
}

template <typename T>
T Stackt<T>::pop() {
    // Student Task: Implement the pop function
    // This function should remove and return the top element from the stack.
    // Steps:
    // - Check if the stack is empty using the isEmpty() method.
    // - If empty, throw an underflow_error.
    if(isEmpty()) {
        throw underflow_error("Stack is empty");
    }

    // - Otherwise, return the element at 'top' and decrement 'top'.
    return arr[top--];
}

template <typename T>
T Stackt<T>::peek() const {
    // Student Task: Implement the peek function
    // This function should return the top element of the stack without removing it.
    // Steps:
    // - Check if the stack is empty using the isEmpty() method.
    // - If empty, throw an underflow_error.
    if(isEmpty()) {
        throw underflow_error("Stack is empty");
    }


    // - Otherwise, return the element at 'top'.
    return arr[top];
}

template <typename T>
bool Stackt<T>::isEmpty() const {
    // Student Task: Implement the isEmpty function
    // This function should return true if the stack is empty, and false otherwise.
    // Hint: The stack is empty when 'top' is -1.
    if (top == -1) {return true;}
    return false;

}

template <typename T>
bool Stackt<T>::isFull() const {
    // Student Task: Implement the isFull function
    // This function should return true if the stack is full, and false otherwise.
    // Hint: The stack is full when 'top' is equal to 'capacity - 1'.
    if (top == capacity-1) {return true;}
    return false;

}
template <typename T>
int Stackt<T>::size() const {
    return top + 1;  // Return the number of elements in the stack
}

// template <typename T>
// void Stackt<T>::display() const {
//     // This function is implemented for you.
//     // It prints all elements of the stack from top to bottom.
//     for (int i = top; i >= 0; i--) {
//         cout << arr[i] << " ";
//     }
//     cout << endl;
// }


// Explicit instantiation of Stackt for the types used in the project
template class Stackt<int>;
template class Stackt<char>;
template class Stackt<double>;
template class Stackt<TreeNode*>;