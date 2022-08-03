#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include "timer.h"

using namespace std::chrono_literals;
int main()
{
    varTime tim(1,1,1);
    while (true)
    {
        std::this_thread::sleep_for(1s);
        std::cout << tim << std::endl;
    }
}
