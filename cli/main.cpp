#include <iostream>
#include <thread>

#include "timer.h"
#include "io_data.h"


using namespace std::chrono_literals;

std::string state(varTime *vt)
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
    const std::string history = getdata();

    std::thread ifenter(state,&studied);
     
    while(true){
    std::cout << history << std::endl;
    std::cout << "Today Studied   :- " << studied << "  Not :- " << sittime - studied  << "  | Sit :- " << sittime << std::endl;
    std::this_thread::sleep_for(1s);
    system("clear");
    }

}
