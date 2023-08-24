#ifndef LIST_SIMPLE_H
#define LIST_SIMPLE_H
#include "../../includes/linked_list_functions/linked_list_functions.h"
#include "../../includes/node/node.h"
#include <iostream>
#include <iomanip>
using namespace std;

template <class ITEM_TYPE>
class List
{
public:
    List()
    {
        head = nullptr;
        _size = 0;
    }

    ~List()
    {
        _clear_list(head);
        _size = 0;
    }

    List(const List<ITEM_TYPE> &copyThis)
    {
        head = _copy_list(copyThis.begin());
        _size = copyThis.size();
    }
    List &operator=(const List &RHS)
    {
        head = _copy_list(RHS.begin());
        _size = RHS._size;

        return *this;
    }

    node<ITEM_TYPE> *insert_head(ITEM_TYPE i) // inset i at the head of list
    {   
        _size++;
        return _insert_head(head, i);
    }
    node<ITEM_TYPE> *insert_after(ITEM_TYPE i, node<ITEM_TYPE> *iMarker) // insert i after iMarker
    {
        _size++;
        return _insert_after(head, iMarker, i);
    }

    node<ITEM_TYPE> *insert_before(ITEM_TYPE i, node<ITEM_TYPE> *iMarker) // insert i before iMarker
    {
         _size++;
        return _insert_before(head, iMarker, i);
    }

    node<ITEM_TYPE> *insert_sorted(ITEM_TYPE i) // insert i. Assume sorted list
    {
         _size++;
        return _insert_sorted(head,i,false);
    }

    ITEM_TYPE Delete(node<ITEM_TYPE> *iMarker) // delete node pointed to by iMarker
    {
        _size--;
        return _delete_node(head, iMarker);
    }

    void Print() const // print the list
    {
        _print_list(head);
    }
    node<ITEM_TYPE> *search(const ITEM_TYPE &key) // return pointer to node containing key. NULL if not there
    {
        return _search_list(head, key);
    }

    node<ITEM_TYPE> *prev(node<ITEM_TYPE> *iMarker) // get the previous node to iMarker
    {
        return _previous_node(head, iMarker);
    }

    ITEM_TYPE &operator[](int index) // return the item at index
    {
        return _at(head, index);
    }
    node<ITEM_TYPE> *begin() const // return the head of the list
    {
        return head;
    }
    node<ITEM_TYPE> *end() const
    {   
        return nullptr;
    }

    bool empty() const { return head == nullptr; }

    int size() const { return _size; }

    template <class U>
    friend ostream &operator<<(ostream &outs, const List<U> &l); // insertion operator for list

private:
    node<ITEM_TYPE> *head;
    int _size;
};

template <class T>
ostream &operator<<(ostream &outs, const List<T> &l) // insertion operator for list
    {
        _print_list(l.begin());
        return outs;
    }

#endif