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


#define countStart 00,02,00 // format hh,mm,ss
#define dupliTime 30 // time to duplicate main save filec

using namespace std::chrono_literals;
using namespace mn::CppLinuxSerial;

varTime studied;
varTime sittime;
short loopCount = 1;
bool switchState = true;
bool studyState = false;
bool ledstate = false;
timer times[3];
std::string to_print = "";

void exeCommand();
bool listenSwitch();

std::thread* ifenter;
std::thread* swich;

void createThreads(){
    ifenter = new std::thread(exeCommand);
    swich = new std::thread(listenSwitch);
}

bool listenSwitch()
{
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
            if(studyState)
            {
                studied.stop();
                addLog("Stopped Studing!");
                studyState = false;
            }
            else 
            {
                studied.count();
                addLog("Started Studing!");
                studyState = true;
            }
            readData = "";	
		}

        if(studyState == !ledstate)
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
            if(studyState)
            {
                studied.stop();
                addLog("Stopped Studing!");
                studyState = false;
            }
            else 
            {
                studied.count();
                addLog("Started Studing!");
                studyState = true;
            }
        }



        else if(inputcom[0] == '+')
        {
            std::stringstream pss;
            std::stringstream ss;
            
            if((inputcom[1] == 't') && (inputcom.size() == 3))
            {
                std::string ifrom;
                std::string ist;
                std::string inst;
                std::string itsit;
                if(inputcom[2] == '0')
                {
                    ifrom = "07:00:00";
                    ist = "05:20:00";
                    inst = "00:40:00";
                    itsit = "06:00:00";
                }
                else if(inputcom[2] == '1')
                {
                    ifrom = "08:35:00";
                    ist = "04:00:00";
                    inst = "00:25:00";
                    itsit = "04:25:00";
                }
                else if(inputcom[2] == '2')
                {
                    ifrom = "10:10:00";
                    ist = "02:40:00";
                    inst = "00:10:00";
                    itsit = "02:50:00";  
                }
                else
                {
                    addLog("Invalid Tution Input!");
                    goto end;
                }
                
                times[0] = times[0] + ist;
                times[1] = times[1] + inst;
                times[2] = times[2] + itsit;
                pss << ifrom << " => " << "13:00:00" << "  -  " << ist << "     " << inst << "    | " << itsit << '\n';
                ss  << " [" << ifrom << " - " << "13:00:00" << "] => " << ist << '\n';
                addLog("Tution Time Added!");
            }
            else
            {
                if(inputcom.size() != 27)
                {
                    addLog("Invalid Add Time Input!");
                    goto end;
                }

                std::string_view  st(&inputcom[1],8);
                std::string_view nst(&inputcom[10],8);
                std::string_view  et(&inputcom[19],8);

                timer totalsit = timer(st) + nst;
                times[0] = times[0] + st;
                times[1] = times[1] + nst;
                times[2] = times[2] + totalsit;

                pss << timer(et) - totalsit << " => " << et << "  -  " << st << "     " << nst << "    | " << totalsit << '\n';
                ss  << " [" << timer(et) - totalsit << " - " << et << "] => " << st << '\n';     
            }
            to_print += pss.str();
            saveexplictTime(ss.str());
            end:
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
    }   
}

int main()
{
    
    printProfiles();
    createThreads();

    short *countinfo = new short[3]{countStart};
    studied.stop();

    noteinfo();
    const std::string history = getHistory();
    
    to_print = printnget(&history[0],history.size(),times);
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
    // if((loopCount%dupliTime == 0) && (towrite))
    // {
    //     system("cp /home/dev/Documents/Studysaves.txt /home/dev/Dropbox/Studysaves.txt");
    //     loopCount = 1;
    // }
    // loopCount++;
}
    ifenter->detach(); 
	swich->detach();
}
