#include <fstream>
#include <chrono>
#include <array>

#include "io_data.h"

static std::string logs = "";

static std::fstream stream;
static char prefix[24];
static bool isfirst = true;
const std::string getHistory()
{
    stream.open("/home/dev/Documents/Studysaves.txt");
    std::array<char,10> data;
    bool _continue = true;
    int loopcnt= 0;
    std::array<char,10> nowdate;
    std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::strftime(&nowdate[0],11, "%d-%m-%Y", std::localtime(&now));
    //const std::string formatHistory(char* begin,const unsigned int size);

    
    while(_continue)
    {
        stream.seekp((-45*(loopcnt+1)),std::ios::end);
        stream.read(&data[0],10);

        if(data == nowdate) {
            loopcnt++;
        }
        else{
             _continue = false;
        }  
    }
    stream.seekp(-45*(loopcnt),std::ios::end);
    char to_return[(45*loopcnt)+1];
    stream.read(&to_return[0],45*loopcnt);
    stream.close();
    to_return[(45*loopcnt)] = '\0';
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
    stream.open("/home/dev/Documents/Studysaves.txt");
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
    stream.open("/home/dev/Documents/Studysaves.txt");
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
