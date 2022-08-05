#include <chrono>

#include "timer.h"

timer::timer()
    :hrs(0), min(0), sec(0)
{ }
timer::timer(short hr, short mn, short sc)
    :hrs(hr), min(mn), sec(sc)
{
    synctime();
}

timer::~timer(){}

timer timer::operator+(const timer &obj)
{
    return timer(hrs + obj.hrs,min + obj.min,sec + obj.sec);
}

timer timer::operator-(const timer & obj)
{
    short h = 0,m = 0,s = 0;
    if(sec >= obj.sec)
    {
        s = sec - obj.sec;
        if(min >= obj.min) 
        {
            m = min - obj.min;
            h = hrs - obj.hrs;
        }
        else
        {
            m = 60 + min - obj.min;
            h = hrs - obj.hrs - 1;
        }
    }
    else
    {
        if(min >= obj.min) 
        {
            m = min - obj.min - 1;
            s = 60 + sec - obj.sec;
            h = hrs - obj.hrs;
        }
        else
        {
            m = 60 + min - obj.min - 1;
            s = 60 + sec - obj.sec;
            h = hrs - obj.hrs - 1;
        }
    }

    return timer(h,m,s);
}

timer varTime::operator-(varTime& obj)
{
    if(ifcounting) update();
    if(obj.ifcounting) obj.update();
    return timer::operator-(obj);
}

void timer::synctime()
{
    short _min = min + (sec / 60); 
    hrs = hrs + (_min / 60);
    min = _min % 60;
    sec = (sec % 60);
}
std::ostream& operator<<(std::ostream & os,const timer & obj)
{
    (obj.hrs > 9) ? (os << obj.hrs) : (os << 0 << obj.hrs); os << ":";
    (obj.min > 9) ? (os << obj.min) : (os << 0 << obj.min); os << ":";
    (obj.sec > 9) ? (os << obj.sec) : (os << 0 << obj.sec);
    return os;
}


std::ostream& operator<<(std::ostream & os,varTime & obj)
{
    if(obj.ifcounting) obj.update();
    (obj.hrs > 9) ? (os << obj.hrs) : (os << 0 << obj.hrs); os << ":";
    (obj.min > 9) ? (os << obj.min) : (os << 0 << obj.min); os << ":";
    (obj.sec > 9) ? (os << obj.sec) : (os << 0 << obj.sec);
    return os;
    
}

void varTime::count()
{
    ifcounting = true;
    start = std::chrono::system_clock::now();
}
void varTime::stop()
{   
    update();
    ifcounting = false;
}
void varTime::update()
{
    const unsigned int data = (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - start)).count();
    start = std::chrono::system_clock::now();
    sec = (sec + (data % 60));
    unsigned int _min = min + (data /60) + (sec / 60); 
    hrs = hrs + (_min / 60);
    min = _min % 60;
    sec = sec%60;
}

varTime::varTime(const short && h, const short && m, const short && s)
    :timer(h,m,s)
    {}
varTime::varTime()
    :timer() 
    {}
