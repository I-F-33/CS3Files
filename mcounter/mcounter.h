#ifndef MCOUNTER_H
#define MCOUNTER_H

class MCounter
{
public:
    MCounter();
    MCounter(int n);
    int add_1();                //increment functions
    int add_10();
    int add_100();
    int add_1000();
    int reset();                //reset error  state, _count
    int count() const;          //returns _count
    bool error() const;         //returns _error
    bool is_error() const;      //true  if an error has occurred

private:
    int add(int n);             //add n to _count
    int _count;
    bool _error;
};


#endif