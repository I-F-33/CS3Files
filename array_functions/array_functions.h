#ifndef ARRAY_FUNCTIONS_H
#define ARRAY_FUNCTIONS_H

#include <cmath>
#include <iostream>
#include <iomanip>
#include <set>
#include <vector>
#include <cassert>
using namespace std;


const int MINIMUM_CAPACITY = 3;

template<class T>      //copy from src to dest
void copy_array(T* dest, const T* src, int many_to_copy)
{
    const T* walker_old = src;
    T* walker_new = dest;

    for (int i = 0; i < many_to_copy; i++)
    {
        *walker_new = *walker_old;
        walker_new++;
        walker_old++;
    }
}

template <class T>                  //copies an array from another one, returns the array copy, placed atop to be used by other functions
T* copy_array(const T* src, int size)
{
    T* array_copy = new T[size];
    copy_array<T>(array_copy, src, size);
    return array_copy;

}
template<class T>   //allocates a dynamic array
T* allocate(int capacity = MINIMUM_CAPACITY)
{
    bool debug = false;
    if (debug) cout << "Allocate: Capacity " << capacity << endl;
    return new T[capacity];
}         

template<class T>        //reallocates a dynamic array, preserves the contents
T* reallocate(T* a, int size, int capacity)
{

    T* new_array = allocate<T>(capacity);
    copy_array<T>(new_array, a, size);
    delete[] a;
    return new_array;
}



template <class T>  //prints debug information to terminal
void print(T* a, unsigned int how_many, ostream& outs = cout)
{

        cout << "[";

        for (int i = 0; i < how_many; i++)
        {
            cout << *a << " ";
            a++;
        }

        cout << "]" << endl;
}

template<class T>  //prints an array to terminal
void print_array(T* a, int size, int capacity = 0, ostream& outs = cout)
{
        cout << "( " << size << "/" << capacity << ")";

        print(a, size, outs);
}

template<class T>      //returns the address/pointer of the found element
T* search_entry(T* a, int size, const T& find_me)
{
        T* walker = a;
        for (int i = 0; i < size; i++)
        {
            if (*walker == find_me)
            {
                return walker;
            }
            walker++;
        }
        return nullptr;
}

template <class T>             //returns the index of the found element
int search(T* a, int size, const T& find_me)
    {
        T* index_pointer = search_entry<T>(a, size, find_me);
        if (index_pointer == 0) return -1;
        int index_value = index_pointer - a;
        return index_value;
    }

template <class T>       //shifts an array 'to the right' makes a duplicate at the shift-point. Shifts at a POINTER
void shift_right(T *a, int &size, T* shift_here)
{
    if (size <= 0) return; // expels invalid indicies

     size++; // increase size

        T* stop_condition = shift_here;

        T* current_cell = a + size - 1; // might not work, try cout

        T* next_cell = current_cell - 1;

        while (current_cell != stop_condition)
        {
            *current_cell = *next_cell;
            current_cell--;
            next_cell--;
        }

        return;
}


template <class T>      //shifts an array 'to the right' makes a duplicate at the shift-point. Shifts at an INDEX
void shift_right(T *a, int &size, int shift_here)
{
    if (size <= 0) return; // expels invalid indicies

     size++; // increase size

        //stop condition is the index of the shift point
        T* stop_condition = a + shift_here;

        //current cell is the last cell in the array
        T* current_cell = a + size - 1;

        //next cell is the cell before the current cell
        T* next_cell = current_cell - 1;

        //while the current cell is not the stop condition
        while (current_cell != stop_condition)
        {
            //copy the value of the next cell to the current cell
            *current_cell = *next_cell;
            current_cell--;
            next_cell--;
        }

        return;
}


template <class T>        //shift left @ pos: errases posistion and lowers size SHIFTS AT POINTER
void shift_left(T* a, int& size, T* shift_here)
{
    T* current_cell = shift_here;
    T* next_cell = current_cell + 1;

    T* end_of_array = a + size - 1;


    while (current_cell != end_of_array)
    {
            *current_cell = *next_cell;
            current_cell++;
            next_cell++;
    }

        size--; // increase size

    return;

}

template <class T>       //shift left @ pos: errases posistion and lowers size SHIFTS AT AN INDEX
void shift_left(T* a, int& size, int shift_here)
{
    T* current_cell = a + shift_here;
    T* next_cell = current_cell + 1;

    T* end_of_array = a + size - 1;

    while (current_cell != end_of_array)
    {
            *current_cell = *next_cell;
            current_cell++;
            next_cell++;
    }
        size--; // increase size
    return;

}

template <class T>              //current implementation is shit, does not adequately differentiate "int" and "char" -- currently outputs ASCII values :()
string array_string(const T *a, int size)
{

    const T* walker = a;
    string return_me = "[";
    char char_value;

    for (int i = 0; i < size; i++)
    {
        if (isalpha(*walker))
        {
            char_value = *walker;
            return_me += char_value;
        }
        else
        {
            return_me += " " + to_string(*walker);
        }
        walker++;
    }

    return return_me;

}
#endif
