#include <fstream>
#include <chrono>
#include <array>

#include "io_data.h"
#include "logs.h"
#include "profiles.h"

static std::string logs = "";

static std::fstream stream;
static char prefix[24];
static bool isfirst = true;


const std::string getHistory()
{
    stream.open(CurrentProfilePath());
    std::array<char,10> nowdate;
    std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::strftime(&nowdate[0],11, "%d-%m-%Y", std::localtime(&now));


    stream.seekg(0,std::ios::end);
    unsigned int sze = stream.tellg();
    int loopcnt = 0;

    std::array<char,10> data;    

    while(true)
    { 
        if((loopcnt + 1)*45 <= sze){
            stream.seekg((-45*(loopcnt+1)),std::ios::end);
        }
        else { 
            break;
        }

        stream.read(data.begin(),10);

        if(data == nowdate && (loopcnt + 1)*45 <= sze) {
            loopcnt++;
        }
        else{
             break;
        }  
    }

    stream.seekg(-45*(loopcnt),std::ios::end);

    char to_return[(45*loopcnt)+1];
    stream.read(&to_return[0],45*loopcnt);
    to_return[(45*loopcnt)] = '\0';

    stream.close();
    return to_return;
}

void noteinfo()
{
    std::time_t ontime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::strftime(&prefix[0],24, "%d-%m-%Y [%X - ", std::localtime(&ontime));
}

void savestate(const std::string& stime)
{
    char nowde[14];
    stream.open(CurrentProfilePath());
    if(isfirst){
        stream.seekg(0,std::ios::end);
        isfirst = false;
    }
    else stream.seekg(-45,std::ios::end);
    stream << prefix;

    std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::strftime(&nowde[0],14, "%X] => ", std::localtime(&now));
    stream << &nowde[0] << stime << "\n";
    stream.close();
}

void saveexplictTime(const std::string& tosave)
{
    stream.open(CurrentProfilePath());
    if(isfirst){
        stream.seekg(0,std::ios::end);
    }
    else 
    {
        stream.seekg(-45,std::ios::end);
    }
    isfirst = true;

    stream << prefix[0] << prefix[1]<< prefix[2]<< prefix[3]<< prefix[4]<< prefix[5]<< prefix[6]<< prefix[7]<< prefix[8]<< prefix[9];
    stream << tosave;
    stream.close();
    
}
