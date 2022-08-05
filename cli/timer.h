#pragma once


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

    timer operator+(const timer &obj);
    timer operator-(const timer & obj);

    void synctime();

    friend std::ostream& operator<<(std::ostream & os,const timer & obj);
};

class varTime : public timer
{
    bool ifcounting = true;
    std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
public:
    varTime();
    varTime(const short && h, const short && m, const short && s);

    timer operator-(varTime & obj);

    friend std::ostream& operator<<(std::ostream & os,varTime & obj);

    void count();
    void stop();
    void update();
};