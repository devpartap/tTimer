#include "timer.h"

timer::timer()
    :hrs(0), min(0), sec(0), count(nullptr)
{ }
timer::timer(short hr, short mn, short sc)
    :hrs(hr), min(mn), sec(sc), count(nullptr)
{ }
timer::~timer(){}

std::ostream& operator<<(std::ostream & os,timer & obj)
{
    os << obj.hrs << ":" << obj.min << ":" << obj.sec;
    return os;
}

std::ostream& operator<<(std::ostream & os,varTime & obj)
{
    if(obj.count)
    {
        obj.addsec((std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - obj.start)).count());
    }
    
    os << obj.hrs << ":" << obj.min << ":" << obj.sec;
    return os;
  
}

timer timer::operator+(timer & obj)
{
    return timer(hrs + obj.hrs,min + obj.min,sec + obj.sec);
}

void varTime::stcount()
{
    start = std::chrono::system_clock::now();
    count = true;
}

void varTime::addsec(const unsigned int && toadd)
{
    hrs = hrs + (toadd / 3600);
    short hold = (toadd % 3600);
    min = min + (hold / 60);
    sec = sec + (hold % 60);
    
}
