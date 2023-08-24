#ifndef ADD_ENTRY_H
#define ADD_ENTRY_H
#include <cassert>
#include <iostream>
#include <iomanip>
#include "../../includes/array_functions/array_functions.h"
using namespace std;


template <class T>
T* increase_size_if_need(T*a, int &size, int &capacity){
     // if there is only one more space available to fill, let user know there is limited space
    if((size + 1) == capacity) {
        cout << "Size has almost reached max capacity, there is one index left" << endl;
    }
     if(size == capacity) {
        cout << "Array has reached its max size, increasing size to " << capacity * 2 << endl;
        T* new_list = reallocate(a,size,capacity * 2);
        capacity += capacity;
        cout << capacity << endl;
        return new_list;
    }
    return a;
}

template <class T>
T* reduce_size_if_need(T* a, int &size, int &capacity){

    // Reallocate array to 1/2 of used space if only 1/4th of capacity is being used
    if(size <= (.25 * capacity)) {
        cout << "Only one fourth or less is being used in array, resizing by 1/2" << endl;
        cout << "Capacity is now " << capacity/2 << endl;
        T* new_list = reallocate(a, size, capacity/2);
        capacity -= capacity/2;
        return new_list;
    }

    return a;
}

template<class T>
T* add_entry(T* list, const T& new_entry, int& size, int& capacity) {

    // check if there is any memory to allocate the new values
    assert(capacity > 0);

    //check if there is enough meemory to input the new entry
    list = increase_size_if_need(list,size,capacity);

    // address where new entry will be added
    T* insert_index = list + size;

    // address now holds new_entry value
    *insert_index = new_entry;

    //increase size
    size++;

    // check if capcity needs to be increased or if its almost full then return apporpriate array
    return list;
}


template<class T>
T* remove_entry(T* list, const T& delete_me, int& size, int& capacity) {

    // reduce the size of the array if it is 1/4 of size
    list = reduce_size_if_need(list,size,capacity);

    // fetch index of element that needs to be removed
    T* index_to_remove = search_entry(list,size,delete_me);

    // shift left and replace the "delete_me" element with the element next (right)
    shift_left(list,size,index_to_remove);

    // Reallocate array to 1/2 of used space if only 1/4th of capacity is being used
    // if not then return the array
    return list;

}



template <class T>
T *remove_last_entry(T *list, T &popped, int &size, int &capacity) {

    list = reduce_size_if_need(list,size,capacity);
    // Index of element to be removed
    T* remove_index = list + (size - 1);

    //popped is assigned the value of the index that is be to removed
    popped = *remove_index;

    // replace last entry with garbage
    shift_left(list,size,remove_index);

    //reallocate array to 1/2 of used space if only 1/4th of capacity is being used
    // if not then return the array
    return list;
}




template <class T>
T *insert_entry(T *list, const T &insert_this, int insert_here, int &size, int &capacity) {

    list = increase_size_if_need(list,size,capacity);
    //pointer pointing to the address of where to insert the new element
    T* entry_point = list + insert_here;

    //shift right at the entry point to create a space for new element
    shift_right(list,size,entry_point);

    // duplicate is now set to the value of the desired new element
    *entry_point = insert_this;

    //deleting pointer
    delete entry_point;

    // check if capacity needs to be increases, if then increase to capacity * 2 then return
    // check if array is almost full, if it is then notify user
    // else none then return array
    return list;
}

template <class T>
T *erase_entry(T *list, int index, int &size, int &capacity) {
    
    assert(capacity > 0); //assert that capacity is greater than zero

    assert(size > 0); //assert that there are elements in the array

    //reduce the size if only 1/4 of space or less than is used
    list = reduce_size_if_need(list, size, capacity);

    //Pointer pointing to the address that needs to be removed
    T* erase_here = list + index;

    // Shift left and remove the value at the given index
    shift_left(list,size,erase_here);

    // if used memory is less than 1/4 of array then reduce size else return the array
    return list;
}

#endif
