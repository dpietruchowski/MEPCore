#include "log.h"
#include "color.h"

#include <string>
#include <cstdio>

namespace mep {

Log::Log(LogLevel level, LogTag tag, Color color)
{
    std::string levelTag = toString(level);
    levelTag += ':';
    levelTag += toString(tag);
    levelTag.resize(15, ' ');
    levelTag += ": ";
    os_ << color + levelTag;
}

Log::~Log() {
    os_ << std::endl;
    fprintf(stderr, "%s", os_.str().c_str());
    fflush(stderr);
}

const char *Log::toString(LogTag tag)
{
    switch(tag) {
    case GENE: return "GENE";
    case CHROMOSOME: return "CHROMOSOME";
    case POPULATION: return "POPULATION";
    default: return "TAG";
    }
}

const char* Log::toString(LogLevel level)
{
    switch(level) {
    case ERROR: return "E";
    case WARNING: return "W";
    case INFO: return "I";
    case DEBUG: return "D";
    default: return "L";
    }
}

GeneLog::GeneLog(LogLevel level):
    Log(level, GENE, Color::BLUE)
{}

ChromosomeLog::ChromosomeLog(LogLevel level):
    Log(level, CHROMOSOME, Color::MAGNETA)
{}

PopulationLog::PopulationLog(LogLevel level):
    Log(level, POPULATION, Color::CYAN)
{}

}
