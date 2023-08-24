#include "mcounter.h"
#include <iostream>
#include <iomanip>
using namespace std;

MCounter::MCounter()
{
    _count = 0;
    _error = false;
}

MCounter::MCounter(int n)
{
    _count = add(n);
    _error = false;
}

int MCounter::add(int n)
{
    _count += n;
    _error = is_error();
    if (_error)
    {
        return 0;
    }
    else
    {
        return n;
    }
}

int MCounter::add_1()
{ // increment functions
    return add(1);
}

int MCounter::add_10()
{
    return add(10);
}

int MCounter::add_100()
{
    return add(100);
}

int MCounter::add_1000()
{
    return add(1000);
}
int MCounter::reset()
{ // reset error  state, _count
    _count = 0;
    _error = false;
    return _count;
}
int MCounter::count() const
{ // returns _count
    return _count;
}
bool MCounter::error() const
{ // returns _error
    return _error;
}
bool MCounter::is_error() const
{ // true  if an error has occurred
    if (_count > 9999)
    {
        return true;
    }
    return false;
}