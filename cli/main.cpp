#include <iostream>
#include <thread>
#include <string>

#include "timer.h"
#include "io_data.h"
#include "logs.h"

#define countStart 00,00,40 // format hh,mm,ss

using namespace std::chrono_literals;

std::string exeCommand(varTime *vt)
{
    std::string inputcom = "\n";
    bool countstate = false;
    while (true)
    {
        std::getline(std::cin,inputcom,'\n');
        if(inputcom == "")
        {
            if(countstate)
            {
                vt->stop();
                addLog("Stopped Studing!");
            }
            else 
            {
                vt->count();
                addLog("Started Studing!");
            }
        }
        else if(inputcom == "yoyo")
        {
            std::cout << "yup" << std::endl;
        }
        inputcom = "";
        
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
    
    std::thread ifenter(exeCommand,&studied);
    bool towrite = false;

    while(true){

    std::cout << to_print << std::endl;
    std::cout << "         Today Total  :- " << studied + times[0]  << "     " << (sittime - studied) + times[1] << "    | " << sittime + times[2]<< std::endl;    
    std::cout << "         Currently    :- " << studied << "     " << sittime - studied  << "    | " << sittime << std::endl;
    std::cout << '\n' << viewLogs();
    if(towrite){
        savestate(timer_tostr(studied));
    }
    else {
        if(studied == countinfo) towrite = true;
    }

    std::this_thread::sleep_for(1s);
    system("clear");
    }

    ifenter.detach(); 
}

