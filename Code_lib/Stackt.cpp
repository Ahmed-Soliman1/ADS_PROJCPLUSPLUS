#include "Stackt.h"
#include <stdexcept>
#include <iostream>
#include "TreeNode.h"

using namespace std;

//Stack constructor
template <typename T>
Stackt<T>::Stackt(int size) : capacity(size), top(-1) {
    array = new T[capacity]; //creates array to hold stack elements
}
//Copy constructor
template <typename T>
Stackt<T>::Stackt(const Stackt& other) : capacity(other.capacity), top(other.top) {

    array = new T[capacity];
    for (int i = 0; i < capacity; i++) {
        array[i] = other.array[i];
    }
}
//overloading the assignment operator
template <typename T>
Stackt<T>& Stackt<T>::operator=(const Stackt& other) {

    if (this != &other) {
        delete[] array;
    }
    capacity = other.capacity;
    top = other.top;


    array = new T[capacity];
    for (int i = 0; i < capacity; i++) { //copies each element from other.array to array
        array[i] = other.array[i];
    }
    return *this;

}
//destructor to delete the array and free up memory
template <typename T>
Stackt<T>::~Stackt() {

    delete[] array;
}
//push function to add elements on top of the stack
template <typename T>
void Stackt<T>::push(T element) {
    if(isFull()) {
        //checks if stack is full and if so throws an overflow error
        throw overflow_error("Stack is full");
    }
    //if it isn't full the elemelt will be added in the stack
    array[++top] = element;
}

template <typename T>
T Stackt<T>::pop() {
    // checks if stack is empty and if so throws an underflow error
    if(isEmpty()) {
        throw underflow_error("Stack is empty");
    }

    // if it isn't empty the top element is removed
    return array[top--];
}

template <typename T>
T Stackt<T>::peek() const {
    //checks if the stack is empty if so throws underflow error
    if(isEmpty()) {
        throw underflow_error("Stack is empty");
    }
    //if not, simply returns the top element without removing it
    return array[top];
}

template <typename T>
//returns true if stack is empty
bool Stackt<T>::isEmpty() const {
    //if the top is -1 then the stack is empty
    return (top == -1) ? true : false;
}
//returns true if stack is full
template <typename T>
bool Stackt<T>::isFull() const {
    // the stack is full if top is equal to the capacity - 1
    return (top == capacity-1) ? true : false;
}
//returns the number of elements in the stack not the actual size (not the capacity)
template <typename T>
int Stackt<T>::size() const {
    return top + 1;
}




//explicit instantiations for the stack types used
template class Stackt<int>;
template class Stackt<char>;
template class Stackt<double>;
template class Stackt<TreeNode*>;