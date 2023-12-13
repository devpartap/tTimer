#include "profiles.h"

#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>

#define pwait(x) cout << x << endl; getchar()//; std::cin.ignore()

using std::cout, std::endl;

static std::filesystem::path _profileDir_ = std::filesystem::current_path() / "profiles";
static std::filesystem::path _currentProfile_;

void createNewProfile()
{
    system("clear");

    std::string profile_name = "";
    std::cout << "\n  Input New Profile Name(no extension) :- ";

    std::getline(std::cin,profile_name);
   
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

    std::ofstream ofstream;
    ofstream.open(_profileDir_ / profile_name);
    ofstream.close();
    
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


    bool reloop;
    do {
        reloop = false;
        std::vector<std::filesystem::path> profiles;

        for (auto const& dir_entry : std::filesystem::directory_iterator(_profileDir_)) 
        {
            profiles.push_back(dir_entry.path());
        }


        cout << "\nChoose Profile To Log On : \n" << endl;

        for(u_int i = 1;i<=profiles.size();i++)
        {
            cout << i << ". " << profiles[i-1].stem() << endl; 
        }
        cout << "\n" << profiles.size()+1 << ". " << "Create New Profile\n" << endl; 

        int inp = 0;
        std::cin>>inp;
        std::cin.ignore();

        if(inp > profiles.size()+1 || inp <= 0)
        {
            pwait("\n  Invalid Input!");
            reloop = true;
        }
        
        else if(inp == profiles.size()+1)
        {
            createNewProfile();
            reloop = true;
        }    

        else
        {
            _currentProfile_.assign(profiles[inp-1]);
        }

        system("clear");

    } while(reloop);
    
}

std::string CurrentDir()
{
    return _profileDir_.string();
}

std::string CurrentProfile()
{
    return _currentProfile_.stem().string();
}

std::string CurrentProfilePath()
{  
    return _currentProfile_.string();
}
