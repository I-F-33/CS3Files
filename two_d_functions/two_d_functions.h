#ifndef TWO_D_FUNCTIONS_H
#define TWO_D_FUNCTIONS_H
#include "../../includes/array_functions/array_functions.h"
#include <iostream>
#include <iomanip>
using namespace std;

int array_size(int* sizes);
void print_array(int* a);
bool index_is_valid(int* sizes, int row, int col);
//To call: int** p = allocate_twod<int>(sizes_array)  

template <class T>
T** allocate_twod(int* sizes) {
    //number of sizes in sizes_array
    int size = array_size(sizes);

    //intitializing the 2d array with the size of rows  = size of sizes array
    T** two_d_array = new T*[size];

    // Walker for 2D array
    T** two_d_walker = two_d_array;

    //walker for sizes array needed to get the values from sizes
    int* size_walker = sizes;

    //adding an array of with sizes from the size array
    for(int i = 0; i < size; i++, two_d_walker++, size_walker++) {

        //each T pointer is given an array with a different size
        *two_d_walker = new T[*size_walker];
    }

    return two_d_array;
}

template <class T>
T** deallocate_twod(T** twod, int size) {

    //deleting every pointer in the pointer array
    for(int i = 0; i < size; i++) {
        twod[i];
    }

    //deleting main 2d array
    delete[] twod;

    return nullptr;
}

template <class T>
T read_twod(T** twod, int row, int col) {

    //walker for twod initilaized at position row
    T** twod_walker = twod + row;

    //walker for columns in twod array initialized at int column
    T* value_to_return = *twod_walker + col;

    //dereferenced pointer value at twod[row][col]

    return *value_to_return;
}

template <class T>
void write_twod(T** twod, int row, int col, const T& item) {
    
    //Pointer for referenced two d array + row 
    //pointing to the row wanted
    T** row_pointer = twod + row;

    //pointer pointing to the wanted column at the wanted row
    T* value_wanted = *row_pointer + col;

    //the index at [row][column] is now equal to item
    *value_wanted = item;

    return;
}

template <class T>
T& get_twod(T** twod, int row, int col) {

    //ptr pointing to the row wanted
    T** twod_pointer = twod + row;

    //ptr pointing to row and column (index) wanted
    T* wanted_value = *twod_pointer + col;

    //returning address wanted
    return *wanted_value;
}

template<class T>
void init_twod(T** twod, int* sizes, T init_item = T()) {

    //number of columns in 2d array
    int columns = array_size(sizes);

    //walker for sizes (needed to get sizes of columns)
    int* size_walker = sizes;

    //Every iteration of first loop shifts the twod_walker and size_walker 
    //size walker is used to restrict the second loop 
    for(int i = 0; i < columns; i++, size_walker++){

        //loop is restricted by the value at size_walker
        //the value at column_walker is equal to the init_item
        for(int j = 0; j < *size_walker; j++) {
            
            write_twod(twod,i,j,init_item);
        }
    }
}

template<class T>
bool search_twod(T** twod, int* sizes, const T& key, int& row, int& col) {

    // number of rows
    int size = array_size(sizes);

    for(int i = 0; i < size; i++, sizes++) {

        for(int j = 0; j < *sizes; j++) {
            if(read_twod(twod,i,j) == key) { //if the key is found at current index location then        
                row = i;                // row is equal to the row where found
                col = j;                // col is equal to column where found
                return true;
            }
        }
    }

    //if key is not found then return false
    return false;
}

//return a pointer to the item if found, nullptr if not found: 
//                                                 (Ms. Barskhian)
template<class T> 
T* search_twod(T** twod, int* sizes, const T& key) {

    //number of rows in the 2d array
    int size = array_size(sizes);

    //walker for sizes
    int* sizes_walker = sizes;

    for(int i = 0; i < size; i++, sizes++) {

        for(int j = 0; j < *sizes; j++) {

            if(read_twod(twod,i,j) == key) {
                T** twod_row = twod + i;
                T* value_wanted = *twod_row + j;
                return value_wanted;
            }
        }
    }
    return nullptr;
}

template <class T>
void print_twod(T** twod, int* sizes) {

    //The amount of columsn to iterate
    int size = array_size(sizes);

    //loop and print through the entire array row * row
    for(int i = 0; i < size; i++, sizes++) {

        for(int j = 0; j < *sizes; j++) {
            cout << "[" << read_twod(twod,i,j) << "]  " ;
        }
        cout << endl;
    }
}

#endif