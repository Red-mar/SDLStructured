#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <fstream>
#include <string>

class Log
{
    public:
    static void error(std::string msg);
    static void warning(std::string msg);

    static void log(std::string msg);
    static void log_raw(std::string msg);

    static void debug(std::string msg);
    static void verbose(std::string msg);

    static void debugMode(bool option);
    static void verboseMode(bool option);

    static void colors(bool option);
    static void clearLine();
    static void intToString(int num);

    private:
    static bool isDebugMode;
    static bool isVerboseMode;

    static bool haveEscapeCodes;
};

#endif // !LOG_H
