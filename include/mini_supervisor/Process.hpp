#pragma once

#include <string>

class Process
{
private:
public:
    std::string name;
    std::string command;
    int limit;
    int pid;

    Process(std::string name, std::string command, int limit);
    ~Process();
};
