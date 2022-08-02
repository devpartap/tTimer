#pragma once
#include "iostream"
class timer
{
public: 
    unsigned int hrs = 0;
    unsigned int min = 0;
    unsigned int sec = 0;

    timer();
    ~timer();
    friend std::ostream& operator<<(std::ostream & os,timer & obj);


};