#include <iostream>
#include <thread>
#include <string>
#include <string_view>
#include <sstream>

#include "timer.h"
#include "io_data.h"
#include "logs.h"
#include "profiles.h"
#include "Libs/CppLinuxSerial/SerialPort.hpp"

#include "definations.h"


using namespace std::chrono_literals;
using namespace mn::CppLinuxSerial;

short loopCount = 1;
bool switchState = true;
bool workState = false;
bool ledstate = false;

bool runin = true;

timer times[3];
std::string to_print = "";

void exeCommand();
bool listenSwitch();

std::thread* ifenter;
std::thread* swich;

varTime studied;
varTime sittime;


bool listenSwitch()
{
#ifndef __linux__
    return 0;
#endif

    SerialPort serialPort("/dev/ttyACM0", BaudRate::B_9600, NumDataBits::EIGHT, Parity::NONE, NumStopBits::ONE);
    serialPort.SetTimeout(0);
	if(serialPort._Open())
    {
        addLog("Switch Connected!");
    }
    else
    {
        addLog("Switch Not Detected!");
        switchState = false;
        serialPort.Close();
        return 0;
    }

    std::string readData;

    while(true) {
        if(switchState == false){
			serialPort.Close();
            addLog("Switch Disconnected!");
			return 0;
  		}

        serialPort.Read(readData);
		if(readData != "")
		{
            if(workState)
            {
                studied.stop();
                addLog("Stopped Studing!");
                workState = false;
            }
            else 
            {
                studied.count();
                addLog("Started Studing!");
                workState = true;
            }
            readData = "";	
		}

        if(workState == !ledstate)
        {
            serialPort.Write("b");
            ledstate = !ledstate;
            std::this_thread::sleep_for(1s);
        }
    
    std::this_thread::sleep_for(10ms);

	}
}

void exeCommand()
{
    std::string inputcom = "\n";
    while (true)
    {
        std::getline(std::cin,inputcom,'\n');
        if(inputcom == "")
        {
            if(workState)
            {
                studied.stop();
                addLog("Stopped Studing!");
                workState = false;
            }
            else 
            {
                studied.count();
                addLog("Started Studing!");
                workState = true;
            }
        }



        else if(inputcom[0] == '+')
        {
            std::stringstream pss;
            std::stringstream ss;
            
            
            if(inputcom.size() != 27)
            {
                addLog("Invalid Add Time Input!");
            }

            else
            {

                std::string_view  st(&inputcom[1],8);
                std::string_view nst(&inputcom[10],8);
                std::string_view  et(&inputcom[19],8);

                timer totalsit = timer(st) + nst;

                times[0] = times[0] + st;
                times[1] = times[1] + nst;
                times[2] = times[2] + totalsit;

                pss << timer(et) - totalsit << " => " << et << "  -  " << st << "     " << nst << "    | " << totalsit << '\n';
                ss  << " [" << timer(et) - totalsit << " - " << et << "] => " << st << '\n';     

                to_print += pss.str();
                saveexplictTime(ss.str());
            }

            inputcom = "";
        }



        else if(inputcom[0] == 's')
        {
            if(inputcom[1] == '+')
            {
                switchState = true;
                std::thread swich(listenSwitch);
            }
            else
            {
                switchState = false;
            }
        }  

        else if(inputcom[0] == 'q')
        {
            runin = false;
        }      
    }   
}

int main()
{

    studied.stop();
    sittime.stop();

    printProfiles();
    
    short *countinfo = new short[3]{countStart};

    noteinfo();
    const std::string history = getHistory();
    
    to_print = printnget(&history[0],history.size(),times);
    bool towrite = false;

    ifenter = new std::thread(exeCommand);
    swich = new std::thread(listenSwitch);

    sittime.count();

    while(runin){
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
    __clearconsole;

    }

    // ifenter->detach(); 
	swich->detach();

    delete ifenter;
    delete swich;

}
