#include "profiles.h"

#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>

#define pwait(x) cout << x << endl; getchar(); std::cin.ignore()

using std::cout, std::endl;

static std::filesystem::path _profileDir_ = std::filesystem::current_path() / "profiles";
static std::filesystem::directory_entry _currentProfile_;

void createNewProfile()
{
    system("clear");

    std::string profile_name = "hello there";
    std::cout << "\n  Input New Profile Name(no extension) :- " << std::endl;

    // std::cin >> profile_name;
   
    for(u_int8_t i = 0;i<profile_name.length();i++)
    {
        if(profile_name[i] == ' ')
        {
            profile_name[i] = '_';
        }
    }
    profile_name += ".txt";
    cout << profile_name << endl;


    if(!std::filesystem::exists(_profileDir_))
    {
        std::filesystem::create_directories(_profileDir_);
    }

    _currentProfile_.assign(_profileDir_ / profile_name);
    cout << _currentProfile_ << endl;


    std::ofstream ofstream;
    ofstream.open(_currentProfile_.path());
    
    pwait("Profile Created, Press any key to continue ");
    system("clear");

}

void printProfiles()
{
    if(!std::filesystem::exists(_profileDir_) || std::filesystem::is_empty(_profileDir_))
    {
        pwait("\n  You currently have no profile, press any key to create a profile ");
        createNewProfile();
    }
    

    std::vector<std::string> profiles;

    for (auto const& dir_entry : std::filesystem::directory_iterator(_profileDir_)) 
    {
        profiles.push_back(dir_entry.path().filename());
    }

    for(auto a : profiles)
    {
        std::cout << a << std::endl;
    }
    
    pwait("exit");

    
}

// std::string CurrentDir()
// {
//     return _profileDir_;
// }

// std::string CurrentProfile()
// {
//     return _currentProfile_;
// }

