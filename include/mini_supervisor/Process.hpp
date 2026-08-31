#pragma once

#include <string>

class Process
{
private:
    std::string name_;
    std::string command_;
    int pid_;
    int pgid_;

public:
    // Constructer & destructer
    Process(std::string name, std::string command, int limit);
    ~Process();

    // Getters
    std::string get_name() const;
    std::string get_command() const;
    int get_pid() const;
    int get_pgid() const;

    // Setters

    // Methods
    int start();
    int stop();
    int wait();
};
