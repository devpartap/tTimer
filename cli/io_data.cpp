#include <fstream>
#include <chrono>
#include <array>

#include "io_data.h"


static std::fstream stream;

std::string getdata()
{
    stream.open("saves.txt");
    
    std::array<char,10> data;
    bool _continue = true;
    int loopcnt= 0;
    std::array<char,10> nowdate;
    std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::strftime(&nowdate[0],11, "%d-%m-%Y", std::localtime(&now));

    while(_continue)
    {
        stream.seekp((-45*(loopcnt+1)),std::ios::end);
        //stream.seekp(0);
        stream.read(&data[0],10);

        if(data == nowdate) {
            loopcnt++;
        }
        else{
             _continue = false;
        }  
    }

    stream.seekp(-45*(loopcnt),std::ios::end);
    char to_return[45*loopcnt];
    stream.read(&to_return[0],45*loopcnt);
    stream.close();
    return to_return;
}

