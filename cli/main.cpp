#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include "timer.h"

using namespace std::chrono_literals;

void state(varTime *vt)
{
    while (true)
    {
        std::cin.get();
        vt->stop();
        std::cin.get();
        vt->count();
    }   
}
int main()
{
    varTime studied;
    varTime sittime;

    std::thread ifenter(state,&studied); 
    while(true){
    std::cout << "Today Studied   :- " << studied << "  Not :- " << sittime - studied  << "  | Sit :- " << sittime << std::endl;
    std::this_thread::sleep_for(1s);
    system("clear");
    }

}
