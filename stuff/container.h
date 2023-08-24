#ifndef CONTAINER_H
#define CONTAINER_H
#include <vector>
#include <iostream>


//WARNING: No Big 3 Funcions. DO I NEED ONE?
using namespace std;
template <typename T>
class Container
{
public:
    Container();
    void Add(T cargo);
    T& operator[](int i);
    int Length();
private:
    vector <T> container;
};

#endif // CONTAINER_H













template <typename T>
Container<T>::Container()
{
}
template <typename T>
void Container<T>::Add(T cargo){
    container.push_back(cargo);
}

template <typename T>
T& Container<T>::operator[](int i){
    return container[i];
}

template <typename T>
int Container<T>::Length(){
    return container.size();
}
