#ifndef LOG_H
#define LOG_H

#include <sstream>

#include "color.h"

namespace mep {

enum LogLevel {
    ERROR,
    WARNING,
    INFO,
    DEBUG
};

enum LogTag {
    GENE,
    CHROMOSOME,
    POPULATION
};

class Log
{
public:
    Log(LogLevel level, LogTag tag, Color color);
    ~Log();

    template<typename Type>
    std::ostringstream& operator<<(const Type& input) {
        os_ << input;
        return os_;
    }

private /* methods */:
    const char* toString(LogTag tag);
    const char* toString(LogLevel level);

private:
     std::ostringstream os_;
};

class GeneLog: public Log
{
public:
    GeneLog(LogLevel level);

    template<typename Type>
    std::ostringstream& operator<<(const Type& input) {
        return Log::operator<<(input);
    }
};

class ChromosomeLog: public Log
{
public:
    ChromosomeLog(LogLevel level);

    template<typename Type>
    std::ostringstream& operator<<(const Type& input) {
        return Log::operator<<(input);
    }
};

class PopulationLog: public Log
{
public:
    PopulationLog(LogLevel level);

    template<typename Type>
    std::ostringstream& operator<<(const Type& input) {
        return Log::operator<<(input);
    }
};

}

#endif // LOG_H
