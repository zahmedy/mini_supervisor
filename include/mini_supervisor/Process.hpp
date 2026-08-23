#pragma once

#include <string>

class Process
{
private:
    std::string name_;
    std::string command_;
    int limit_;
    int pid_;

public:
    // Constructer & destructer
    Process(std::string name, std::string command, int limit);
    ~Process();

    // Getters
    std::string get_name() const;
    std::string get_command() const;
    int get_limit() const;
    int get_pid() const;

    // Setters
    void set_limit(int limit);

    // Methods
    int start();
};
