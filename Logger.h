#ifndef LOGGER
#define LOGGER

#include <fstream>

class Logger
{
    public:
        Logger();
        ~Logger();
        void log(std::string& message) const;
    private:
        inline constexpr static char cLogFileName[] = "log.txt";
        std::ofstream mFile;
};

#endif /* LOGGER */
