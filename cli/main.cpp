#include <iostream>
#include <thread>
#include <string>
#include <string_view>
#include <sstream>

#include "timer.h"
#include "io_data.h"
#include "logs.h"

#define countStart 00,00,40 // format hh,mm,ss

using namespace std::chrono_literals;

varTime studied;
varTime sittime;

timer times[3];
std::string to_print = "";

std::string exeCommand()
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
                studied.stop();
                addLog("Stopped Studing!");
            }
            else 
            {
                studied.count();
                addLog("Started Studing!");
            }
        }
        else if(inputcom[0] == '+')
        {
            std::string_view  st(&inputcom[1],8);
            std::string_view nst(&inputcom[10],8);
            std::string_view  et(&inputcom[19],8);

            timer totalsit = timer(st) + nst;
            times[0] = times[0] + st;
            times[1] = times[1] + nst;
            times[2] = times[2] + totalsit;
            
            std::stringstream pss;
            std::stringstream ss;

            pss << timer(et) - totalsit << " => " << et << "  -  " << st << "     " << nst << "    | " << totalsit << '\n';
            ss  << " [" << timer(et) - totalsit << " - " << et << "] => " << st << '\n';
            to_print += pss.str();

            saveexplictTime(ss.str());

        }
        inputcom = "";
        
    }   
}

int main()
{
    short *countinfo = new short[3]{countStart};
    studied.stop();

    noteinfo();
    const std::string history = getHistory();
    
    to_print = printnget(&history[0],history.size(),times);
    
    std::thread ifenter(exeCommand);
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

