#include "profiles.h"

#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>

#include "definations.h"

#define pwait(x) cout << x << endl; getchar()//; std::cin.ignore()

using std::cout, std::endl;

#if defined(__linux__) || defined(__APPLE__)
    static std::filesystem::path _profileDir_ = std::filesystem::current_path() / ".config/tTimer";
#elif defined(_WIN32) || defined(_WIN64)
    static std::filesystem::path _profileDir_ = std::filesystem::current_path() / "Documents/tTimer";
#endif

static std::filesystem::path _currentProfile_;

void createNewProfile()
{
    __clearconsole;

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

    if(!std::filesystem::exists(_profileDir_))
    {
        std::filesystem::create_directories(_profileDir_);
    }

    std::ofstream ofstream;
    ofstream.open(_profileDir_ / profile_name);
    ofstream.close();
    
    pwait("Profile Created, Press any key to continue ");
    __clearconsole;

}

void printProfiles()
{
    bool reloop;
    do {
        if(!std::filesystem::exists(_profileDir_) || std::filesystem::is_empty(_profileDir_))
        {
            pwait("\n  You currently have no profile, press any key to create a profile ");
            createNewProfile();
        }


    
        reloop = false;
        std::vector<std::filesystem::path> profiles;

        for (auto const& dir_entry : std::filesystem::directory_iterator(_profileDir_)) 
        {
            profiles.push_back(dir_entry.path());
        }


        cout << "\nChoose Profile To Log On : \n" << endl;

        for(u_int i = 1;i<=profiles.size();i++)
        {
            cout << "  " << i << ". " << profiles[i-1].stem() << endl; 
        }
        cout << "\n  " << profiles.size()+1 << ". " << "Create New Profile" << endl; 
        cout << "  "   <<  profiles.size()+2 << ". " << "Delete a Profile\n" << endl; 

        cout << "Input :- ";
        int inp = 0;
        std::cin>>inp;
        std::cin.ignore();

        if(inp > profiles.size()+2 || inp <= 0)
        {
            pwait("\n  Invalid Input!");
            reloop = true;
        }
        
        else if(inp == profiles.size()+1)
        {
            createNewProfile();
            reloop = true;
        } 

        else if(inp == profiles.size()+2)
        {
            cout << "  [WARNING: All enteries of the profile will be deleated]\n  Input Profile Index to remove from above:- ";
            int rminp;
            std::cin>>rminp;
            std::cin.ignore();

            std::filesystem::remove(profiles[rminp-1]);
            reloop = true;
        }       

        else
        {
            _currentProfile_.assign(profiles[inp-1]);
        }

        __clearconsole;

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
