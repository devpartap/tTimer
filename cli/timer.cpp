#include <chrono>
#include <string_view>
#include <sstream>

#include "timer.h"

timer::timer()
    :hrs(0), min(0), sec(0)
{ }
timer::timer(const short& hr, const short& mn, const short& sc)
    :hrs(hr), min(mn), sec(sc)
{
    synctime();
}

timer::timer(std::string_view data)
{
    hrs = ((int)(data[0]- '0')*10) + (int)(data[1]-'0');
    min = ((int)(data[3]-'0')*10) + (int)(data[4]-'0');
    sec = ((int)(data[6] -'0')*10) + (int)(data[7]-'0');
    synctime();
}

timer::~timer(){}

varTime::varTime(const short & h, const short & m, const short & s)
    :timer(h,m,s)
    {}
varTime::varTime()
    :timer()  
    {}


timer timer::operator+(const timer &obj)
{
    return timer(hrs + obj.hrs,min + obj.min,sec + obj.sec);
}
timer timer::operator+(const std::string_view & data)
{
    return timer(hrs + ((int)(data[0]- '0')*10) + (int)(data[1]-'0'),min + ((int)(data[3]-'0')*10) + (int)(data[4]-'0'),sec + ((int)(data[6] -'0')*10) + (int)(data[7]-'0'));
}

 varTime varTime::operator+(const timer &obj)
 {
    update();
    return varTime(hrs + obj.hrs,min + obj.min,sec + obj.sec);
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
    else{
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
std::ostream& operator<<(std::ostream & os,const timer & obj)
{
    (obj.hrs > 9) ? (os << obj.hrs) : (os << 0 << obj.hrs); os << ":";
    (obj.min > 9) ? (os << obj.min) : (os << 0 << obj.min); os << ":";
    (obj.sec > 9) ? (os << obj.sec) : (os << 0 << obj.sec);
    return os;
}


std::ostream& operator<<(std::ostream & os,varTime & obj)
{
    obj.update();
    (obj.hrs > 9) ? (os << obj.hrs) : (os << 0 << obj.hrs); os << ":";
    (obj.min > 9) ? (os << obj.min) : (os << 0 << obj.min); os << ":";
    (obj.sec > 9) ? (os << obj.sec) : (os << 0 << obj.sec);
    return os;
}

bool varTime::operator==(const short* data)
 {  
    if((data[0] == hrs) && (data[1] == min) && (data[2] == sec)){ 
        delete data;
        return true;
    }
    return false;
 }

void timer::synctime()
{
    short _min = min + (sec / 60); 
    hrs = hrs + (_min / 60);
    min = _min % 60;
    sec = (sec % 60);
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
    if(ifcounting){
        const unsigned int data = (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - start)).count();
        start = std::chrono::system_clock::now();
        sec = (sec + (data % 60));
        unsigned int _min = min + (data /60) + (sec / 60); 
        hrs = hrs + (_min / 60);
        min = _min % 60;
        sec = sec%60;
    }
}

std::string printnget(const char * data,const unsigned int & size, timer* times)
{   // [Optimisable?]
    std::stringstream ey;
    ey << " Today's sits :- \n      Duration         Time Studied  Not Studied      Sits \n";

    if(size){
    for(unsigned int i = 0; i<size;i = i + 45)
    {
        timer from = std::string_view(&data[i+12],8);
        timer to = std::string_view(&data[i+23],8);
        timer studied = std::string_view(&data[i+36],8);
        timer duration = to - from;

        ey << from << " => " <<  to << "  -  " << studied << "     " << (duration - studied) << "    | " << duration << "\n";
        times[0] = times[0] + studied;
        times[2] = times[2] + duration;       
    }
    times[1] = times[2] - times[0];
    }
    else
    {
        ey << "         --                 --           --            --\n";
    }
    
    return ey.str();
}

std::string timer_tostr(const timer & obj)
{
    std::stringstream st;
    st << obj;
    return st.str();
}
