#ifndef _LOGGER_HPP_
#define _LOGGER_HPP_

#include <cstdio>

class Logger
{
    private:
        int mInfoLog;
        int mWarningLog;
        int mErrorLog;

    public:
        Logger();
        ~Logger();

        void log();
};

#endif

