
#ifndef DSVECTOR_H
#define DSVECTOR_H

#include<iostream>

using namespace std;

// A vector is an array that will resize itself as needed, i.e A vector is just a resizable dymanic array. It grows dynamically.

// In terms of data structure, a vector can work as a stack, but a stack cannot work as a vector.
// A stack is like a vector but only supports "First in Last out" functions like push(), pop() and peek(). 
// A vector can do other things, like insert an element into anywhere or delete an element at anywhere. 

// Vector is template class and is C++ only construct whereas arrays are built-in language construct and present in both C and C++.
// Vector are implemented as dynamic arrays with list interface whereas arrays can be implemented as statically or dynamically 
// with primitive data type interface. (GeeksforGeeks)


template<typename T>

class DSVector {

private:
	int size;
	int capacity;
	T* arr;


public:
	DSVector();						// default constructor
	DSVector(int cap);				// parameterized constrcutor

	~DSVector();								// destructor
	DSVector(const DSVector& rhs); 				// copy constructor
	DSVector& operator=(const DSVector& rhs);   // copy assignment operator


	void resize();

	void push_back(T data);            // insert the element at the end 
	//void insert(T data, int idx);	   // insert element at the specified index

	void pop();						   // remove the last element (could be a version of returning the last element)
	//void remove(int idx);			   // remove element at the specified index

	T& operator[](int idx);			   // overloaded [] operator to access element at the specified index
	T* get_arr();
	int get_size();
	int get_capacity();
	bool is_empty();
	void print_pages();




};



// default constructor
template<typename T>
DSVector<T>::DSVector() {

	capacity = 1;
	size = 0;
	arr = new T[1];
}


// parameterized constructor
template<typename T>
DSVector<T>::DSVector(int cap) {

	capacity = cap;
	size = 0;
	arr = new T[capacity];
}


// decstructor
template<typename T>
DSVector<T>::~DSVector() {

	delete[] arr;
}


// copy constructor
template<typename T> 
DSVector<T>::DSVector(const DSVector& rhs) {

	size = rhs.size;
	capacity = rhs.capacity;

	arr = new T[capacity];

	for (int i = 0; i < size; i += 1) {      
		arr[i] = rhs.arr[i];
	}

	//cout << "(DSVector) copy constructor called..." << endl;

}


// copy assigment operator
template<typename T>
DSVector<T>& DSVector<T>::operator=(const DSVector& rhs) {

	// To avoid self-copy
	// "this" is a pointer to the lhs object, so it is compared with the address of the rhs object
	if (this == &rhs) {
		return *this;
	}

	// destructor
	delete[] arr;


	// copy constrcutor
	size = rhs.size;
	capacity = rhs.capacity;

	arr = new T[capacity];

	for (int i = 0; i < size; i += 1) {
		arr[i] = rhs.arr[i];
	}

	//cout << "(DSVector) copy assignment operator called..." << endl;

	// return *this (return the copied object)
	return *this;
}



//===================================================================================================================================
//===================================================================================================================================

template<typename T>
void DSVector<T>::resize() {

	// create a new array on the heap with doubled capacity 
	T* temp = new T[capacity * 2];

	// copy old array's elements over to new array
	for (int i = 0; i < size; i += 1) {
		temp[i] = arr[i];
	}

	// deallocate dynamic memory used by the old array
	delete[] arr;
	// make arr point to the new array
	arr = temp;

	// update the capacity
	capacity *= 2; 
}


template<typename T>
void DSVector<T>::push_back(T data) {	

	if (size == capacity) {
		resize();
	}

	arr[size] = data;    // This will invoke the copy assignment operator
	size += 1;
}


template<typename T>
void DSVector<T>::pop() { 

	if (size > 0) {
		size -= 1;
	}
}


template<typename T>
T& DSVector<T>::operator[](int idx) {

	// index range validation
	if ((idx >= 0) && (idx < size)) {
		return arr[idx];
	}

	else {
		cout << "invalid index..." << endl;
		exit(1);
	}
}


template<typename T>
T* DSVector<T>::get_arr() {
	return arr;
}


template<typename T>
int DSVector<T>::get_size() {
	return size;
}

template<typename T>
int DSVector<T>::get_capacity() {
	return capacity;
}


template<typename T>
bool DSVector<T>::is_empty() {

	if (size == 0) {
		return true;
	}
	else {
		return false;
	}
}


template<typename T>
void DSVector<T>::print_pages() {
	for (int i = 0; i < size; i += 1) {
		// To avoid printing an extra comma in the end
		if (i < size - 1) {
			cout << arr[i] << ", ";
		}
		else {
			cout << arr[i] << endl;
		}
	}
}







#endif






