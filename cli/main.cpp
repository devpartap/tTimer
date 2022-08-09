#include <iostream>
#include <thread>

#include "timer.h"
#include "io_data.h"

#define countStart 00,00,10 // format hh,mm,ss

using namespace std::chrono_literals;

std::string state(varTime *vt)
{
    while (true)
    {
        std::cin.get();
        vt->count();
        std::cin.get();
        vt->stop();
    }   
}

int main()
{
    varTime studied;
    varTime sittime;
    short *countinfo = new short[3]{countStart};
    studied.stop();

    noteinfo();
    const std::string history = getHistory();
    
    timer times[3];
    const std::string to_print = printnget(&history[0],history.size(),times);
    
    std::thread ifenter(state,&studied);
    
    bool towrite = false;
    int j = 0;
    while(true){

    std::cout << to_print << std::endl;
    std::cout << "         Today Total  :- " << studied + times[0]  << "     " << (sittime - studied) + times[1] << "    | " << sittime + times[2]<< std::endl;    
    std::cout << "         Currently    :- " << studied << "     " << sittime - studied  << "    | " << sittime << std::endl;

    if(towrite){
        savestate(timer_tostr(studied));
    }
    else {
        if(studied == countinfo) towrite = true;
    }

    std::this_thread::sleep_for(1s);
    system("clear");
    j++;
    }

    ifenter.detach(); 
}

