
#include "Logger.h"
#include <iostream>

Logger::Logger()
{
    mFile.open(cLogFileName);
}

Logger::~Logger()
{
    if (mFile.is_open())
    {
        mFile.close();
    }
}

void Logger::log(std::string& message) const
{
    std::cout << message << std::endl;
}