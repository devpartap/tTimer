## STv2 
#### **A Productivity Tracker - cli**

Still in bare bones, it tracks the time you have studied in a duration and helps you stay productive \
It also save your progress in saves.txt file and helps you track you studied time in the span of the day

**- install -** \
Make sure you have gcc or clang installed, or any of your c++ compilers.

1. clone the repo in you filesystem \
	`git clone https://github.com/devpartap/STv2.git ` 
    
2. Go to cli folder \
	` cd cli `
    
3. build the project \
	` clang++ -std=c++20 -O3 main.cpp timer.cpp io_data.cpp logs.cpp Libs/CppLinuxSerial/SerialPort.cpp -lstdc++ -o STv2` \
    									or \
    ` gcc -std=c++20 -O3 main.cpp timer.cpp io_data.cpp logs.cpp Libs/CppLinuxSerial/SerialPort.cpp -lstdc++ -o STv2` 

**- how to use -** 
* This program tracks your studied time on a span of the day
* Press enter to start or stop your time count

>Contact me on discord - **Dev_Partap_#3175**