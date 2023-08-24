#ifndef VECTOR_CLASS_H
#define VECTOR_CLASS_H
#include "../../includes/add_entry/add_entry.h"
#include "../../includes/array_functions/array_functions.h"
#include <iomanip>
#include <iostream>
#include <assert.h>
using namespace std;

template <class T> class Vector {
public:
  Vector(int size = 100);
  Vector(T *arr, int size);
  // big three:
  Vector(const Vector &other);

  // return reference to item at position index
  T &at(int index);

  // return a const item at position index
  const T &at(int index) const;

  // return item at position 0.
  T &front();

  // return item at the last position
  T &back();

  // append to the end
  void push_back(const T &item);

  // remove last item and return it
  T pop_back();

  // Insert and Erase:
  // insert at pos
  void insert(int insert_here, const T &insert_this);

  // erase item at position
  void erase(int erase_this_index);

  // search for item. retur index.
  int index_of(const T &item);

  // size and capacity:
  // enlarge the vector to this size
  void set_size(int size);

  // allocate this space
  void set_capacity(int capacity);

  // return _size
  int size() const;

  // return _capacity
  int capacity() const;

  // return true if vector is empty
  bool empty() const;

  // OUTPUT:
  template <class U>
  friend ostream &operator<<(ostream &outs, const Vector<U> &_a);

  Vector &operator=(const Vector &rhs) {
    if (this == &rhs) {
      return *this;
    }

    delete[] array;

    array = new T [rhs._capacity];

    copy_array(array, rhs.array, rhs._how_many);

    _how_many = rhs._how_many;

    _capacity = rhs._capacity;

    return *this;
  }

  ~Vector();

  // member access functions:
  T &operator[](int index) {

    //pointer to the index of the array
    T* walker = array + index;
    
    //return the dereferenced index
    return *walker;
  }
  const T &operator[](int index) const {

    //pointer to the index of the array
    T* walker = array + index;
    
    //return the dereferenced index
    return *walker;
  }

  // Push and Pop functions:
  // push_back
  Vector &operator+=(const T &item) {

    //PUSH BACK THE ITEM INTO THE ARRAY
    push_back(item);

    return *this;
    
  }

private:

  int _how_many;

  int _capacity;

  T *array;
};

template <class T> 
Vector<T>::Vector(int size) {
  //make sure the size of the array is greater than 0
  assert(size > 0);

  //create array and set size and capacity
  array = allocate<T>(size);
  _capacity = size;
  _how_many = 0;
}

template <class T> 
Vector<T>::Vector(T *arr, int size) {
  //assigning vector variables
  _how_many = 0;
  _capacity = 3;

  //creating vector array
  array = allocate<T>(_capacity);

  //pushing back each element of the array
  for (int i = 0; i < size; i++) {
    push_back(arr[i]);
  }

}

template <class T> 
Vector<T>::Vector(const Vector &other) {
  if (this == &other) {
    return ;
  }
  array = allocate<T>(other._capacity);
  copy_array(array, other.array, other._how_many);
  _capacity = other._capacity;
  _how_many = other._how_many;
}

template <class T> 
Vector<T>::~Vector() {
  delete[] array; 
}

// return reference to item at position index
template <class T> 
T &Vector<T>::at(int index) {

  assert(index >= 0 && index < _how_many);

  T* walker = array + index;

  return *walker;
}

// return a const item at position index
template <class T> 
const T &Vector<T>::at(int index) const {
  assert(index >= 0 && index < _how_many);
  return array[index];
}

// return item at position 0.
template <class T> 
T &Vector<T>::front() {

  assert(_how_many > 0);

  return array[0];
}

// return item at the last position
template <class T> 
T &Vector<T>::back() {

  assert(_how_many > 0);

  return array[_how_many - 1];
}

// append to the end
template <class T> 
void Vector<T>::push_back(const T &item) {

  array = add_entry<T>(array,item, _how_many, _capacity);

}

// remove last item and return it
template <class T> 
T Vector<T>::pop_back() {

  //assert that the vector is not empty
  assert(_how_many > 0);

  //create a temp variable to hold the last item
  T popped;

  //remove the last item & assign last item to popped
  array = remove_last_entry<T>(array, popped, _how_many, _capacity);

  //return the last item
  return popped;
}

// Insert and Erase:
// insert at pos
template <class T>
void Vector<T>::insert(int insert_here, const T &insert_this) {

  array = insert_entry<T>(array, insert_this, insert_here, _how_many, _capacity);
}

// erase item at position
template <class T> 
void Vector<T>::erase(int erase_this_index) {

  array = erase_entry<T>(array, erase_this_index, _how_many, _capacity);
}

// search for item. retur index.
template <class T> 
int Vector<T>::index_of(const T &item) {
  return search(array,_how_many, item);
}

// size and capacity:
// enlarge the vector to this size
template <class T> 
void Vector<T>::set_size(int size) {
  _how_many = size;
}

// allocate this space
template <class T> 
void Vector<T>::set_capacity(int capacity) {
  _capacity = capacity;
}

// return _size
template <class T> 
int Vector<T>::size() const { return _how_many; }

// return _capacity
template <class T> 
int Vector<T>::capacity() const { return _capacity; }

// return true if vector is empty
template <class T>
bool Vector<T>::empty() const {
  return _how_many == 0;
}

template <class U> 
ostream &operator<<(ostream &outs, const Vector<U> &_a) {

  U* walker = _a.array;
  for (int i = 0; i < _a._how_many; i++, walker++) {
    outs << *walker << " ";
  }

  return outs;
}

#endif