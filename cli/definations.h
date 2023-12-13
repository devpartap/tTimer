#define countStart 00,00,30 // format hh,mm,ss
#define dupliTime 30 // time to duplicate main save filec

#if defined(_WIN32) || defined(_WIN64)
    #define __clearconsole system("cls")
#else
    #define __clearconsole system("clear")
#endif