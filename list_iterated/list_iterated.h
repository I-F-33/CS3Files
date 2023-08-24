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
    class Iterator
    {
    public:
        friend class List; // give access to list to access _ptr

        Iterator() // default ctor
        {
            _ptr = nullptr;
        }

        Iterator(node<ITEM_TYPE> *p) // Point Iterator to where p is pointing to
        {
            _ptr = p;
        }
        operator bool(); // casting operator: true if _ptr not NULL
                         //       this turned out to be a pain!

        ITEM_TYPE &operator*() // dereference operator
        {
            return _ptr->_item;
        }

        ITEM_TYPE *operator->() // member access operator
        {
            return *_ptr->_item;
        }

        bool is_null() // true if _ptr is NULL
        {
            return _ptr == nullptr;
        }
        Iterator &operator++() // member operator: ++it; or ++it = new_value
        {
            _ptr = _ptr->_next;
            return *this;
        }

        friend Iterator operator++(Iterator &it, int unused) // friend operator: it++
        {

            ++it;
            return it;
        }

        friend bool operator!=(const Iterator &left, const Iterator &right) // true if left != right
        {
            return left._ptr != right._ptr;
        }

        friend bool operator==(const Iterator &left, const Iterator &right) // true if left == right
        {
             return left._ptr == right._ptr;
        }

    private:
        node<ITEM_TYPE> *_ptr; // pointer being encapsulated
    };

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
        head = _copy_list(copyThis.head);
        _size = copyThis._size;
    }
    List &operator=(const List &RHS)
    {
        head = _copy_list(RHS.head);
        _size = RHS._size;

        return *this;
    }

    node<ITEM_TYPE> *simple_insert_head(ITEM_TYPE i) // inset i at the head of list
    {
        _size++;
        return _insert_head(head, i);
    }
    node<ITEM_TYPE> *simple_insert_after(ITEM_TYPE i, node<ITEM_TYPE> *iMarker) // insert i after iMarker
    {
        _size++;
        return _insert_after(head, iMarker, i);
    }

    node<ITEM_TYPE> *simple_insert_before(ITEM_TYPE i, node<ITEM_TYPE> *iMarker) // insert i before iMarker
    {
        _size++;
        return _insert_before(head, iMarker, i);
    }

    node<ITEM_TYPE> *simple_insert_sorted(ITEM_TYPE i) // insert i. Assume sorted list
    {
        _size++;
        return _insert_sorted(head, i, false);
    }

    ITEM_TYPE simple_Delete(node<ITEM_TYPE> *iMarker) // delete node pointed to by iMarker
    {
        _size--;
        return _delete_node(head, iMarker);
    }

    void simple_Print() const // print the list
    {
        _print_list(head);
    }
    node<ITEM_TYPE> *simple_search(const ITEM_TYPE &key) // return pointer to node containing key. NULL if not there
    {
        return _search_list(head, key);
    }

    node<ITEM_TYPE> *simple_prev(node<ITEM_TYPE> *iMarker) // get the previous node to iMarker
    {
        return _previous_node(head, iMarker);
    }

    ITEM_TYPE &operator[](int index) // return the item at index
    {
        return _at(head, index);
    }
    node<ITEM_TYPE> *simple_begin() const // return the head of the list
    {
        return head;
    }
    node<ITEM_TYPE> *simple_end() const
    {
        return nullptr;
    }

    bool empty() const { return head == nullptr; }

    int size() const { return _size; }

    template <class U>
    friend ostream &operator<<(ostream &outs, const List<U> &l); // insertion operator for list

    Iterator begin() const // Iterator to the head node
    {
        return simple_begin();
    }
    Iterator end() const // Iterator to NULL
    {
        return simple_end();
    }
    Iterator last_node() const // Iterator to the last node
    {
        return _last_node(head);
    }
    Iterator search(const ITEM_TYPE &key) // return Iterator to node [key]
    {
        return simple_search(key);
    }

    Iterator prev(Iterator iMarker) // previous node to marker
    {
        return simple_prev(iMarker._ptr);
    }
    Iterator insert_head(ITEM_TYPE i) // insert at the head of list
    {
        return simple_insert_head(i);
    }
    Iterator insert_after(ITEM_TYPE i, Iterator iMarker) // insert after marker
    {
        return simple_insert_after(i, iMarker._ptr);
    }
    Iterator insert_before(ITEM_TYPE i, Iterator iMarker) // insert before marker
    {
        return simple_insert_before(i, iMarker._ptr);
    }
    Iterator insert_sorted(ITEM_TYPE i) // insert in a sorted list
    {
        return simple_insert_sorted(i);
    }
    ITEM_TYPE Delete(List<ITEM_TYPE>::Iterator iMarker) // delete node pointed to by marker
    {
        return simple_Delete(iMarker._ptr);
    }

private:
    node<ITEM_TYPE> *head;
    int _size;
};

template <class U>
ostream &operator<<(ostream &outs, const List<U> &l) // insertion operator for list
{
    _print_list(l.simple_begin());
    return outs;
}

#endif