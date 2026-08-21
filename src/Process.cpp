#include "../include/mini_supervisor/Process.hpp"

Process::Process(std::string procName, std::string procCommand, int restartLimit)
    : name_(procName), command_(procCommand), limit_(restartLimit)
{
}

Process::~Process()
{
}

std::string Process::get_name() const
{
    return name_;
}

std::string Process::get_command() const
{
    return command_;
}

int Process::get_limit()
{
    return limit_;
}

int Process::get_pid() const
{
    return pid_;
}