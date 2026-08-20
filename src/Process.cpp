#include "../include/mini_supervisor/Process.hpp"

Process::Process(std::string procName, std::string procCommand, int restartLimit)
    : name(procName), command(procCommand), limit(restartLimit)
{
}

Process::~Process()
{
}
