#pragma once
#include <iostream>
#include <chrono>
class timer
{
public:
    short hrs;
    short min;
    short sec;
    bool count;

public: 
    timer();
    timer(short hr, short mn, short sc);
    ~timer();

    timer operator+(timer & obj);

    friend std::ostream& operator<<(std::ostream & os,timer & obj);
};

class varTime : public timer
{
   std::chrono::_V2::system_clock::time_point start;
public:


    void addsec(const unsigned int && toadd);
    void stcount();

    friend std::ostream& operator<<(std::ostream & os,varTime & obj);
};