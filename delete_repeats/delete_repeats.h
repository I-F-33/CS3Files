#ifndef DELETE_REPEATS_H
#define DELETE_REPEATS_H
#include <iomanip>
#include <iostream>
#include <cassert>
#include "../../includes/array_functions/array_functions.h"
using namespace std;

template <class T>
void delete_repeats(T* array, int &size){

    // if size is not greater than zero then return
    assert(size > 0);

    //Flag to end loop at end of the array
    T* end = array + (size - 1) ;

    // walker starting at first index to seek out duplicates
    T* walker = array;

    while(walker <= end) {

        // find the first index of the value searched for
       T* found_at = search_entry(array,size,*walker);

       //if the current walker address is not == to the returned address of the index searched for
        if(walker != found_at) {
        //shift left and remove the duplicate found_at
        shift_left(array,size,found_at);

        //shift the end flag to the left if an element is deleted
        end--;
        } else{
        //move walker to the next index if current index is unique
        walker++;
        }
    }
    
}
#endif