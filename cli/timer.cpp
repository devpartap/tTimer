#include "timer.h"

timer::timer()
    :hrs(0), min(0), sec(0)
{ }
timer::~timer(){}

std::ostream& operator<<(std::ostream & os,timer & obj)
{
    os << obj.hrs << ":" << obj.min << ":" << obj.sec;
    return os;
}