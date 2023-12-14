# tTimer bash install script

st=false

if clang++  -v; then
	echo -e "\nclang++ found! compiling"
    if clang++ -std=c++20 -O3 main.cpp timer.cpp io_data.cpp logs.cpp profiles.cpp Libs/CppLinuxSerial/SerialPort.cpp -lstdc++ -o tTimer; then
        echo -e "\nSucess!\n"
        st=true
    else
        echo -e "\nFailed!\n"
    fi

elif g++; then
	echo -e "\ng++ found! compiling"
    mkdir tTimer
    if g++ -std=c++20 -O3 main.cpp timer.cpp io_data.cpp logs.cpp profiles.cpp Libs/CppLinuxSerial/SerialPort.cpp -lstdc++ -o tTimer; then
        echo -e "\nSucess!\n"
        st=true
    else
        echo -e "\nFailed!\n"
    fi

else
	echo "No c++ Compiler Found! Please install a c++ compiler like 'clang++'"
fi




