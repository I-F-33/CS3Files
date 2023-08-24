#ifndef ARRAY_FUNCTIONS_H
#define ARRAY_FUNCTIONS_H
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <cassert>
using namespace std;

const int MINIMUM_CAPACITY = 3;

// allocate 'capacity'
//       elements.
//   return array
template <class T> T *allocate(int capacity = MINIMUM_CAPACITY) {
  T *array = new T[capacity]; // Creates new dynamic array with size capacity
  return array;
}

// take array, resize it
//   return new array.
//   delete old array
template <class T>
 T *reallocate(T *a, int size, int capacity) {
  // creating new dynamic array of size
  T *tempArray = new T[capacity];
  // assigning all values of old array into new resized array
  for (int i = 0; i < size; i++) {
    tempArray[i] = a[i];
  }
  // deleting old array
  // pointing old array ptr to new resized array
  return tempArray;
}

// prints
//   (size/capacity)
//   for debugging
template <class T>
void print_array(T *a, int size, int capacity = 0) {
  cout << "Printing Array...." << endl;
  T *walker = a; // walker pointing to address of first index in array a
  for (int i = 0; i < size; i++) {
    cout << setw(8) << "[" << i << "] = " << *walker << endl;
    walker++;
  }
  cout << "Printing array COMPLETE" << endl;
}

template <class T>
void print(T *a, unsigned int how_many, ostream &outs = cout) {
  outs << "Printing Array.....";
  T *walker = a;
  for (int i = 0; i < how_many; i++) {
    outs << "[" << i << "] = [" << *walker << "]" << endl;
    walker++;
  }
  outs << "Print Array COMPLETE";
} // print array

template <class T>
T *search_entry(T *a, int size, const T &find_me) { // search for 'find me'
  T *walker = a; // walker is pointing to the first address in given array

  for (int i = 0; i < size; i++) {
    if (*walker == find_me) { // if the value at walker is equal to he find_me
      return walker;          // return the address of walker
    }
    walker++;
  }
  return nullptr;
}

template <class T>
int search(T *a, int size, const T &find_me) { // search for 'find me'
  T *walker = a; // walker is pointing to the first index of array

  for (int i = 0; i < size; i++) {
    if (*walker == find_me) { // returns the index of where find_me is at
      cout << "found at index [" << i << "]" << endl;
      return i;
    }
    walker++;
  }
  return -1;
}

template <class T>
void shift_left(T *a, int &size, int shift_here) { // shift left @ pos:
 //if given index is negative
assert(shift_here >= 0);
// if index is out of range
assert(shift_here < size);

// flag at end of the array
T* end = a + (size - 1);

// walker for array at given index
T* walker = a + shift_here;

//2nd walker ahead one index, used to shift elements
T* walker_2 = walker + 1;

while(walker != end) {
  //shift elements
  *walker = *walker_2;
  walker++;
  walker_2++;
}

//reduce size of array
size--; 
}

template <class T>
void shift_left(T *a, int &size, T *shift_here) { // shift left @ pos:
  
  int shift_at = shift_here - a;
  shift_left(a, size, shift_at);
}

template <class T> 
void shift_right(T *a, int &size, int shift_here) {
  // edge case
  if (shift_here >= size || size == 0) { // if shifting right at last element
    return;
  }

  size++; // increase size to fit value at former highest index  at new highest
          // index

  T *walker = a + size;            // pointing to address where need to shift
  T *ptr_next_walker = walker + 1; // pointing to address next(right) of walker

  for (int i = size; i >= shift_here; i--) {
    *ptr_next_walker = *walker; // value of new unused address = former value of
                                // last used address

    ptr_next_walker--; // now at former largest size
    walker--;          // now one slot to the left of ptr_next_walker
  }
}

// shift right:
//    make a hole
template <class T>
void shift_right(T *a, int &size, T *shift_here) {
  int shift_at = shift_here - a;

  shift_right(a, size, shift_at);
}

// copy from src to dest
template <class T> void copy_array(T *dest, const T *src, int many_to_copy) {
  T *destination_walker = dest; // pointer for the start of dest array
  const T *source_walker = src; // pointer for the start of source array

  for (int i = 0; i < many_to_copy;
       i++) { // loops for (many_to_copy) amount of times
    *destination_walker =
        *source_walker;   // values of address at destination walker = value of
                          // address at source walker
    destination_walker++; // increment each pointer to continue copying values
    source_walker++;
  }
}

template <class T>
T *copy_array(const T *src, int size) { // return a copy of src
  if (size == 0) {
    return nullptr;
  }
  T *copy_of_src = new T[size]; // copy of source array
  const T *walker_src = src;    // walkers for the copy array and source array
  T *walker_copy = copy_of_src;

  for (int i = 0; i < size; i++) { // copy element from src array to copy array
                                   // for (Size) number of times
    *walker_copy = *walker_src;
    walker_copy++;
    walker_src++;
  }
  return copy_of_src;
}

template <class T>
string array_string(const T *a, int size) { // return array as a string
  if (size == 0) {
    return "";
  }
  // creating a empty string to
  const T *walker = a;
  string output = "";

  char character;

  for (int i = 0; i < size; i++, walker++) {
    // If the array is made up of characters
    if (isalpha(*walker)) {
      // append character to string
      character = *walker;

      output = output + character;
    } else {
      // if the array is made up of ints, doubles , etc..
      output = output  + to_string(*walker);
    }
  }

  return output;
}

#endif
