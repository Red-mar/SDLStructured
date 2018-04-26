#include "log.h"
#include <sstream>

bool Log::isDebugMode = true;
bool Log::isVerboseMode = false;

std::string bold_red     = "";
std::string red          = "";
std::string bold_cyan    = "";
std::string cyan         = "";
std::string bold_green   = "";
std::string green        = "";
std::string bold_yellow  = "";
std::string yellow       = "";
std::string reset_color  = "";
std::string clear_screen = "";
std::string clear_line   = "";

// Prefixes
std::string errorPrefix   = "Error:   ";
std::string warningPrefix = "Warning: ";
std::string debugPrefix   = "Debug:   ";
std::string verbosePrefix = "Verbose: ";
std::string logPrefix     = "Log:     ";

void Log::error(std::string msg)
{
    std::cerr << bold_red << errorPrefix << msg << reset_color << std::endl;
}

void Log::warning(std::string msg)
{
    std::cerr << bold_yellow << warningPrefix << msg << reset_color << std::endl;
}

void Log::log(std::string msg)
{
    std::cout << bold_green << logPrefix << msg << reset_color << std::endl;
}

void Log::debug(std::string msg)
{
    if (isDebugMode)
    {
        std::cerr << bold_cyan << debugPrefix << msg << reset_color << std::endl;
    }
}

void Log::verbose(std::string msg)
{
    if (isVerboseMode)
    {
        std::cerr << cyan << verbosePrefix << msg << reset_color << std::endl;
    }
}

void Log::debugMode(bool option)
{
    if (option == false)
    {
        isDebugMode = false;
        return;
    }

    isDebugMode = true;
    Log::debug("Debug Mode activated");
}
/* not on windows baby
void Log::colors(bool option)
{
	if (option)
	{
		bold_red     = "\e[1;31m";
		red          = "\e[0;31m";
		bold_cyan    = "\e[1;36m";
		cyan         = "\e[0;36m";
		bold_green   = "\e[1;32m";
		green        = "\e[0;32m";
		bold_yellow  = "\e[1;33m";
		yellow       = "\e[0;33m";
		reset_color  = "\e[0m";
		clear_screen = "[H[2J";
		clear_line   = "\r\e[0K";
	}
	else
	{
		bold_red     = "";
		red          = "";
		bold_cyan    = "";
		cyan         = "";
		bold_green   = "";
		green        = "";
		bold_yellow  = "";
		yellow       = "";
		reset_color  = "";
		clear_screen = "";
		clear_line   = "";
	}
}
*/
void Log::verboseMode(bool option)
{
    if (option == false)
    {
        isVerboseMode = false;
        return;
    }

    isVerboseMode = true;
    Log::verbose("Verbose Mode activated");
}