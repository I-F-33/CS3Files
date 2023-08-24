#ifndef LIST_SORTED_H
#define LIST_SORTED_H
#include "../../includes/linked_list_functions/linked_list_functions.h"
#include <iostream>
using namespace std;

template <class T>
class List
{
public:
    class Iterator
    {
    public:
        friend class List; // give access to list to
                           //           access _ptr

        Iterator() { _ptr = NULL; } // default ctor

        Iterator(node<T> *p) // Point Iterator to where p is pointing to
        {
            _ptr = p;
        }

        T &operator*() // dereference operator
        {
            return _ptr->_item;
        }

        T *operator->() // member access operator
        {
            return &_ptr->_item;
        }
        bool is_null() // true if _ptr is NULL
        {
            return _ptr == nullptr;
        }
        friend bool operator!=(const Iterator &left, const Iterator &right) // true if left != right
        {
            return left._ptr != right._ptr;
        }
        friend bool operator==(const Iterator &left, const Iterator &right) // true if left == right
        {
            return left._ptr == right._ptr;
        }
        Iterator &operator++() // member operator:  ++it; or  ++it = new_value
        {

            _ptr = _ptr->_next;
            return *this;
        }

        friend Iterator operator++(Iterator &it, int unused) // friend operator: it++
        {
            ++it;
            return it;
        }

    private:
        node<T> *_ptr; // pointer being encapsulated
    };

    List(bool order = true, bool unique = false) // CTOR: default args
    {
        _head_ptr = nullptr;
        _order = order;
        _unique = unique;
        _size = 0;
    }
    // BIG 3:
    ~List()
    {
        _clear_list(_head_ptr);
        _size = 0;
        _order = false;
        _unique = true;
    }

    List(const List<T> &copyThis)
    {
        _head_ptr = _copy_list(copyThis._head_ptr, _head_ptr);
        _size = copyThis._size;
        _order = copyThis._order;
        _unique = copyThis._unique;
    }
    List &operator=(const List &RHS)
    {
        _clear_list(_head_ptr);

        _head_ptr = _copy_list(RHS._head_ptr);
        _order = RHS._order;
        _unique = RHS._unique;
        _size = RHS._size;

        return *this;
    }

    Iterator insert(const T &i) // Insert i
    {
        _size++;
        return _insert_sorted(_head_ptr, i, _order);
    }

    Iterator insert_and_add(const T &i) // Insert i
    {
        _size++;
        return _insert_sorted_and_add(_head_ptr, i, _unique);
    }

    T Delete(List<T>::Iterator iMarker) // delete node at marker
    {
        _size--;
        return _delete_node(_head_ptr, iMarker._ptr);
    }

    void Print() const
    {
        _print_list(_head_ptr);
    }

    Iterator search(const T &key) const // return Iterator to node [key]
    {
        return _search_list(_head_ptr, key);
    }

    Iterator prev(Iterator iMarker) // previous node: marker
    {
        return _previous_node(_head_ptr, iMarker._ptr);
    }

    const T &operator[](int index) const // const version of the operator [ ]
    {
        return _at(_head_ptr, index);
    }

    T &operator[](int index) // return item at index
    {
        return _at(_head_ptr, index);
    }
    Iterator begin() const // Iterator to head node
    {
        return _head_ptr;
    }
    Iterator end() const // Iterator to NULL
    {
        return nullptr;
    }
    Iterator last_node() const // Iterator to last node
    {
        return _last_node(_head_ptr);
    }
    bool empty() const { return _head_ptr == nullptr; }
    template <class U> // Note template arg U
    friend ostream &operator<<(ostream &outs, const List<U> &l);
    int size() const { return _size; }

private:
    node<T> *_head_ptr;
    bool _order;
    bool _unique;
    int _size;
};
template <class U>
ostream &operator<<(ostream &outs, const List<U> &l) // insertion operator for list
{
    _print_list(l._head_ptr);
    return outs;
}
#endif // LIST_SORTED_H