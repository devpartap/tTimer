#include "timer.h"

timer::timer()
    :hrs(0), min(0), sec(0)
{ }
timer::timer(short hr, short mn, short sc)
    :hrs(hr), min(mn), sec(sc)
{ }
timer::~timer(){}

timer timer::operator+(timer & obj)
{
    return timer(hrs + obj.hrs,min + obj.min,sec + obj.sec);
}

std::ostream& operator<<(std::ostream & os,timer & obj)
{
    os << obj.hrs << ":" << obj.min << ":" << obj.sec;
    return os;
}

std::ostream& operator<<(std::ostream & os,varTime & obj)
{
    const unsigned int data = (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - obj.start)).count();
    unsigned int _min = obj.min + (data / 60);    

    os << obj.hrs + (_min / 60) << ":" << _min % 60 << ":" << obj.sec + (data % 60);
    return os;
}

varTime::varTime(const short && h, const short && m, const short && s)
    :timer(h,m,s)
    {}
