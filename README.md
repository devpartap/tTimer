## tTimer
#### **A Productivity Tracker - cli**

It tracks the time worked on the task in a duration and helps you stay productive \
It also saves your progress in profiles folder

**- install -** \
Make sure you have gcc or clang or any of your c++ compilers installed.

1. Clone the repo in your filesystem \
    `git clone https://github.com/devpartap/tTimer.git ` 
    
2. Go to the cli folder \
    ` cd tTimer/cli `
    
3. Build the project \
    For Linux :- `./install_linux.sh ` \
    For Windows :- `install_windows.bat ` 

        To Build yourself \
    ` clang++ -std=c++20 -O3 main.cpp timer.cpp io_data.cpp logs.cpp profiles.cpp Libs/CppLinuxSerial/SerialPort.cpp -lstdc++ -o tTimer` \
                                        or \
    ` gcc -std=c++20 -O3 main.cpp timer.cpp io_data.cpp logs.cpp profiles.cpp Libs/CppLinuxSerial/SerialPort.cpp -lstdc++ -o tTimer` 

**- how to use -**

* This program tracks your worked time on a task over the span of the day.
* Create a profile for your work to track time of.
* Press enter to start or stop your time count.

**- commands -** \
You can interact with the app by following commands. 

|Commands|Explanation |
| - | -|
| 'enter'|To start or stop tracking time.|
| '+hh:mm:ss hh:mm:ss hh:mm:ss'|To add external entry in the record(time not measured by the app) here first time is 'worked time', second time is 'not worked' time and third time is 'stopped working' time.|
| 's'|To enable the attached switch.|
| 's+'|To disable the attached switch.|
| 'q'|To quit the app.|

>Contact me on discord - **Dev_Partap_#3175**
