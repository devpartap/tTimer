@echo off

SET st=false
IF clang++ "-v" (
  echo "-e" "
  clang++ found! compiling"
  IF clang++ "-std=c++20" "-O3" "main.cpp" "timer.cpp" "io_data.cpp" "logs.cpp" "profiles.cpp" "Libs\CppLinuxSerial\SerialPort.cpp" "-lstdc++" "-o" "tTimer" (
    echo "-e" "
    Sucess!
    "
    SET st=true
  ) ELSE (
    echo "-e" "
    Failed!
    "
  )
) ELSE (
  IF g++ (
    echo "-e" "
    g++ found! compiling"
    mkdir "tTimer"
    IF g++ "-std=c++20" "-O3" "main.cpp" "timer.cpp" "io_data.cpp" "logs.cpp" "profiles.cpp" "Libs\CppLinuxSerial\SerialPort.cpp" "-lstdc++" "-o" "tTimer" (
      echo "-e" "
      Sucess!
      "
      SET st=true
    ) ELSE (
      echo "-e" "
      Failed!
      "
    )
  ) ELSE (
    echo "No c++ Compiler Found! Please install a c++ compiler like 'clang++'"
  )
)