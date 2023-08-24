#include "plane.h"
#include "../../includes/two_d_functions/two_d_functions.h"
#include "../../includes/array_functions/array_functions.h"
#include <iostream>
#include <iomanip>
using namespace std;

//creates the 7*4 sizes array
int* create_size() {
    int* sizes = allocate<int>(8);

    int* size_walker = sizes;

    // filling size array with 7 fours and one -1 at end
    for(int i = 0; i < 8; i++, size_walker++) {
        if(i == 7) {
            *size_walker = -1;
        } else {
        *size_walker = 4;
        }
    }

    return sizes;
}

bool **init_plane() {

    int* sizes = create_size();

    bool** plane = allocate_twod<bool>(sizes);

    //plane will be initiated to all false values
    init_twod(plane, sizes, false);

    return plane;
}

bool reserve(bool **plane, int row, int seat) {
    if(read_twod(plane,row,seat) == false) {
        write_twod(plane,row,seat,true);
        return true;
    }
    return false;
}
bool cancel(bool** plane, int row, int seat) {
    if(read_twod(plane,row,seat) == true) {
        write_twod(plane,row,seat,false);
        return true;
    }
    return false;
}
void print_plane(bool **plane) {

    int* sizes = create_size();

    int size = array_size(sizes);

   // print_twod(plane,sizes);

   for(int i = 0; i < size; i++) {

    for(int j = 0; j < *sizes; j++) {
        if(read_twod(plane,i,j) == true) {
            switch(j) {
                case 0 : cout << "A ";
                        break;
                case 1 : cout << "B ";
                        break;
                case 2 : cout << "C ";
                        break;
                case 3 : cout << "D ";
                        break;
                default: cout << "X ";
                        break;
            }
        } else {
            cout << "X ";
        }
    }
    cout << endl;
   }

}