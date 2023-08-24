#include "lab.h"
#include "../../includes/two_d_functions/two_d_functions.h"
#include <iostream>
#include <iomanip>
using namespace std;

int **init_lab(int* stations) {
    
    // allocating and creating array
    int** lab = allocate_twod<int>(stations);

    //2d array will be filled with zeros
    init_twod(lab, stations, 0);

    return lab;

}

bool login(int** labs, int lab, int station, int id) {
    //if the lab and station is empty then write the user id to that lab and station
    if(read_twod(labs,lab,station) == 0) {
        write_twod(labs,lab,station,id);
        //return true if user logged
        return true;
    }
    //return  false if the lab and station was already taken
    return false;
}

bool logout(int** labs, int* sizes, int id) {

    //search_twod will search and return true if the user is logged in
    // lab and station will be set to the index of that user's id
    int lab = 0;
    int station = 0;

    if(search_twod(labs,sizes,id,lab,station) == false) {
        return false;
    }

    while(search_twod(labs,sizes,id,lab,station)) {
        //log user out at all stations and replace id with zero
        write_twod(labs,lab,station,0);
    }
    return true;
}