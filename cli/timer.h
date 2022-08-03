#pragma once
#include <iostream>
#include <chrono>
class timer
{
public:
    short hrs;
    short min;
    short sec;

public: 
    timer();
    timer(short hr, short mn, short sc);
    ~timer();

    timer operator+(timer & obj);

    friend std::ostream& operator<<(std::ostream & os,timer & obj);
};

class varTime : public timer
{
   std::chrono::_V2::system_clock::time_point start = std::chrono::system_clock::now();
public:
    varTime(const short && h, const short && m, const short && s);
    friend std::ostream& operator<<(std::ostream & os,varTime & obj);
};