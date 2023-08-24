#include "two_d_functions.h"
#include "../../includes/array_functions/array_functions.h"
#include <iostream>
#include <iomanip>
using namespace std;

//This function returns the number of sizes in the size array
int array_size(int* sizes) {
    //counter
    int size = 0;
    //while the calue in sizes is not -1 the counter will incement one
    while (*sizes != -1) {
        size++;
        sizes++;
    }

    //return the counter 
    return size;
}

void print_array(int* a) {

    //walker for passed in array
    int* walker = a;

    //While the value at walker is not a -1 then print the value
    while (*walker != -1) {
        cout << *walker << " ";
        walker++;
    }
}

bool index_is_valid(int* sizes, int row, int col) {
    
    //number of rows
    int size = array_size(sizes);

    //if index exists then return true
    for(int i = 0; i < size; i++, sizes++) {
        //if row is equal to i and column is equal to j return true
        for(int j = 0; j < *sizes; j++) {
            if(i == row && col == j){
                return true;
            }
        }
    }

    //if index doesnt match then return false
    return false;
}

