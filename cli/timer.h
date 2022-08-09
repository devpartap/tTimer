#pragma once

class timer
{
public: 
    short hrs;
    short min;
    short sec;

    timer();
    timer(const short& hr, const short& mn, const short& sc);
    timer(std::string_view data);
    ~timer();

    timer operator+(const timer &obj);
    timer operator+(const std::string_view & data);
    timer operator-(const timer & obj);

    void synctime();
    std::string getinstr();

    friend std::ostream& operator<<(std::ostream & os,const timer & obj);
};

class varTime : public timer
{
    bool ifcounting = true;
    std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
public:
    varTime();
    varTime(const short & h, const short & m, const short & s);

    timer operator-(varTime & obj);
    varTime operator+(const timer &obj);
    bool operator==(const short* data);

    void count();
    void stop();
    void update();

    friend std::ostream& operator<<(std::ostream & os,varTime & obj);
};

std::string printnget(const char * data,const unsigned int & size, timer* times);
std::string timer_tostr(const timer & obj);
