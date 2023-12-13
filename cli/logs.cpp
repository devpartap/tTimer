#include <string>

#include "definations.h"

#define logtimeout 5

static std::string logs = "";
static bool intime = false;
static bool occupied = false;
static short count = 0;

std::string viewLogs()
{
    if(intime){
        if(count == logtimeout)
        {
            logs = "";
            count = 0;
            intime = false;
            return "";
        }
        count++;
        return "         Logs : " + logs + "\n"; //there is some weird relation with this \n and getline something idk, this works
    }
    return "";
}
void addLog(const char* msg)
{
    logs += msg;
    logs += "\n                ";
    count = 0;
    intime = true;
}

